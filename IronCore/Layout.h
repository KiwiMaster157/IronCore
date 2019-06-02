#pragma once

#include "Utility.h"

#include <string>
#include <vector>

namespace iron
{

struct LayoutMember
{
	std::string name;
	Point2i position;
	std::vector<int> arguments;
	int offset;
};

struct Pin
{
	Point2i position;
	short width;
	enum Direction : short
	{
		In,
		Out,
		Bidir
	} direction;
};

class Layout
{
public:

private:
	std::vector<LayoutMember> m_children;
	std::vector<Pin> m_ioPins;
	int m_numArguments = 0;
	int m_numInternal = 0;
	LayoutCallback* m_callback = nullptr;
};

}