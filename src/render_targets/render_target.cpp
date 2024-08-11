#include <rt/render_targets/render_target.hpp>

Rect RenderTarget::clamp(const Rect& rect) noexcept {
	// ToDo: What shall happen when the rect is completely outside of the render target?
	Rect clamped = rect;
	if (clamped.m_min.m_x < 0) {
		clamped.m_min.m_x = 0;
	}
	if (clamped.m_min.m_y < 0) {
		clamped.m_min.m_y = 0;
	}
	if (clamped.m_max.m_x > (int32_t)m_size.m_x) {
		clamped.m_max.m_x = (int32_t)m_size.m_x;
	}
	if (clamped.m_max.m_y > (int32_t)m_size.m_y) {
		clamped.m_max.m_y = (int32_t)m_size.m_y;
	}
	return clamped;
}