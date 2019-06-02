#pragma once

#include "Node.h"

#include <vector>
#include <queue>

namespace iron
{

class SimulationEvent
{
public:
	SimulationEvent() = default;
	SimulationEvent(int position);
	
	friend class Simulation;
	friend class ObjectView;
	friend class ObjectIterator;
	
	int object = 0;

private:
	SimulationEvent(int position, bool isAbsolute);
	
	bool absolute = false;
};

class Simulation
{
public:
	
	/// Returns the number of Nodes in m_objectData.
	int nodeSize() const noexcept;
	
	int objectSize() const noexcept;

	/// Returns true if the event queue is empty.
	bool empty() const noexcept;

	/// Adds an event to the queue.
	/// 
	/// \param e is the event to add
	void pushEvent(SimulationEvent e);

	/// If event queue is empty, returns false.
	/// Otherwise, removes an event from the queue, runs it, and returns true.
	bool runEvent();

	/// Runs a given event and returns true.
	///
	/// \param e is the event to run
	bool runEvent(SimulationEvent e);

private:
	std::vector<Node> m_objectData;
	std::queue<SimulationEvent> m_eventQueue;
	mutable int m_numObjects = -1;

	/// Creates an ObjectView corresponding to an event
	///
	/// \param e is the event to extract the object from
	ObjectView m_getObject(SimulationEvent e);
};

}