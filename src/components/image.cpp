#include "../stb/stb_image.h"

#include <rt/components/image.hpp>
#include <rt/render_targets/render_target.hpp>

Image::Image(const char* path) noexcept : m_data(nullptr) {
	int x = 0;
	int y = 0;
	int n = 0;
	m_data = reinterpret_cast<Color*>(stbi_load(path, &x, &y, &n, 4));
	if (!m_data) {
		panic("Image can not be loaded."); // ToDo: include path.
	}
	m_size.m_x = x;
	m_size.m_y = y;
}

Size Image::get_requested_size(const Size& provided_size) noexcept {
	return Size(
		std::min(m_size.m_x, provided_size.m_x),
		std::min(m_size.m_y, provided_size.m_y)
	);
}

void Image::layout(const Rect& provided_rect) noexcept {
	m_rect.m_min.m_x = provided_rect.m_min.m_x;
	m_rect.m_min.m_y = provided_rect.m_min.m_y;
	m_rect.m_max.m_x = std::min(provided_rect.m_min.m_x + (int32_t)m_size.m_x, provided_rect.m_max.m_x);
	m_rect.m_max.m_y = std::min(provided_rect.m_min.m_y + (int32_t)m_size.m_y, provided_rect.m_max.m_y);
}

void Image::render(RenderTarget& rt) noexcept {
	rt.render_image(m_rect, m_data);
}