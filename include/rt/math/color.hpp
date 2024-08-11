#pragma once

#include <cstdint>

#include <rt/common.hpp>

class Color final {
public:
	uint8_t m_r;

	uint8_t m_g;

	uint8_t m_b;

	uint8_t m_a;


	// ToDo: It might be better to put the default colors in a seperate namespace.
	// In case the coder writes Color:: or color-> or color., it's IDE autocompetion will be flooded with names.
	// The interface of every class should be as small as possible so that the user can directly see what is possible
	// by checking the IDE's autocompletion.
	static RT_INLINE Color black() noexcept {
		return Color(
			0,
			0,
			0,
			255
		);
	}

	static RT_INLINE Color blue() noexcept {
		return Color(
			0,
			0,
			255,
			255
		);
	}

	static RT_INLINE Color green() noexcept {
		return Color(
			0,
			255,
			0,
			255
		);
	}

	static RT_INLINE Color red() noexcept {
		return Color(
			255,
			0,
			0,
			255
		);
	}

	static RT_INLINE Color white() noexcept {
		return Color(
			255,
			0,
			0,
			255
		);
	}

	RT_INLINE Color() noexcept : m_b(0), m_g(0), m_r(0), m_a(255) {

	}

	// ToDo: Using a default value allows the coder to see the default value immediately and does
	// not need to guess or take the documentation.
	RT_INLINE Color(uint8_t r, uint8_t g, uint8_t b) noexcept : m_r(r), m_g(g), m_b(b), m_a(255) {

	}

	RT_INLINE Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept : m_r(r), m_g(g), m_b(b), m_a(a) {

	}

	RT_INLINE Color(const Color&) noexcept = default;

	RT_INLINE Color(Color&&) noexcept = default;

	RT_INLINE ~Color() noexcept = default;

	RT_INLINE Color& operator = (const Color& rhs) noexcept = default;

	RT_INLINE Color& operator = (Color&& rhs) noexcept = default;

	RT_INLINE bool operator == (const Color& rhs) const noexcept {
		return (m_r == rhs.m_r) && (m_g == rhs.m_g) && (m_b == rhs.m_b) && (m_a == rhs.m_a);
	}

	RT_INLINE bool operator != (const Color& rhs) const noexcept {
		return (m_r != rhs.m_r) || (m_g != rhs.m_g) || (m_b != rhs.m_b) || (m_a == rhs.m_a);
	}
};