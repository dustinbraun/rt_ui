#include <rt/components/v_align_b.hpp>

VAlignB::~VAlignB() noexcept {
	if (m_content) {
		delete m_content;
	}
}

Size VAlignB::get_requested_size(const Size& provided_size) noexcept {
	if (m_content) {
		return Size(m_content->get_requested_size(provided_size).m_x, provided_size.m_y);
	}
	else {
		return Size(0, provided_size.m_y);
	}
}

void VAlignB::layout(const Rect& provided_rect) noexcept {
	if (m_content) {
		auto expected_content_size = m_content->get_requested_size(provided_rect.get_size());
		Rect provided_content_rect(
			provided_rect.m_min.m_x,
			provided_rect.m_max.m_y - expected_content_size.m_y,
			provided_rect.m_min.m_x + expected_content_size.m_x,
			provided_rect.m_max.m_y
		);
		m_content->layout(provided_content_rect);
		m_rect = m_content->get_rect();
	}
	else {
		m_rect.m_min.m_x = provided_rect.m_min.m_x;
		m_rect.m_min.m_y = provided_rect.m_max.m_y;
		m_rect.m_max.m_x = provided_rect.m_min.m_x;
		m_rect.m_max.m_y = provided_rect.m_max.m_y;
	}
}

void VAlignB::render(RenderTarget& rt) noexcept {
	if (m_content) {
		m_content->render(rt);
	}
}