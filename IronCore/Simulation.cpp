#include "Simulation.h"
#include "ObjectView.h"
#include "ObjectIterator.h"

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

int Simulation::nodeSize() const noexcept
{
	return m_objectData.size();
}

int Simulation::objectSize() const noexcept
{
	if (m_numObjects >= 0)
		return m_numObjects;

	m_numObjects = 0;

	ObjectIterator iterator(m_objectData.data(), m_objectData.size());

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
	
	ObjectIterator iterator(m_objectData.data(), m_objectData.size());

	for (int i = 0; i < e.object; i++)
		++iterator;

	return ObjectView(m_objectData.data(), this, iterator.getPosition());
}

}