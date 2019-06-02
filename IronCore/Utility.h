#pragma once

namespace iron
{

class ObjectView;

using LayoutCallback = void(ObjectView);

template<typename T>
struct Point2
{
	Point2() noexcept = default;
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

}