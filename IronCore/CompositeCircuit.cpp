#include "CompositeCircuit.h"
#include "ObjectControl.h"

namespace iron
{

Circuit::Type CompositeCircuit::getType() const noexcept
{
	return Circuit::Type::Composite;
}

int CompositeCircuit::totalSize(const Part& part) const noexcept
{
	if (m_sizeCacheUpdated)
		return m_sizeCache;

	m_sizeCache = ControlOffsets::Count + 2 * m_pins.size();
	for (int i = 0; i < m_parts.size(); i++)
	{
		m_sizeCache += m_parts[i].totalSize();
	}

	m_sizeCacheUpdated = true;
	return m_sizeCache;
}

bool CompositeCircuit::pinIsInput(const Part& part, int pin) const noexcept
{
	switch (m_pins.at(pin).direction)
	{
	case Pin::Direction::In:
	case Pin::Direction::Bidir:
		return true;
	}
	return false;
}

bool CompositeCircuit::pinIsOutput(const Part& part, int pin) const noexcept
{
	switch (m_pins.at(pin).direction)
	{
	case Pin::Direction::Out:
	case Pin::Direction::Bidir:
		return true;
	}
	return false;
}

short CompositeCircuit::pinWidth(const Part& part, int pin) const noexcept
{
	return m_pins.at(pin).width;
}

Point2i CompositeCircuit::pinLocation(const Part& part, int pin) const noexcept
{
	return m_pins.at(pin).location;
}

void CompositeCircuit::clearCache() noexcept
{
	m_sizeCacheUpdated = false;
}

}