#pragma once

#include <rt/common.hpp>
#include <rt/math/point.hpp>
#include <rt/math/size.hpp>

class Rect final {
public:
	// Exclusive.
	Point m_min;

	// Inclusive.
	Point m_max;


	RT_INLINE Rect() noexcept = default;

	RT_INLINE Rect(const Point& min, const Point& max) noexcept : m_min(min), m_max(max) {

	}

	RT_INLINE Rect(int32_t min_x, int32_t min_y, int32_t max_x, int32_t max_y) noexcept : m_min(min_x, min_y), m_max(max_x, max_y) {

	}

	RT_INLINE Rect(const Size& size) noexcept : m_min(0, size.m_x), m_max(0, size.m_y) {

	}

	RT_INLINE Rect(const Rect&) noexcept = default;

	RT_INLINE Rect(Rect&&) noexcept = default;

	RT_INLINE ~Rect() noexcept = default;

	RT_INLINE Rect& operator = (const Rect&) noexcept = default;

	RT_INLINE Rect& operator = (Rect&&) noexcept = default;

	RT_INLINE bool operator == (const Rect& rhs) const noexcept {
		return (m_min == rhs.m_min) && (m_max == rhs.m_max);
	}

	RT_INLINE bool operator != (const Rect& rhs) const noexcept {
		return (m_min != rhs.m_min) || (m_max != rhs.m_max);
	}

	RT_INLINE bool has_content() const noexcept {
		return (m_min.m_x != m_max.m_x) && (m_min.m_y != m_max.m_y);
	}

	RT_INLINE Size get_size() const noexcept {
		RT_ASSERT(m_min.m_x <= m_max.m_x);
		RT_ASSERT(m_min.m_y <= m_max.m_y);
		return Size(
			m_max.m_x - m_min.m_x,
			m_max.m_y - m_min.m_y
		);
	}

	RT_INLINE bool contains_point(const Point& point) const noexcept {
		// ToDo: Order the comparisons so that the values which fail more probably are tested first.
		// It might be possible that for example max.x is exceeded more often than min.x
		// in usual interface setups.
		return (point.m_x >= m_min.m_x) && (point.m_y >= m_min.m_y) && (point.m_x < m_max.m_x) && (point.m_y < m_max.m_y);
	}

	RT_INLINE void clamp(const Rect& parent_rect) noexcept {
		m_min.m_x = std::max(m_min.m_x, parent_rect.m_min.m_x);
		m_min.m_y = std::max(m_min.m_y, parent_rect.m_min.m_y);
		m_max.m_x = std::min(m_max.m_x, parent_rect.m_max.m_x);
		m_max.m_y = std::min(m_max.m_y, parent_rect.m_max.m_y);
	}
};