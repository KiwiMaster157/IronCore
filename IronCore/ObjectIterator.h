#pragma once

#include "Node.h"

namespace iron
{

class ObjectIterator
{
public:
	ObjectIterator() = default;
	ObjectIterator(const Node* data, int nodeCount);

	/// Assigns one ObjectIterator to another
	ObjectIterator& operator=(const ObjectIterator&) = default;

	/// Returns true if the iterator is in bounds, false otherwise.
	/// An iterator is out of bounds if its pointer is NULL or its position
	/// is less than 0 or at least node count.
	explicit operator bool() const noexcept;

	/// Pre-increment operator.
	/// Moves iterator to the next object.
	/// Throws std::logic_error on failure.
	ObjectIterator& operator++();

	/// Pre-decrement operator.
	/// Moves iterator to the previous object.
	/// Throws std::logic_error on failure.
	ObjectIterator& operator--();

	/// Post-increment operator.
	/// Moves iterator to the next object.
	/// Throws std::logic_error on failure.
	ObjectIterator operator++(int);

	/// Post-decrement operator.
	/// Moves iterator to the previous object.
	/// Throws std::logic_error on failure.
	ObjectIterator operator--(int);

	/// Returns the object count.
	int getCount() const noexcept;

	/// Returns the object position.
	int getPosition() const noexcept;

private:
	const Node* m_begin = nullptr;
	int m_position = 0;
	int m_count = 0;
	int m_nodeCount = 0;
};

}