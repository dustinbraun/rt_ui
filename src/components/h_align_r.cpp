#include <rt/components/h_align_r.hpp>

HAlignR::~HAlignR() noexcept {
	if (m_content) {
		delete m_content;
	}
}

Size HAlignR::get_requested_size(const Size& provided_size) noexcept {
	if (m_content) {
		return m_content->get_requested_size(provided_size);
	}
	else {
		return Size(0, 0);
	}
}

void HAlignR::layout(const Rect& provided_rect) noexcept {
	if (m_content) {
		auto expected_content_size = m_content->get_requested_size(provided_rect.get_size());
		Rect provided_content_rect(
			provided_rect.m_max.m_x - expected_content_size.m_x,
			provided_rect.m_min.m_y,
			provided_rect.m_max.m_x,
			provided_rect.m_min.m_y + expected_content_size.m_y
		);
		m_content->layout(provided_content_rect);
		m_rect = m_content->get_rect();
	}
	else {
		m_rect.m_min.m_x = provided_rect.m_max.m_x;
		m_rect.m_min.m_y = provided_rect.m_min.m_y;
		m_rect.m_max.m_x = provided_rect.m_max.m_x;
		m_rect.m_max.m_y = provided_rect.m_min.m_y;
	}
}

void HAlignR::render(RenderTarget& rt) noexcept {
	if (m_content) {
		m_content->render(rt);
	}
}