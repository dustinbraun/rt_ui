#pragma once

#include <rt/common.hpp>
#include <rt/components/component.hpp>

class RenderTarget;

class HAlignR final : public Component {
public:
	RT_INLINE HAlignR() : m_content(nullptr) {

	}

	RT_INLINE HAlignR(Component* content) : m_content(content) {
		if (content) {
			content->set_parent(this);
		}
	}

	HAlignR(const HAlignR&) = delete;

	HAlignR(HAlignR&&) = delete;

	virtual ~HAlignR() noexcept;

	HAlignR& operator = (const HAlignR&) = delete;

	HAlignR& operator = (HAlignR&&) = delete;

	Size get_requested_size(const Size& provided_size) noexcept override;

	void layout(const Rect& provided_rect) noexcept override;

	void render(RenderTarget& rt) noexcept override;

	void animate() noexcept override {
		if (m_content) {
			m_content->animate();
		}
	}

	bool hit(const Point& point) noexcept override {
		if (m_rect.contains_point(point)) {
			if (m_content) {
				if (m_content->hit(point)) {
					return true;
				}
			}
			on_hit();
			return true;
		}
		return false;
	}

	Component* cursor_move(const Point& point) noexcept override {
		if (m_rect.contains_point(point)) {
			if (m_content) {
				if (auto* catched = m_content->cursor_move(point); catched) {
					return catched;
				}
			}
			return this;
		}
		return nullptr;
	}

private:
	Component* m_content;
};