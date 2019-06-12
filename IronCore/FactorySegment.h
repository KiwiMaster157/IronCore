#pragma once

#include "Node.h"

namespace iron
{

class FactorySegment
{
public:
	FactorySegment() = delete;
	FactorySegment(Node* thePtr, int theSize);

	/// Returns a sub-segment of the calling object.
	/// If lenght == npos, segment extends to end.
	FactorySegment subSegment(int begin, int length);

	/// Returns a sub-segment of the calling object.
	/// Return value starts at end of current object.
	/// If length == npos, segment extends to end.
	FactorySegment postSegment(int length = FactorySegment::npos);

#pragma region Size Accessors

	bool isObject() const noexcept;

	/// Returns the number of elements in the segment.
	int size() const noexcept;

	/// Returns the number of arguments the Object has.
	/// Returns npos on failure.
	int numArgs() const noexcept;

	/// Returns the number of internal values the Object has.
	/// Returns npos on failure.
	int numInternals() const noexcept;

	/// Returns the number of inputs the Object has.
	/// Returns npos on failure.
	int numInputs() const noexcept;

	/// Returns the number of outputs the Object has.
	/// Returns npos on failure.
	int numOutputs() const noexcept;

	/// Returns the total size of the Object.
	/// Returns npos on failure.
	int objectSize() const noexcept;

#pragma endregion

#pragma region Element Accessors

	/// Returns the index'th element in the segment.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the item to return.
	Node& operator[](int index);

	/// Returns the index'th element in the segment.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the item to return.
	const Node& operator[](int index) const;

	/// Returns a copy of the callback function pointer.
	/// Returns nullptr on failure.
	CircuitCallback* getCallback() const noexcept;

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
	int getOutputObject(int index) const;

	/// Returns a copy of the specified output value.
	/// 
	/// Returns a copy of the input value that the specified output sends to.
	/// Note that this may not be the last value output by the current Object.
	/// Throws std::invalid_argument if the index is out of range.
	///
	/// \param index is the position of the output to return.
	int getOutputDestination(int index) const;

#pragma endregion

#pragma region Size Mutators

	/// Fills the control block offsets given a list of sizes.
	/// Throws std::domain_error on size failure.
	/// Returns reference to calling object.
	FactorySegment& setControlBlock(int numArguments, int numInternals, 
		int numInputs, int numOutputs);

#pragma endregion

#pragma region Element Mutators

	/// Sets the callback function.
	/// Throws std::domain_error on size failure.
	/// Returns reference to calling object.
	FactorySegment& setCallback(CircuitCallback* function);

	/// Sets the specified argument.
	/// Throws std::domain_error on failure.
	/// Throws std::invalid_argument on index failure.
	/// Returns reference to calling object.
	FactorySegment& setArgument(int index, Node value);

	/// Sets the specified internal value.
	/// Throws std::domain_error on failure.
	/// Throws std::invalid_argument on index failure.
	/// Returns reference to calling object.
	FactorySegment& setInternal(int index, Node value);

	/// Sets the specified output object index.
	/// Throws std::domain_error on failure.
	/// Throws std::invalid_argument on index failure.
	/// Returns reference to calling object.
	FactorySegment& setOutputObject(int index, int value);

	/// Sets the specified output destination index.
	/// Throws std::domain_error on failure.
	/// Throws std::invalid_argument on index failure.
	/// Returns reference to calling object.
	FactorySegment& setOutputDestination(int index, int value);

	/// Sets the specified output object and destination indices.
	/// Throws std::domain_error on failure.
	/// Throws std::invalid_argument on index failure.
	/// Returns reference to calling object.
	FactorySegment& setOutput(int index, int object, int destination);

#pragma endregion

	enum
	{
		npos = -1
	};

private:
	Node* m_ptr = nullptr;
	int m_size = 0;

	int m_argsPosition() const noexcept;
	int m_internalsPosition() const noexcept;
	int m_inputsPosition() const noexcept;
	int m_outputsPosition() const noexcept;
	int m_nextObjectPosition() const noexcept;

	int m_outputObject(int index) const noexcept;
	int m_outputDestination(int index) const noexcept;
};

}