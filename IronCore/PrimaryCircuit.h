#pragma once

#include "Circuit.h"
#include "ObjectControl.h"

namespace iron
{

class PrimaryCircuit : public Circuit
{
public:

	virtual Circuit::Type getType() const noexcept override final;

	virtual int totalSize(const Part& part) const noexcept override final;
};

}