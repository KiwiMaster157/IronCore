#include "ObjectView.h"
#include "Simulation.h"
#include "ObjectControl.h"
#include <stdexcept>

namespace iron
{

#pragma region Lifetime

ObjectView::ObjectView(Node* data, Simulation* simulation, int offset)
	: m_begin(data), m_simulation(simulation), m_position(offset)
{
	if (offset >= simulation->nodeSize())
		throw std::logic_error("iron::ObjectView::ObjectView: index exceeds data");
}

ObjectView& ObjectView::operator=(const ObjectView& view)
{
	if (m_begin != view.m_begin || m_simulation != view.m_simulation)
		throw std::logic_error("iron::ObjectView::operator=: cannot change internal pointers");
	m_position = view.m_position;
	return *this;
}

#pragma endregion

#pragma region Callback

void ObjectView::callback()
{
	m_begin[m_position](*this);
}

#pragma endregion

#pragma region Block Sizes

int ObjectView::numArgs() const noexcept
{
	return m_internalsPosition() - m_argsPosition();
}

int ObjectView::numInternals() const noexcept
{
	return m_inputsPosition() - m_internalsPosition();
}

int ObjectView::numInputs() const noexcept
{
	return m_outputsPosition() - m_inputsPosition();
}

int ObjectView::numOutputs() const noexcept
{
	//Division by 2 is because each output takes 2 Nodes
	return (m_nextObjectPosition() - m_outputsPosition()) / 2;
}

#pragma endregion

#pragma region Accessors

int ObjectView::getArgument(int index) const
{
	if (index < 0)
		throw std::invalid_argument("iron::ObjectView::getArgument: index < 0");
	if (index >= numArgs())
		throw std::invalid_argument("iron::ObjectView::getArgument: index >= count");
	return int(m_begin[m_argsPosition() + index]);
}

Node ObjectView::getInternal(int index) const
{
	if (index < 0)
		throw std::invalid_argument("iron::ObjectView::getInternalInt: index < 0");
	if (index >= numInternals())
		throw std::invalid_argument("iron::ObjectView::getInternalInt: index >= count");
	return m_begin[m_internalsPosition() + index];
}

Bus ObjectView::getInput(int index) const
{
	if (index < 0)
		throw std::invalid_argument("iron::ObjectView::getInput: index < 0");
	if (index >= numInputs())
		throw std::invalid_argument("iron::ObjectView::getInput: index >= count");
	return Bus(m_begin[m_inputsPosition() + index]);
}

Bus ObjectView::getOutput(int index) const
{
	if (index < 0)
		throw std::invalid_argument("iron::ObjectView::getInput: index < 0");
	if (index >= numOutputs())
		throw std::invalid_argument("iron::ObjectView::getInput: index >= count");
	return Bus(m_begin[m_outputDestination(index)]);
}

#pragma endregion

#pragma region Mutators

void ObjectView::setInternal(int index, Node value)
{
	if (index < 0)
		throw std::invalid_argument("iron::ObjectView::setInternal: index < 0");
	if (index >= numInternals())
		throw std::invalid_argument("iron::ObjectView::setInternal: index >= count");
	m_begin[m_internalsPosition() + index] = value;
}

bool ObjectView::setOutput(int index, Bus signal)
{
	if (index < 0)
		throw std::invalid_argument("iron::ObjectView::setOutput: index < 0");
	if (index >= numOutputs())
		throw std::invalid_argument("iron::ObjectView::setOutput: index >= count");
	if (Bus(m_begin[m_outputDestination(index)]) == signal)
		return false;
	m_begin[m_outputDestination(index)] = signal;
	m_simulation->pushEvent(SimulationEvent(m_outputObject(index), true)); //true indicates absolute position
	return true;
}

#pragma endregion

#pragma region Position Accessors (Implementation)

int ObjectView::m_argsPosition() const noexcept
{
	return m_position + ControlOffsets::ArgumentsBegin;
}

int ObjectView::m_internalsPosition() const noexcept
{
	return m_position + int(m_begin[m_position + ControlOffsets::InternalsOffset]);
}

int ObjectView::m_inputsPosition() const noexcept
{
	return m_position + int(m_begin[m_position + ControlOffsets::InputsOffset]);
}

int ObjectView::m_outputsPosition() const noexcept
{
	return m_position + int(m_begin[m_position + ControlOffsets::OutputsOffset]);
}

int ObjectView::m_nextObjectPosition() const noexcept
{
	return m_position + int(m_begin[m_position + ControlOffsets::TotalSize]);
}

int ObjectView::m_outputObject(int index) const noexcept
{
	return int(m_begin[m_outputsPosition() + 2 * index]);
}

int ObjectView::m_outputDestination(int index) const noexcept
{
	return int(m_begin[m_outputsPosition() + 2 * index + 1]);
}

#pragma endregion

}