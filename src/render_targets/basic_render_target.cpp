#include <rt/render_targets/basic_render_target.hpp>

#include "../stb/stb_image.h"
#include "../stb/stb_image_write.h"

BasicRenderTarget BasicRenderTarget::from(const char* path) noexcept {
	int x = 0;
	int y = 0;
	int n = 0;
	Color* data = reinterpret_cast<Color*>(stbi_load(path, &x, &y, &n, 4));
	if (!data) {
		panic("Render target can not be loaded."); // ToDo: include path.
	}
	return BasicRenderTarget(Size(x, y), data);
}

BasicRenderTarget::BasicRenderTarget(const Size& size) noexcept : RenderTarget(size), m_data(new (std::nothrow) Color[size.get_area()]) {
	if (!m_data) {
		panic(PANIC_REASON_OUT_OF_MANA);
	}
}

BasicRenderTarget::~BasicRenderTarget() noexcept {
	if (m_data) {
		delete[] m_data;
	}
}

bool BasicRenderTarget::operator == (const BasicRenderTarget& rhs) const noexcept {
	if (m_size == rhs.m_size) {
		if (std::memcmp(m_data, rhs.m_data, m_size.get_area()) == 0) {
			return true;
		}
	}
	return false;
}

void BasicRenderTarget::clear(const Color& color) noexcept {
	const auto count = m_size.get_area();
	for (uint32_t i = 0; i < count; ++i) {
		m_data[i] = color;
	}
}

void BasicRenderTarget::render_rect(const Rect& rect, const Color& color) noexcept {
	Rect clamped = rect;
	clamped.clamp(m_restriction);
	for (int32_t y = clamped.m_min.m_y; y < clamped.m_max.m_y; ++y) {
		for (int32_t x = clamped.m_min.m_x; x < clamped.m_max.m_x; ++x) {
			m_data[y * m_size.m_x + x] = color;
		}
	}
}

void BasicRenderTarget::render_point(const Point& point, const Color& color) noexcept {
	if (m_restriction.contains_point(point)) {
		m_data[point.m_y * m_size.m_x + point.m_x] = color;
	}
}

void BasicRenderTarget::render_bitmap(const Rect& rect, const uint8_t* bitmap) noexcept {
	auto size = rect.get_size();
	for (int32_t y = 0; y < (int32_t)size.m_y; ++y) {
		for (int32_t x = 0; x < (int32_t)size.m_x; ++x) {
			auto strength = bitmap[y * size.m_x + x];
			render_point(Point(rect.m_min.m_x + x, rect.m_min.m_y + y), Color(strength, strength, strength, 255));
		}
	}
}

void BasicRenderTarget::render_image(const Rect& rect, const Color* image) noexcept {
	auto size = rect.get_size();
	for (int32_t y = 0; y < (int32_t)size.m_y; ++y) {
		for (int32_t x = 0; x < (int32_t)size.m_x; ++x) {
			auto strength = image[y * size.m_x + x];
			render_point(Point(rect.m_min.m_x + x, rect.m_min.m_y + y), image[y * size.m_x + x]);
		}
	}
}

void BasicRenderTarget::render_border(const Rect& content_rect, uint32_t border_thickness, const Color& border_color) noexcept {
	render_tborder(content_rect, border_thickness, border_color);
	render_lborder(content_rect, border_thickness, border_color);
	render_bborder(content_rect, border_thickness, border_color);
	render_rborder(content_rect, border_thickness, border_color);
}

void BasicRenderTarget::render_tborder(const Rect& content_rect, uint32_t border_thickness, const Color& border_color) noexcept {
	Rect rect;
	rect.m_min.m_x = content_rect.m_min.m_x - border_thickness;
	rect.m_min.m_y = content_rect.m_min.m_y - border_thickness;
	rect.m_max.m_x = content_rect.m_max.m_x + border_thickness;
	rect.m_max.m_y = content_rect.m_min.m_y;
	render_rect(rect, border_color);
}

void BasicRenderTarget::render_lborder(const Rect& content_rect, uint32_t border_thickness, const Color& border_color) noexcept {
	Rect rect;
	rect.m_min.m_x = content_rect.m_min.m_x - border_thickness;
	rect.m_min.m_y = content_rect.m_min.m_y;
	rect.m_max.m_x = content_rect.m_min.m_x;
	rect.m_max.m_y = content_rect.m_max.m_y;
	render_rect(rect, border_color);
}

void BasicRenderTarget::render_bborder(const Rect& content_rect, uint32_t border_thickness, const Color& border_color) noexcept {
	Rect rect;
	rect.m_min.m_x = content_rect.m_min.m_x - border_thickness;
	rect.m_min.m_y = content_rect.m_max.m_y;
	rect.m_max.m_x = content_rect.m_max.m_x + border_thickness;
	rect.m_max.m_y = content_rect.m_max.m_y + border_thickness;
	render_rect(rect, border_color);
}

void BasicRenderTarget::render_rborder(const Rect& content_rect, uint32_t border_thickness, const Color& border_color) noexcept {
	Rect rect;
	rect.m_min.m_x = content_rect.m_max.m_x;
	rect.m_min.m_y = content_rect.m_min.m_y;
	rect.m_max.m_x = content_rect.m_max.m_x + border_thickness;
	rect.m_max.m_y = content_rect.m_max.m_y;
	render_rect(rect, border_color);
}

void BasicRenderTarget::to(const char* path) noexcept {
	if (stbi_write_png(path, m_size.m_x, m_size.m_y, 4, (const void*)m_data, m_size.m_x*4) == 0) {
		panic("Can not save render-target.");
	}
}