#include <rt/components/v_stack.hpp>

VStack::~VStack() noexcept {
	for (auto* content : m_contents) {
		if (content) {
			delete content;
		}
	}
}

Size VStack::get_requested_size(const Size& provided_size) noexcept {
	Size requested_size(0, 0);
	auto provided_content_size = provided_size;
	for (auto* content : m_contents) {
		if (content) {
			auto requested_content_size = content->get_requested_size(provided_content_size);
			if (requested_content_size.m_x > requested_size.m_x) {
				requested_size.m_x = requested_content_size.m_x;
			}
			requested_size.m_y += requested_content_size.m_y;
			provided_content_size.m_y -= requested_content_size.m_y;
		}
	}
	return requested_size;
}

void VStack::layout(const Rect& provided_rect) noexcept {
	auto requested_content_size = get_requested_size(provided_rect.get_size());
	auto provided_content_rect = provided_rect;
	provided_content_rect.m_max.m_x = provided_content_rect.m_min.m_x + requested_content_size.m_x;
	for (auto* content : m_contents) {
		if (content) {
			content->layout(provided_content_rect);
			provided_content_rect.m_min.m_y = content->get_rect().m_max.m_y;
		}
	}
	m_rect.m_min.m_x = provided_rect.m_min.m_x;
	m_rect.m_min.m_y = provided_rect.m_min.m_y;
	m_rect.m_max.m_x = provided_rect.m_min.m_x + requested_content_size.m_x;
	m_rect.m_max.m_y = provided_content_rect.m_min.m_y;
}

void VStack::render(RenderTarget& rt) noexcept {
	for (auto* content : m_contents) {
		if (content != nullptr) {
			content->render(rt);
		}
	}
}

void VStack::animate() noexcept {
	for (auto* content : m_contents) {
		if (content) {
			content->animate();
		}
	}
}