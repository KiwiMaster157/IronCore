#include "ObjectIterator.h"
#include "ObjectControl.h"
#include <stdexcept>

namespace iron
{

ObjectIterator::ObjectIterator(const Node* data, int nodeCount)
	: m_begin(data), m_nodeCount(nodeCount)
{/* other data default initialized to 0 */}

ObjectIterator::operator bool() const noexcept
{
	if (!m_begin)
		return false;
	if (m_position < 0 || m_position >= m_nodeCount)
		return false;
	return true;
}

ObjectIterator& ObjectIterator::operator++()
{
	if (!*this)
		throw std::runtime_error("iron::ObjectIterator::operator++ index exceeds data");
	m_count++;
	m_position += int(m_begin[m_position + ControlOffsets::TotalSize]);
	return *this;
}

ObjectIterator& ObjectIterator::operator--()
{
	if (!*this)
		throw std::runtime_error("iron::ObjectIterator::operator-- negative index");
	m_count++;
	m_position -= int(m_begin[m_position + ControlOffsets::PreviousSize]);
	return *this;
}

ObjectIterator ObjectIterator::operator++(int)
{
	ObjectIterator retval = *this;
	++(*this);
	return retval;
}

ObjectIterator ObjectIterator::operator--(int)
{
	ObjectIterator retval = *this;
	--(*this);
	return retval;
}

int ObjectIterator::getCount() const noexcept
{
	return m_count;
}

int ObjectIterator::getPosition() const noexcept
{
	return m_position;
}

}