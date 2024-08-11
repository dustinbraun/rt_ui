#pragma once

#include <rt/common.hpp>
#include <rt/components/component.hpp>
#include <rt/render_targets/render_target.hpp>

class Body final {
public:
	// ToDo: use unique_ptr<Component>, but the problem is that there is not implicit conversion
	// from unique_ptr to pointer, so the user must write the unique_ptr<Component*> out each time
	// a component is provided to a parent.
	// The benefit is that the user can immediately see that a component takes ownership.
	RT_INLINE Body(const Size& size, Component* content) : m_size(size), m_content(content) {

	}

	RT_INLINE void layout() {
		if (m_content) {
			m_content->layout(Rect(0, 0, m_size.m_x, m_size.m_y));
		}
	}

	RT_INLINE void render(RenderTarget& rt) {
		if (m_content) {
			m_content->render(rt);
		}
	}

	RT_INLINE void animate() {
		if (m_content) {
			m_content->animate();
		}
	}

	RT_INLINE Component* get_content() {
		return m_content;
	}

	RT_INLINE void hit(const Point& point) {
		if (m_content) {
			m_content->hit(point);
		}
	}

	RT_INLINE void cursor_move(const Point& point) noexcept {
		if (m_content) {
			if (auto* catched = m_content->cursor_move(point); catched) {
				if (catched != m_hoverd_component) {
					if (m_hoverd_component != nullptr) {
						m_hoverd_component->on_cursor_leave();
					}
					if (catched != nullptr) {
						catched->on_cursor_enter();
					}
					m_hoverd_component = catched;
				}
			}
		}
	}

private:
	Size m_size;

	Component* m_content;

	Component* m_hoverd_component = nullptr;
};