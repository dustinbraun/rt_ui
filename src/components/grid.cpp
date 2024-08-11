#pragma once

#include <cassert>

#include <rt/components/grid.hpp>
#include <rt/render_targets/render_target.hpp>

Grid::~Grid() noexcept {
	for (auto& row : m_contents) {
		for (auto* content : row) {
			if (content) {
				delete content;
			}
		}
	}
}

void Grid::push_row(std::vector<Component*>&& contents) noexcept {
	const auto& row = m_contents.emplace_back(std::move(contents));
	for (auto* content : row) {
		if (content) {
			content->set_parent_once(this);
		}
	}
}

Size Grid::get_requested_size(const Size& provided_size) noexcept {
	// ToDo: Use a specialized vector class which uses stack memory until a specific amount of contents
	// and use the heap only for very big grids! Heap allocations can become very expensive when there must
	// be requested new memory from the operation system.
	// We do not want to use class members for this. But the used stack space should not be too big because
	// the get_requested_size() is recursive and grows with interface depth.
	std::vector<uint32_t> v_sizes;
	v_sizes.reserve(m_contents.size());
	std::vector<uint32_t> h_sizes;
	h_sizes.reserve(64);
	get_requested_sizes(provided_size, v_sizes, h_sizes);
	Size requested_size(0, 0);
	for (uint32_t v = 0; v < (uint32_t)v_sizes.size(); ++v) {
		requested_size.m_y += v_sizes[v];
	}
	for (uint32_t h = 0; h < (uint32_t)h_sizes.size(); ++h) {
		requested_size.m_x += h_sizes[h];
	}
	return requested_size;
}

void Grid::layout(const Rect& provided_rect) noexcept {
	std::vector<uint32_t> v_sizes;
	v_sizes.reserve(m_contents.size());
	std::vector<uint32_t> h_sizes;
	h_sizes.reserve(64);
	get_requested_sizes(provided_rect.get_size(), v_sizes, h_sizes);
	Rect provided_content_rect(
		provided_rect.m_min.m_x,
		provided_rect.m_min.m_y,
		0,
		0
	);
	for (uint32_t v = 0; v < (uint32_t)v_sizes.size(); ++v) {
		provided_content_rect.m_min.m_x = provided_rect.m_min.m_x;
		provided_content_rect.m_max.m_y = provided_content_rect.m_min.m_y + v_sizes[v];
		for (uint32_t h = 0; h < (uint32_t)h_sizes.size(); ++h) {
			provided_content_rect.m_max.m_x = provided_content_rect.m_min.m_x + h_sizes[h];
			if (auto* content = m_contents[v][h]; content) {
				content->layout(provided_content_rect);
			}
			provided_content_rect.m_min.m_x = provided_content_rect.m_max.m_x;
		}
		provided_content_rect.m_min.m_y = provided_content_rect.m_max.m_y;
	}
	m_rect.m_min.m_x = provided_rect.m_min.m_x;
	m_rect.m_min.m_y = provided_rect.m_min.m_y;
	m_rect.m_max.m_x = provided_content_rect.m_max.m_x;
	m_rect.m_max.m_y = provided_content_rect.m_max.m_y;
}

void Grid::render(RenderTarget& rt) noexcept {
	for (auto& row : m_contents) {
		for (auto* content : row) {
			if (content) {
				content->render(rt);
			}
		}
	}
}

void Grid::animate() noexcept {
	for (auto& row : m_contents) {
		for (auto* content : row) {
			if (content) {
				content->animate();
			}
		}
	}
}

void Grid::get_requested_sizes(const Size& provided_size, std::vector<uint32_t>& v_sizes, std::vector<uint32_t>& h_sizes) noexcept {
	for (uint32_t v = 0; v < m_contents.size(); ++v) {
		for (uint32_t h = 0; h < m_contents[v].size(); ++h) {
			if (auto* content = m_contents[v][h]; content) {
				auto requested_content_size = content->get_requested_size(provided_size);
				assert((uint32_t)v_sizes.size() >= v);
				if ((uint32_t)v_sizes.size() == v) {
					v_sizes.push_back(requested_content_size.m_y);
				}
				else {
					if (v_sizes[(size_t)v] < requested_content_size.m_y) {
						v_sizes[(size_t)v] = requested_content_size.m_y;
					}
				}
				assert(h_sizes.size() >= h);
				if (h_sizes.size() == h) {
					h_sizes.push_back(requested_content_size.m_x);
				}
				else {
					if (h_sizes[(size_t)h] < requested_content_size.m_x) {
						h_sizes[(size_t)h] = requested_content_size.m_x;
					}
				}
			}
		}
	}
}