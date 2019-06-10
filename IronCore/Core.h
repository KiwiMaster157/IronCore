#pragma once

#include "Simulation.h"
#include "Layout.h"

#include <map>
#include <string>

namespace iron
{

class Core
{
public:
	
	const std::string& focusTitle() const;
	LayoutView focus();

private:
	std::map<std::string, LayoutData> m_circuits;
	Simulation m_simulation;
	std::string m_root;
	std::pair<const std::string, LayoutData>* m_focus = nullptr;
};

}