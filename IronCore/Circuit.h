#pragma once

#include "Utility.h"
#include "FactorySegment.h"

#include <stdexcept>
#include <string>
#include <variant>

namespace iron
{

class Part;

class Circuit
{
public:
#pragma region Lifetime

	enum class Type
	{
		Primary,
		Composite
	};
	
	virtual ~Circuit() = default;

	virtual Type getType() const noexcept = 0;

#pragma endregion

#pragma region Query
	/// Returns a pointer to the update function
	virtual CircuitCallback* getUpdate() const = 0;
	
	/// Determines the total number of Nodes an object will occupy.
	virtual int totalSize(const Part& part) const noexcept = 0;

	/// Determines if the specified pin is an input.
	///
	/// \param part is the Part being inspected.
	/// \param pin is the index of the Pin being inspected.
	/// \return true if the pin is an input, false otherwise.
	virtual bool pinIsInput(const Part& part, int pin) const noexcept = 0;

	/// Determines if the specified pin is an output.
	///
	/// \param part is the Part being inspected.
	/// \param pin is the index of the Pin being inspected.
	/// \return true if the pin is an output, false otherwise.
	virtual bool pinIsOutput(const Part& part, int pin) const noexcept = 0;

	/// Determines the bit-width of the specified pin.
	///
	/// \param part is the Part being inspected.
	/// \param pin is the index of the Pin being inspected.
	/// \return the bit-width of the pin.
	virtual short pinWidth(const Part& part, int pin) const noexcept = 0;

	/// Determines the location of the specified pin.
	/// Location is relative to the origin of the part and does not 
	/// take into account rotation.
	///
	/// \param part is the Part being inspected.
	/// \param pin is the index of the Pin being inspected.
	/// \return the location of the pin.
	virtual Point2i pinLocation(const Part& part, int pin) const noexcept = 0;

	/// Determines how many pins the part has.
	/// This value will be used by the caller of pin___ functions to verify range.
	///
	/// \param part is the Part being inspected.
	/// \return the number of pins the part has.
	virtual int pinCount(const Part& part) const noexcept = 0;

	/// Determines how many arguments the part has.
	virtual int numArguments(const Part& part) const noexcept = 0;

	/// Determines how many internal values the part has.
	virtual int numInternal(const Part& part) const noexcept = 0;

	virtual void simulate(const Part& part, FactorySegment factory) const = 0;
#pragma endregion
};

}