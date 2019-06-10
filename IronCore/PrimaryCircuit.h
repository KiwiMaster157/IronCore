#pragma once

#include "Circuit.h"
#include "ObjectControl.h"

namespace iron
{

class PrimaryCircuit : public Circuit
{
public:

	virtual Circuit::Type getType() const noexcept override final
	{
		return Circuit::Type::Primary;
	}

	virtual int totalSize(const Part& part) const noexcept override final
	{
		int numOutput = 0;
		for (int i = 0; i < pinCount(part); i++)
		{
			if (pinIsOutput(part, i))
			{
				numOutput++;
			}
		}

		return numOutput + pinCount(part) + numInternal(part)
			+ numArguments(part) + ControlOffsets::Count;
	}
};

}