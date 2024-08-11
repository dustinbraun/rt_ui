#pragma once

#include <vector>

#include <rt/common.hpp>
#include <rt/components/component.hpp>

class RenderTarget;

class VStack : public Component {
public:
	RT_INLINE VStack() = default;

	RT_INLINE VStack(std::vector<Component*>&& contents) noexcept : m_contents(std::move(contents)) {

	}

	VStack(const VStack&) = delete;

	VStack(VStack&&) = delete;

	virtual ~VStack() noexcept;

	VStack& operator = (const VStack&) = delete;

	VStack& operator = (VStack&&) = delete;

	RT_INLINE Component* push(Component* content) noexcept {
		return (Component*)m_contents.emplace_back(content);
	}

	Size get_requested_size(const Size& provided_size) noexcept override;

	void layout(const Rect& provided_rect) noexcept override;

	void render(RenderTarget& rt) noexcept override;

	void animate() noexcept override;

	bool hit(const Point& point) noexcept override {
		if (m_rect.contains_point(point)) {
			for (auto* content : m_contents) {
				if (content) {
					if (content->hit(point)) {
						return true;
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
			for (auto* content : m_contents) {
				if (content) {
					if (auto* catched = content->cursor_move(point); catched) {
						return catched;
					}
				}
			}
			return this;
		}
		return nullptr;
	}

private:
	std::vector<Component*> m_contents;
};