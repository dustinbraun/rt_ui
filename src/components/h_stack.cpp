#include <rt/components/h_stack.hpp>

HStack::~HStack() noexcept {
	for (auto* content : m_contents) {
		if (content) {
			delete content;
		}
	}
}

Size HStack::get_requested_size(const Size& provided_size) noexcept {
	Size requested_size(0, 0);
	for (auto* content : m_contents) {
		if (content) {
			auto requested_content_size = content->get_requested_size(provided_size);
			if (requested_content_size.m_y > requested_size.m_y) {
				requested_size.m_y = requested_content_size.m_y;
			}
			requested_size.m_x += requested_content_size.m_x;
		}
	}
	return requested_size;
}

void HStack::layout(const Rect& provided_rect) noexcept {
	auto requested_size = get_requested_size(provided_rect.get_size());
	auto provided_content_rect = provided_rect;
	provided_content_rect.m_max.m_y = provided_content_rect.m_min.m_y + requested_size.m_y;
	for (auto* content : m_contents) {
		if (content) {
			content->layout(provided_content_rect);
			provided_content_rect.m_min.m_x = content->get_rect().m_max.m_x;
		}
	}
	m_rect.m_min.m_x = provided_rect.m_min.m_x;
	m_rect.m_min.m_y = provided_rect.m_min.m_y;
	m_rect.m_max.m_x = provided_content_rect.m_min.m_x;
	m_rect.m_max.m_y = provided_rect.m_min.m_y + requested_size.m_y;
}

void HStack::render(RenderTarget& rt) noexcept {
	for (auto* content : m_contents) {
		if (content) {
			content->render(rt);
		}
	}
}

void HStack::animate() noexcept {
	for (auto* content : m_contents) {
		if (content) {
			content->animate();
		}
	}
}