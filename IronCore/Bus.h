#pragma once

namespace iron
{

/// Any future versions of this class are NOT allowed to heap allocate.
class Bus
{
public:
	unsigned u;

	Bus& operator&=(Bus signal) noexcept;
	Bus& operator|=(Bus signal) noexcept;
	Bus& operator^=(Bus signal) noexcept;

	/// Returns the number of Busses required to store a signal of given width.
	static short require(short width) noexcept;
};

Bus operator~(Bus signal) noexcept;

Bus operator&(Bus lhs, Bus rhs) noexcept;
Bus operator|(Bus lhs, Bus rhs) noexcept;
Bus operator^(Bus lhs, Bus rhs) noexcept;

bool operator==(Bus lhs, Bus rhs) noexcept;
bool operator!=(Bus lhs, Bus rhs) noexcept;

}