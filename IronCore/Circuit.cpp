#include "Circuit.h"

#include <stdexcept>

namespace iron
{

CircuitCallback* Circuit::getUpdate() const
{
	switch (m_data.index())
	{
	case Primary:
		if(m_getPrimary().logic.update)
			return m_getPrimary().logic.update;
		throw std::logic_error("PrimaryCircuit has no 'update' function.");
	case Compound:
		return circuit::CompoundLogic::update;
	}
	throw std::runtime_error("Circuit has invalid variant type.");
}

bool Circuit::pinIsInput(const circuit::Part& part, int pin) const
{
	if (pin < 0 || pin >= pinCount(part))
		throw std::invalid_argument("Index out of bounds.");

	switch (m_data.index())
	{
	case Primary:
		if(m_getPrimary().logic.pinIsInput)
			return m_getPrimary().logic.pinIsInput(part, pin);
		throw std::logic_error("PrimaryCircuit has no 'pinIsInput' function.");
	case Compound:
		return m_getCompound().logic.pinIsInput(pin);
	}
	throw std::runtime_error("Circuit has invalid variant type.");
}

bool Circuit::pinIsOutput(const circuit::Part& part, int pin) const
{
	if (pin < 0 || pin >= pinCount(part))
		throw std::invalid_argument("Index out of bounds.");

	switch (m_data.index())
	{
	case Primary:
		if (m_getPrimary().logic.pinIsOutput)
			return m_getPrimary().logic.pinIsOutput(part, pin);
		throw std::logic_error("PrimaryCircuit has no 'pinIsOutput' function.");
	case Compound:
		return m_getCompound().logic.pinIsOutput(pin);
	}
	throw std::runtime_error("Circuit has invalid variant type.");
}

short Circuit::pinWidth(const circuit::Part& part, int pin) const
{
	if (pin < 0 || pin >= pinCount(part))
		throw std::invalid_argument("Index out of bounds.");

	switch (m_data.index())
	{
	case Primary:
		if (m_getPrimary().logic.pinWidth)
			return m_getPrimary().logic.pinWidth(part, pin);
		throw std::logic_error("PrimaryCircuit has no 'pinWidth' function.");

	case Compound:
		return m_getCompound().logic.pinWidth(pin);
	}
	throw std::runtime_error("Circuit has invalid variant type.");
}

Point2i Circuit::pinLocation(const circuit::Part& part, int pin) const
{
	if (pin < 0 || pin >= pinCount(part))
		throw std::invalid_argument("Index out of bounds.");

	switch (m_data.index())
	{
	case Primary:
		if (m_getPrimary().logic.pinLocation)
			return m_getPrimary().logic.pinLocation(part, pin);
		throw std::logic_error("PrimaryCircuit has no 'pinLocation' function.");

	case Compound:
		return m_getCompound().logic.pinLocation(pin);
	}
	throw std::runtime_error("Circuit has invalid variant type.");
}

int Circuit::pinCount(const circuit::Part& part) const
{
	switch (m_data.index())
	{
	case Primary:
		if (m_getPrimary().logic.pinCount)
			return m_getPrimary().logic.pinCount(part);
		throw std::logic_error("PrimaryCircuit has no 'pinCount' function.");

	case Compound:
		return m_getCompound().logic.pinCount();
	}
	throw std::runtime_error("Circuit has invalid variant type.");
}

int Circuit::numArguments(const circuit::Part& part) const
{
	switch (m_data.index())
	{
	case Primary:
		if (m_getPrimary().logic.numArguments)
			return m_getPrimary().logic.numArguments(part);
		throw std::logic_error("PrimaryCircuit has no 'numArguments' function.");

	case Compound:
		return m_getCompound().logic.numArguments();
	}
	throw std::runtime_error("Circuit has invalid variant type.");
}

int Circuit::numInternal(const circuit::Part& part) const
{
	switch (m_data.index())
	{
	case Primary:
		if (m_getPrimary().logic.numInternal)
			return m_getPrimary().logic.numInternal(part);
		throw std::logic_error("PrimaryCircuit has no 'numInternal' function.");

	case Compound:
		return m_getCompound().logic.numInternal();
	}
	throw std::runtime_error("Circuit has invalid variant type.");
}

circuit::PrimaryCircuit& Circuit::m_getPrimary()
{
	return std::get<Primary>(m_data);
}

const circuit::PrimaryCircuit& Circuit::m_getPrimary() const
{
	return std::get<Primary>(m_data);
}

circuit::CompoundCircuit& Circuit::m_getCompound()
{
	return std::get<Compound>(m_data);
}

const circuit::CompoundCircuit& Circuit::m_getCompound() const
{
	return std::get<Compound>(m_data);
}

}