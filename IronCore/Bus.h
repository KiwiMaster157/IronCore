#pragma once

namespace iron
{

class Bus
{
public:
	unsigned u;

	Bus& operator&=(Bus signal) noexcept;
	Bus& operator|=(Bus signal) noexcept;
	Bus& operator^=(Bus signal) noexcept;
};

Bus operator~(Bus signal) noexcept;

Bus operator&(Bus lhs, Bus rhs) noexcept;
Bus operator|(Bus lhs, Bus rhs) noexcept;
Bus operator^(Bus lhs, Bus rhs) noexcept;

bool operator==(Bus lhs, Bus rhs) noexcept;
bool operator!=(Bus lhs, Bus rhs) noexcept;

}