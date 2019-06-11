#include "PrimaryCircuit.h"

namespace iron
{

Circuit::Type PrimaryCircuit::getType() const noexcept
{
	return Circuit::Type::Primary;
}

int PrimaryCircuit::totalSize(const Part& part) const noexcept
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

}