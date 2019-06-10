#pragma once

namespace iron
{

class ObjectView;

using CircuitCallback = void(ObjectView);

enum class Rotation
{
	None,
	Clockwise,
	Flip,
	CounterClockwise
};

template<typename T>
struct Point2
{
	Point2() noexcept
		: x(0), y(0)
	{}

	Point2(T theX, T theY) noexcept
		: x(theX), y(theY)
	{}

	template<typename U>
	Point2(const Point2<U>& src) noexcept
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
	{}

	T x;
	T y;

	Point2<T>& operator+=(const Point2<T>& data) noexcept
	{
		x += data.x;
		y += data.y;
		return *this;
	}

	Point2<T>& operator-=(const Point2<T>& data) noexcept
	{
		x -= data.x;
		y -= data.y;
		return *this;
	}

	Point2<T>& rotate(Rotation amount, const Point2<T> center = Point2<T>(0, 0)) noexcept
	{
		*this = rotation(amount, center);
		return *this;
	}

	Point2<T> rotation(Rotation amount, const Point2<T> center = Point2<T>(0, 0)) const noexcept
	{
		return (*this - center).rotationAboutOrigin(amount) + center;
	}

private:
	
	Point2<T> rotationAboutOrigin(Rotation amount) const noexcept
	{
		switch (amount)
		{
		case Rotation::None:
			return *this;
		case Rotation::Clockwise:
			return Point2<T>(y, -x);
		case Rotation::Flip:
			return Point2<T>(-x, -y);
		case Rotation::CounterClockwise:
			return Point2<T>(-y, x);
		}
		//This should never happen, but is not worth throwing exception for.
		return Point2<T>(0, 0);
	}
};

template<typename T>
Point2<T> operator-(const Point2<T>& data) noexcept
{
	Point2<T> retval;
	retval.x = -data.x;
	retval.y = -data.y;
	return retval;
}

template<typename T>
Point2<T> operator+(const Point2<T>& lhs, const Point2<T>& rhs) noexcept
{
	Point2<T> retval = lhs;
	retval += rhs;
	return retval;
}

template<typename T>
Point2<T> operator-(const Point2<T>& lhs, const Point2<T>& rhs) noexcept
{
	Point2<T> retval = lhs;
	retval -= rhs;
	return retval;
}

using Point2i = Point2<int>;
using Point2u = Point2<unsigned>;
using Point2f = Point2<float>;

struct Pin
{
	Point2i location;
	enum class Direction : short
	{
		Unassigned,
		In,
		Out,
		Bidir
	} direction = Direction::Unassigned;
	short width = 1;
	int connection = -1;
};

}