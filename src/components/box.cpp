#include <rt/components/box.hpp>
#include <rt/render_targets/render_target.hpp>


Box::~Box() noexcept {
	if (m_content) {
		delete m_content;
	}
}
Size Box::get_requested_size(const Size& provided_size) noexcept {
	if (m_content) {
		Size provided_content_size(
			provided_size.m_x - 2 * (m_desc.m_border_thickness + m_desc.m_padding + m_desc.m_margin),
			provided_size.m_y - 2 * (m_desc.m_border_thickness + m_desc.m_padding + m_desc.m_margin)
		);
		auto requested_content_size = m_content->get_requested_size(provided_content_size);
		return Size(
			requested_content_size.m_x + 2 * (m_desc.m_border_thickness + m_desc.m_padding + m_desc.m_margin),
			requested_content_size.m_y + 2 * (m_desc.m_border_thickness + m_desc.m_padding + m_desc.m_margin)
		);
	}
	else {
		return Size(
			2 * (m_desc.m_padding + m_desc.m_border_thickness + m_desc.m_margin),
			2 * (m_desc.m_padding + m_desc.m_border_thickness + m_desc.m_margin)
		);
	}
}

void Box::layout(const Rect& provided_rect) noexcept {
	if (m_content) {
		Rect provided_content_rect(
			provided_rect.m_min.m_x + m_desc.m_border_thickness + m_desc.m_padding + m_desc.m_margin,
			provided_rect.m_min.m_y + m_desc.m_border_thickness + m_desc.m_padding + m_desc.m_margin,
			provided_rect.m_max.m_x - m_desc.m_border_thickness - m_desc.m_padding - m_desc.m_margin,
			provided_rect.m_max.m_y - m_desc.m_border_thickness - m_desc.m_padding - m_desc.m_margin
		);
		m_content->layout(provided_content_rect);
		const Rect& content_rect = m_content->get_rect();
		m_rect.m_min.m_x = content_rect.m_min.m_x - m_desc.m_border_thickness - m_desc.m_padding - m_desc.m_margin;
		m_rect.m_min.m_y = content_rect.m_min.m_y - m_desc.m_border_thickness - m_desc.m_padding - m_desc.m_margin;
		m_rect.m_max.m_x = content_rect.m_max.m_x + m_desc.m_border_thickness + m_desc.m_padding + m_desc.m_margin;
		m_rect.m_max.m_y = content_rect.m_max.m_y + m_desc.m_border_thickness + m_desc.m_padding + m_desc.m_margin;
	}
	else {
		m_rect.m_min.m_x = provided_rect.m_min.m_x;
		m_rect.m_min.m_y = provided_rect.m_min.m_y;
		m_rect.m_max.m_x = provided_rect.m_min.m_x + 2 * (m_desc.m_padding + m_desc.m_border_thickness + m_desc.m_margin);
		m_rect.m_max.m_y = provided_rect.m_min.m_y + 2 * (m_desc.m_padding + m_desc.m_border_thickness + m_desc.m_margin);
	}
}

void Box::render(RenderTarget& rt) noexcept {
	Rect border_rect(
		m_rect.m_min.m_x + m_desc.m_padding + m_desc.m_border_thickness,
		m_rect.m_min.m_y + m_desc.m_padding + m_desc.m_border_thickness,
		m_rect.m_max.m_x - m_desc.m_padding - m_desc.m_border_thickness,
		m_rect.m_max.m_y - m_desc.m_padding - m_desc.m_border_thickness
	);
	if (m_desc.m_border_thickness > 0) {
		rt.render_border(border_rect, m_desc.m_border_thickness, m_desc.m_border_color);
	}
	if (m_desc.m_background_color.m_a > 0) {
		rt.render_rect(border_rect, m_desc.m_background_color);
	}
	if (m_content) {
		m_content->render(rt);
	}
}

void Box::animate() noexcept {
	on_animate();
	if (m_content) {
		m_content->animate();
	}
}