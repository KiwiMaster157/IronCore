#include "Node.h"
#include "ObjectView.h"

#include <stdexcept>

namespace iron
{

Node::Node(int data) noexcept
{
	m_data.i = data;
}

Node::Node(CircuitCallback* function) noexcept
{
	m_data.fn = function;
}

Node::Node(Bus signal) noexcept
{
	m_data.b = signal;
}

Node& Node::operator=(int data) noexcept
{
	m_data.i = data;
	return *this;
}

Node& Node::operator=(Bus signal) noexcept
{
	m_data.b = signal;
	return *this;
}

Node::operator int() const noexcept
{
	return m_data.i;
}

Node::operator Bus() const noexcept
{
	return m_data.b;
}

void Node::operator()(const ObjectView& object)
{
	if (!m_data.fn)
		throw std::logic_error("Object callback does not exist.");
	m_data.fn(object);
}

Node& Node::operator+=(int data) noexcept
{
	m_data.i += data;
	return *this;
}

Node& Node::operator-=(int data) noexcept
{
	m_data.i -= data;
	return *this;
}

Node& Node::operator*=(int data) noexcept
{
	m_data.i *= data;
	return *this;
}

Node& Node::operator/=(int data) noexcept
{
	m_data.i /= data;
	return *this;
}

Node& Node::operator%=(int data) noexcept
{
	m_data.i %= data;
	return *this;
}

Node& Node::operator&=(Bus signal) noexcept
{
	m_data.b &= signal;
	return *this;
}

Node& Node::operator|=(Bus signal) noexcept
{
	m_data.b |= signal;
	return *this;
}

Node& Node::operator^=(Bus signal) noexcept
{
	m_data.b ^= signal;
	return *this;
}

Node operator+(Node lhs, Node rhs) noexcept
{
	Node retval = lhs;
	retval += int(rhs);
	return retval;
}

Node operator-(Node lhs, Node rhs) noexcept
{
	Node retval = lhs;
	retval -= int(rhs);
	return retval;
}

Node operator*(Node lhs, Node rhs) noexcept
{
	Node retval = lhs;
	retval *= int(rhs);
	return retval;
}

Node operator/(Node lhs, Node rhs) noexcept
{
	Node retval = lhs;
	retval /= int(rhs);
	return retval;
}

Node operator%(Node lhs, Node rhs) noexcept
{
	Node retval = lhs;
	retval %= int(rhs);
	return retval;
}

Node operator&(Node lhs, Node rhs) noexcept
{
	Node retval = lhs;
	retval &= Bus(rhs);
	return retval;
}

Node operator|(Node lhs, Node rhs) noexcept
{
	Node retval = lhs;
	retval |= Bus(rhs);
	return retval;
}

Node operator^(Node lhs, Node rhs) noexcept
{
	Node retval = lhs;
	retval ^= Bus(rhs);
	return retval;
}

}