#pragma once

#include <cstdint>

#include <rt/common.hpp>

class Size final {
public:
	uint32_t m_x;

	uint32_t m_y;


	RT_INLINE Size() noexcept : m_x(0), m_y(0) {

	}

	RT_INLINE Size(uint32_t x, uint32_t y) noexcept : m_x(x), m_y(y) {

	}

	RT_INLINE Size(const Size& rhs) noexcept = default;

	RT_INLINE Size(Size&&) noexcept = default;

	RT_INLINE ~Size() noexcept = default;

	RT_INLINE Size& operator = (const Size& size) noexcept = default;

	RT_INLINE Size& operator = (Size&& size) noexcept = default;

	RT_INLINE bool operator == (const Size& rhs) const noexcept {
		return (m_x == rhs.m_x) && (m_y == rhs.m_y);
	}

	RT_INLINE bool operator != (const Size& rhs) const noexcept {
		return (m_x != rhs.m_x) || (m_y != rhs.m_y);
	}

	RT_INLINE uint32_t get_area() const noexcept {
		return m_x * m_y;
	}
};