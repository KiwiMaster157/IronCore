#pragma once

#include "Utility.h"

#include <string>
#include <vector>

namespace iron
{

class Core;

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
	int internalItem;
	short width;
	enum Direction : short
	{
		In,
		Out,
		Bidir
	} direction;
};

struct LayoutData
{
	std::vector<LayoutMember> m_children;
	std::vector<Pin> m_ioPins;
	int m_numArguments = 0;
	int m_numInternal = 0;
	CircuitCallback* m_callback = nullptr;
};

class LayoutView
{
public:
	
private:
	LayoutData* m_data = nullptr;
	Core* m_core = nullptr;
};

}