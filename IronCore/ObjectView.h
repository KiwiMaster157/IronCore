#pragma once

#include "Node.h"

namespace iron
{

class Simulation;

class ObjectView
{
public:
	ObjectView(Node* data, Simulation* simulation, int offset);

	/// Assigns one ObjectView to another if their internal pointers are the same.
	/// Throws std::logic_error on failure.
	ObjectView& operator=(const ObjectView& view);

	//Callback

	/// Calls the Object's callback function if it exists.
	/// Otherwise, throws std::logic_error.
	void callback();

	//Block Sizes

	/// Returns the number of arguments the Object has.
	int numArgs() const noexcept;

	/// Returns the number of internal values the Object has.
	int numInternals() const noexcept;

	/// Returns the number of inputs the Object has.
	int numInputs() const noexcept;

	/// Returns the number of outputs the Object has.
	int numOutputs() const noexcept;

	//Accessors

	/// Returns a copy of the specified argument.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the argument to return.
	int getArgument(int index) const;

	/// Returns a copy of the specified internal value.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the internal to return.
	Node getInternal(int index) const;

	/// Returns a copy of the specified input value.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the input to return.
	Bus getInput(int index) const;

	/// Returns a copy of the specified output value.
	/// 
	/// Returns a copy of the input value that the specified output sends to.
	/// Note that this may not be the last value output by the current Object.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the output to return.
	Bus getOutput(int index) const;

	//Mutators

	/// Sets the specified internal value.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the internal value.
	/// \param value is the value to set.
	void setInternal(int index, Node value);

	/// Sets the specified output value.
	///
	/// Sets the input value that the specified output sends to.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the internal value.
	/// \param signal is the value to set.
	/// \return True if the set value was changed.
	bool setOutput(int index, Bus signal);

private:
	Node* const m_begin = nullptr;
	Simulation* const m_simulation = nullptr;
	int m_position = 0;

	//Position Accessors (Implementation)

	int m_argsPosition() const noexcept;
	int m_internalsPosition() const noexcept;
	int m_inputsPosition() const noexcept;
	int m_outputsPosition() const noexcept;
	int m_nextObjectPosition() const noexcept;

	int m_outputObject(int index) const noexcept;
	int m_outputDestination(int index) const noexcept;
};

}