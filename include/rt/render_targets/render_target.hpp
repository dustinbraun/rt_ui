#pragma once

#include <rt/common.hpp>
#include <rt/math/color.hpp>
#include <rt/math/point.hpp>
#include <rt/math/size.hpp>
#include <rt/math/rect.hpp>

// This is the default render-target for now.
// It will be an abstract interface in the future, where OpenGL, DirectX, ... renderer could be implemented.
// It is not very efficient implemented, its for testing and development now.

// ToDo: RenderTargets should be able to be saved to disk so that they can be used for interface unit tests later.
// The benefit of a pure software renderer is that we can guarantee that the result will always be the same on every machine.
// There are 0 floating point errors or whatever.
// The default software render-target should also be used for testing!
// The render-target will have a very strict specification (as small as possible) and fully unit-tested, so that
// other render-target implementations could use the existing unit tests to verify that the own implementation is correct.

class RenderTarget {
public:
	RT_INLINE RenderTarget(const Size& size) noexcept : m_size(size), m_restriction(0, 0, size.m_x, size.m_y) {

	}

	RT_INLINE virtual ~RenderTarget() noexcept = default;

	virtual void clear(const Color& color) noexcept = 0;

	virtual void render_point(const Point& point, const Color& color) noexcept = 0;

	virtual void render_rect(const Rect& rect, const Color& color) noexcept = 0;

	virtual void render_bitmap(const Rect& rect, const uint8_t* bitmap) noexcept = 0;

	virtual void render_image(const Rect& rect, const Color* image) noexcept = 0;

	virtual void render_border(const Rect& inner_rect, uint32_t border_thickness, const Color& border_color) noexcept = 0;

	RT_INLINE const Size& get_size() const noexcept {
		return m_size;
	}

	RT_INLINE void restriction(const Rect& restriction) noexcept {
		m_restriction = clamp(restriction);
	}

	RT_INLINE const Rect& get_restriction() const noexcept {
		return m_restriction;
	}

	// Clamps the rectangle so that it fits into the render target.
	Rect clamp(const Rect& rect) noexcept;

protected:
	Size m_size;

	Rect m_restriction;
};