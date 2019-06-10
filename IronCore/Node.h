#pragma once

#include "Bus.h"
#include "Utility.h"

namespace iron
{

class Node
{
public:

	Node() noexcept = default;

	explicit Node(int data) noexcept;
	explicit Node(CircuitCallback* function) noexcept;
	explicit Node(Bus signal) noexcept;

	Node& operator=(int data) noexcept;
	Node& operator=(Bus signal) noexcept;

	explicit operator int() const noexcept;
	explicit operator Bus() const noexcept;

	void operator()(const ObjectView& object); //CANNOT be noexcept

	//Integer operations
	Node& operator+=(int data) noexcept;
	Node& operator-=(int data) noexcept;
	Node& operator*=(int data) noexcept;
	Node& operator/=(int data) noexcept;
	Node& operator%=(int data) noexcept;

	//Bus operations
	Node& operator&=(Bus signal) noexcept;
	Node& operator|=(Bus signal) noexcept;
	Node& operator^=(Bus signal) noexcept;

private:
	union
	{
		CircuitCallback* fn = nullptr;
		int i;
		Bus b;
	} m_data;
};

Node operator+(Node lhs, Node rhs) noexcept;
Node operator-(Node lhs, Node rhs) noexcept;
Node operator*(Node lhs, Node rhs) noexcept;
Node operator/(Node lhs, Node rhs) noexcept;
Node operator%(Node lhs, Node rhs) noexcept;

Node operator&(Node lhs, Node rhs) noexcept;
Node operator|(Node lhs, Node rhs) noexcept;
Node operator^(Node lhs, Node rhs) noexcept;

}