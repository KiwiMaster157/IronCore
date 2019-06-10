#pragma once

#include "Utility.h"

#include <vector>

namespace iron
{

class Circuit;

class Part
{
public:
	Part() = default;

	explicit Part(const Circuit* theCircuit,
		Point2i theLocation = Point2i(0, 0),
		Rotation theOrientation = Rotation::None);

	CircuitCallback* getUpdate() const;

	bool isValid() const noexcept;

	int totalSize() const;

	bool pinIsInput(int pin) const;

	bool pinIsOutput(int pin) const;

	short pinWidth(int pin) const;

	Point2i pinLocation(int pin) const;

	int pinCount() const;

	int numArguments() const;

	int numInternal() const;
	
	Point2i getPosition() const noexcept;

	Rotation getRotation() const noexcept;

	Part& setPosition(Point2i newLocation) noexcept;
	Part& setPosition(int x, int y) noexcept;

	Part& move(Point2i offset) noexcept;
	Part& move(int xOffset, int yOffset) noexcept;

	Part& setRotation(Rotation newOrientation) noexcept;

	Part& rotate(Rotation amount) noexcept;

private:
	const Circuit* m_circuit = nullptr;
	std::vector<int> m_arguments;
	Point2i m_position = { 0, 0 };
	Rotation m_orientation = Rotation::None;

	void m_validate() const;
};

}
