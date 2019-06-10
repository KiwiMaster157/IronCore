#pragma once

#include "Circuit.h"
#include "Part.h"
#include "Utility.h"

#include <vector>

namespace iron
{

class CompositeCircuit final : public Circuit
{
public:

#pragma region Inherited Interface
	virtual Circuit::Type getType() const noexcept override;

	virtual int totalSize(const Part& part) const noexcept override;

	virtual bool pinIsInput(const Part& part, int pin) const noexcept override;

	virtual bool pinIsOutput(const Part& part, int pin) const noexcept override;

	virtual short pinWidth(const Part& part, int pin) const noexcept override;

	virtual Point2i pinLocation(const Part& part, int pin) const noexcept override;
#pragma endregion

	void clearCache() noexcept; //< should this be const?
#pragma region CompositeInterface


#pragma endregion

private:
	std::vector<Pin> m_pins;
	std::vector<Part> m_parts;

	mutable int m_sizeCache;
	mutable bool m_sizeCacheUpdated = false;
};

}