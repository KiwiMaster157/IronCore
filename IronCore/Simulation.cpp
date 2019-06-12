#include "Simulation.h"

#include "FactorySegment.h"
#include "ObjectView.h"
#include "ObjectIterator.h"
#include "Part.h"

#include <stdexcept>

namespace iron
{

SimulationEvent::SimulationEvent(int position)
{
	object = position;
}

SimulationEvent::SimulationEvent(int position, bool isAbsolute)
{
	object = position;
	absolute = isAbsolute;
}

int Simulation::nodeCount() const noexcept
{
	return m_objectData.size();
}

int Simulation::objectCount() const noexcept
{
	if (m_numObjects >= 0)
		return m_numObjects;

	m_numObjects = 0;

	ObjectIterator iterator(m_objectData.data(), nodeCount());

	while (iterator)
	{
		++iterator;
	}

	m_numObjects = iterator.getCount();

	return m_numObjects;
}

bool Simulation::empty() const noexcept
{
	return m_eventQueue.empty();
}

void Simulation::pushEvent(SimulationEvent e)
{
	m_eventQueue.push(e);
}

bool Simulation::runEvent()
{
	if (m_eventQueue.empty())
		return false;
	return runEvent(m_eventQueue.front());
}

bool Simulation::runEvent(SimulationEvent e)
{
	ObjectView object = m_getObject(e);
	object.callback();
	return true;
}

ObjectView Simulation::m_getObject(SimulationEvent e)
{
	if (e.absolute)
		return ObjectView(m_objectData.data(), this, e.object);
	
	ObjectIterator iterator(m_objectData.data(), nodeCount());

	for (int i = 0; i < e.object; i++)
		++iterator;

	return ObjectView(m_objectData.data(), this, iterator.getPosition());
}

//static
//default arg: kickStart = false
Simulation Simulation::makeSimulation(const Part& root, bool kickStart)
{
	Simulation retval;

	retval.m_objectData.reserve(root.totalSize());

	root.simulate(FactorySegment(retval.m_objectData.data(), retval.nodeCount()));

	if (kickStart)
	{
		ObjectIterator iterator(retval.m_objectData.data(), retval.nodeCount());

		while (iterator)
		{
			retval.pushEvent(SimulationEvent(iterator.getPosition(), true));
			++iterator;
		}
	}
	
	return retval;
}

}