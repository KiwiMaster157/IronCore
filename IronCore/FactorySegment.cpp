#include "FactorySegment.h"
#include "ObjectControl.h"

#include <stdexcept>

namespace iron
{

FactorySegment::FactorySegment(Node* thePtr, int theSize)
{
	m_ptr = thePtr;
	m_size = theSize;
}

FactorySegment FactorySegment::subSegment(int begin, int length)
{
	if (begin < 0 || begin >= m_size)
		throw std::logic_error("Invalid sub-segment begin.");

	if (length == FactorySegment::npos)
		return FactorySegment(m_ptr + begin, m_size - begin);
	
	if (begin + length > m_size || length < 0)
		throw std::logic_error("Invalid FactorySegment length.");

	return FactorySegment(m_ptr + begin, length);
}

FactorySegment FactorySegment::postSegment(int length)
{
	return subSegment(objectSize(), length);
}

#pragma region Size Accessors

bool FactorySegment::isObject() const noexcept
{
	return m_size >= ControlOffsets::Count;
}

int FactorySegment::size() const noexcept
{
	return m_size;
}

int FactorySegment::numArgs() const noexcept
{
	if (!isObject())
		return FactorySegment::npos;
	return m_internalsPosition() - m_argsPosition();
}

int FactorySegment::numInternals() const noexcept
{
	if (!isObject())
		return FactorySegment::npos;
	return m_inputsPosition() - m_internalsPosition();
}

int FactorySegment::numInputs() const noexcept
{
	if (!isObject())
		return FactorySegment::npos;
	return m_outputsPosition() - m_inputsPosition();
}

int FactorySegment::numOutputs() const noexcept
{
	if (!isObject())
		return FactorySegment::npos;
	return m_nextObjectPosition() - m_outputsPosition();
}

int FactorySegment::objectSize() const noexcept
{
	if (!isObject())
		return FactorySegment::npos;
	return m_nextObjectPosition();
}

#pragma endregion

#pragma region Element Access

Node& FactorySegment::operator[](int index)
{
	return const_cast<Node&>(
		const_cast<const FactorySegment&>(*this)[index]);
}

const Node& FactorySegment::operator[](int index) const
{
	if (index < 0 || index >= m_size)
		throw std::invalid_argument("Invalid index for FactorySegment");
	return m_ptr[index];
}

CircuitCallback* FactorySegment::getCallback() const noexcept
{
	if (m_size <= 0)
		return nullptr;
	return m_ptr->getFunction();
}

int FactorySegment::getArgument(int index) const
{
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::getArgument invalid index.");
	return int(operator[](m_argsPosition() + index));
}

Node FactorySegment::getInternal(int index) const
{
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::getInternal invalid index.");
	return operator[](m_internalsPosition() + index);
}

int FactorySegment::getOutputObject(int index) const
{
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::getOutputObject invalid index.");
	return int(operator[](m_outputsPosition() + 2 * index));
}

int FactorySegment::getOutputDestination(int index) const
{
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::getOutputDestination invalid index.");
	return int(operator[](m_outputsPosition() + 2 * index + 1));
}

#pragma endregion

#pragma region Size Mutators

FactorySegment& FactorySegment::setControlBlock(int numArguments,
	int numInternals, int numInputs, int numOutputs)
{
	if (!isObject())
		throw std::domain_error("FactorySegment is not an object.");
	int total = numArguments;
	m_ptr[ControlOffsets::InternalsOffset] = total;
	total += numInternals;
	m_ptr[ControlOffsets::InputsOffset] = total;
	total += numInputs;
	m_ptr[ControlOffsets::OutputsOffset] = total;
	total += 2 * numOutputs;
	m_ptr[ControlOffsets::TotalSize] = total;
	if (total > m_size)
		throw std::domain_error("Control Block totalSize excedes FactorySegment.");
	return *this;
}

#pragma endregion

#pragma region Element Mutators

FactorySegment& FactorySegment::setCallback(CircuitCallback* function)
{
	if (!isObject())
		throw std::domain_error("FactorySegment is not an object.");
	*m_ptr = Node(function);
	return *this;
}

FactorySegment& FactorySegment::setArgument(int index, Node value)
{
	if (!isObject())
		throw std::domain_error("FactorySegment is not an object.");
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::setArgument invalid index.");
	operator[](m_argsPosition() + index) = value;
	return *this;
}

FactorySegment& FactorySegment::setInternal(int index, Node value)
{
	if (!isObject())
		throw std::domain_error("FactorySegment is not an object.");
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::setInternal invalid index.");
	operator[](m_internalsPosition() + index) = value;
	return *this;
}

FactorySegment& FactorySegment::setOutputObject(int index, int value)
{
	if (!isObject())
		throw std::domain_error("FactorySegment is not an object.");
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::setOutputObject invalid index.");
	operator[](m_outputsPosition() + 2 * index) = value;
	return *this;
}

FactorySegment& FactorySegment::setOutputDestination(int index, int value)
{
	if (!isObject())
		throw std::domain_error("FactorySegment is not an object.");
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::setOutputDestination invalid index.");
	operator[](m_outputsPosition() + 2 * index + 1) = value;
	return *this;
}

FactorySegment& FactorySegment::setOutput(int index, int object, int destination)
{
	if (!isObject())
		throw std::domain_error("FactorySegment is not an object.");
	if (index < 0 || index >= numArgs())
		throw std::invalid_argument("iron::FactorySegment::setOutput invalid index.");
	operator[](m_outputsPosition() + 2 * index) = object;
	operator[](m_outputsPosition() + 2 * index + 1) = destination;
	return *this;
}

#pragma endregion

#pragma region Position Accessors (Implementation)

int FactorySegment::m_argsPosition() const noexcept
{
	return ControlOffsets::ArgumentsBegin;
}

int FactorySegment::m_internalsPosition() const noexcept
{
	return int(m_ptr[ControlOffsets::InternalsOffset]);
}

int FactorySegment::m_inputsPosition() const noexcept
{
	return int(m_ptr[ControlOffsets::InputsOffset]);
}

int FactorySegment::m_outputsPosition() const noexcept
{
	return int(m_ptr[ControlOffsets::OutputsOffset]);
}

int FactorySegment::m_nextObjectPosition() const noexcept
{
	return int(m_ptr[ControlOffsets::TotalSize]);
}

int FactorySegment::m_outputObject(int index) const noexcept
{
	return int(m_ptr[m_outputsPosition() + 2 * index]);
}

int FactorySegment::m_outputDestination(int index) const noexcept
{
	return int(m_ptr[m_outputsPosition() + 2 * index + 1]);
}

#pragma endregion

}