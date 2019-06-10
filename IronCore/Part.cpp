#include "Part.h"

#include "Circuit.h"

#include <stdexcept>

namespace iron
{

Part::Part(const Circuit* theCircuit, Point2i theLocation, Rotation theOrientation)
{
	m_circuit = theCircuit;
	m_position = theLocation;
	m_orientation = theOrientation;
	m_arguments.resize(numArguments());
}

CircuitCallback* Part::getUpdate() const
{
	m_validate();
	return m_circuit->getUpdate();
}

bool Part::isValid() const noexcept
{
	return !!m_circuit;
}

int Part::totalSize() const
{
	m_validate();
	return m_circuit->totalSize(*this);
}

bool Part::pinIsInput(int pin) const
{
	m_validate();
	return m_circuit->pinIsInput(*this, pin);
}

bool Part::pinIsOutput(int pin) const
{
	m_validate();
	return m_circuit->pinIsOutput(*this, pin);
}

short Part::pinWidth(int pin) const
{
	m_validate();
	return m_circuit->pinWidth(*this, pin);
}

Point2i Part::pinLocation(int pin) const
{
	m_validate();
	return (m_circuit->pinLocation(*this, pin) + m_position).rotation(m_orientation);
}

int Part::pinCount() const
{
	m_validate();
	return m_circuit->pinCount(*this);
}

int Part::numArguments() const
{
	m_validate();
	return m_circuit->numArguments(*this);
}

int Part::numInternal() const
{
	m_validate();
	return m_circuit->numInternal(*this);
}

Point2i Part::getPosition() const noexcept
{
	return m_position;
}

Rotation Part::getRotation() const noexcept
{
	return m_orientation;
}

Part& Part::setPosition(Point2i newLocation) noexcept
{
	m_position = newLocation;
	return *this;
}

Part& Part::setPosition(int x, int y) noexcept
{
	m_position.x = x;
	m_position.y = y;
	return *this;
}

Part& Part::move(Point2i offset) noexcept
{
	m_position += offset;
	return *this;
}

Part& Part::move(int xOffset, int yOffset) noexcept
{
	m_position.x += xOffset;
	m_position.y += yOffset;
	return *this;
}

Part& Part::setRotation(Rotation newOrientation) noexcept
{
	m_orientation = newOrientation;
	return *this;
}

Part& Part::rotate(Rotation amount) noexcept
{
	switch (amount)
	{
	case Rotation::Clockwise:
		switch (m_orientation)
		{
		case Rotation::Clockwise:
			m_orientation = Rotation::Flip;
			break;
		case Rotation::Flip:
			m_orientation = Rotation::CounterClockwise;
			break;
		case Rotation::CounterClockwise:
			m_orientation = Rotation::None;
			break;
		case Rotation::None:
		default:
			m_orientation = Rotation::Clockwise;
			break;
		}
		break;
	case Rotation::Flip:
		switch (m_orientation)
		{
		case Rotation::Clockwise:
			m_orientation = Rotation::CounterClockwise;
			break;
		case Rotation::Flip:
			m_orientation = Rotation::None;
			break;
		case Rotation::CounterClockwise:
			m_orientation = Rotation::Clockwise;
			break;
		case Rotation::None:
		default:
			m_orientation = Rotation::Flip;
			break;
		}
		break;
	case Rotation::CounterClockwise:
		switch (m_orientation)
		{
		case Rotation::Clockwise:
			m_orientation = Rotation::None;
			break;
		case Rotation::Flip:
			m_orientation = Rotation::Clockwise;
			break;
		case Rotation::CounterClockwise:
			m_orientation = Rotation::Flip;
			break;
		case Rotation::None:
		default:
			m_orientation = Rotation::CounterClockwise;
			break;
		}
		break;
	case Rotation::None:
	default:;
		//Do nothing.
	}
	return *this;
}

void Part::m_validate() const
{
	if (!isValid())
		throw std::runtime_error("Part has invalid Circuit.");
}

}