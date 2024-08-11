#pragma once

#include <cstdint>

#include <rt/common.hpp>

class Point final {
public:
	int32_t m_x;

	int32_t m_y;


	RT_INLINE Point() noexcept : m_x(0), m_y(0) {

	}

	RT_INLINE Point(int32_t x, int32_t y) noexcept : m_x(x), m_y(y) {

	}

	RT_INLINE Point(const Point& rhs) noexcept = default;

	RT_INLINE Point(Point&& rhs) noexcept = default;

	RT_INLINE ~Point() noexcept = default;

	RT_INLINE Point& operator = (const Point& rhs) noexcept = default;

	RT_INLINE Point& operator = (Point&& rhs) noexcept = default;

	RT_INLINE Point& operator += (const Point& rhs) noexcept {
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		return (*this);
	}

	RT_INLINE Point& operator -= (const Point& rhs) noexcept {
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		return (*this);
	}

	RT_INLINE Point operator + (const Point& rhs) const noexcept {
		return Point(
			m_x + rhs.m_x,
			m_y + rhs.m_y
		);
	}

	RT_INLINE Point operator - (const Point& rhs) const noexcept {
		return Point(
			m_x - rhs.m_x,
			m_y - rhs.m_y
		);
	}

	RT_INLINE bool operator == (const Point& rhs)  const noexcept {
		return (m_x == rhs.m_x) && (m_y == rhs.m_y);
	}

	RT_INLINE bool operator != (const Point& rhs) const noexcept {
		return (m_x != rhs.m_x) || (m_y != rhs.m_y);
	}
};