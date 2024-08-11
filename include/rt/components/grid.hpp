#pragma once

#include <vector>

#include <rt/common.hpp>
#include <rt/components/component.hpp>

class Rect;
class RenderTarget;
class Size;

class Grid : public Component {
public:
	RT_INLINE Grid() noexcept = default;

	Grid(const Grid&) = delete;

	Grid(Grid&&) = delete;

	virtual ~Grid() noexcept;

	Grid& operator = (const Grid&) = delete;

	Grid& operator = (Grid&&) = delete;

	void push_row(std::vector<Component*>&& contents) noexcept;

	Size get_requested_size(const Size& provided_size) noexcept override;

	void layout(const Rect& provided_rect) noexcept override;

	void render(RenderTarget& rt) noexcept override;

	void animate() noexcept override;

	bool hit(const Point& point) noexcept override {
		if (m_rect.contains_point(point)) {
			for (auto& row : m_contents) {
				for (auto* content : row) {
					if (content) {
						if (content->hit(point)) {
							return true;
						}
					}
				}
			}
			on_hit();
			return true;
		}
		return false;
	}

	Component* cursor_move(const Point& point) noexcept override {
		if (m_rect.contains_point(point)) {
			for (auto& row : m_contents) {
				for (auto* content : row) {
					if (content) {
						if (auto* catched = content->cursor_move(point); catched) {
							return catched;
						}
					}
				}
			}
			return this;
		}
		return nullptr;
	}

private:
	std::vector<std::vector<Component*>> m_contents;


	void get_requested_sizes(const Size& provided_size, std::vector<uint32_t>& v_sizes, std::vector<uint32_t>& h_sizes) noexcept;
};