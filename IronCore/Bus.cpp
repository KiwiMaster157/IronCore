#include "Bus.h"

namespace iron
{

Bus& Bus::operator&=(Bus signal) noexcept
{
	u &= signal.u;
	return *this;
}

Bus& Bus::operator|=(Bus signal) noexcept
{
	u |= signal.u;
	return *this;
}

Bus& Bus::operator^=(Bus signal) noexcept
{
	u ^= signal.u;
	return *this;
}

Bus operator~(Bus signal) noexcept
{
	Bus retval;
	retval.u = ~signal.u;
	return retval;
}

Bus operator&(Bus lhs, Bus rhs) noexcept
{
	Bus retval = lhs;
	retval &= rhs;
	return retval;
}

Bus operator|(Bus lhs, Bus rhs) noexcept
{
	Bus retval = lhs;
	retval |= rhs;
	return retval;
}

Bus operator^(Bus lhs, Bus rhs) noexcept
{
	Bus retval = lhs;
	retval ^= rhs;
	return retval;
}

bool operator==(Bus lhs, Bus rhs) noexcept
{
	return lhs.u == rhs.u;
}

bool operator!=(Bus lhs, Bus rhs) noexcept
{
	return !(lhs == rhs);
}

}