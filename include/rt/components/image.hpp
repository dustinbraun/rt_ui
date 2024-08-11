#pragma once

#include <rt/common.hpp>
#include <rt/components/component.hpp>
#include <rt/math/color.hpp>

class RenderTarget;

class Image : public Component {
public:
	// ToDo: Here we have a constructor which might fail.
	// I am not sure yet if i will use exceptions or some rust-like result class with named constructors.
	// For now we panic...
	// Or we will do the error handling completely different here.
	// It would be great if we always generate a valid interface but filled with dummy components in case some error happened.
	// In this case, the user immediately sees where the error is by watching the resulting interface!
	Image(const char* path) noexcept;

	Image(const Image&) = delete;

	Image(Image&&) = delete;

	virtual RT_INLINE ~Image() = default;

	Image& operator = (const Image&) = delete;

	Image& operator = (Image&&) = delete;

	Size get_requested_size(const Size& provided_size) noexcept override;

	void layout(const Rect& provided_rect) noexcept override;

	void render(RenderTarget& rt) noexcept;

	void animate() noexcept override {
		on_animate();
	}

	bool hit(const Point& point) noexcept override {
		if (m_rect.contains_point(point)) {
			on_hit();
			return true;
		}
		return false;
	}

	Component* cursor_move(const Point& point) noexcept override {
		if (m_rect.contains_point(point)) {
			on_cursor_move(point);
			return this;
		}
		return nullptr;
	}

	RT_INLINE void resize(const Size& size) noexcept {
		// ToDo: Scaling will be supported in the future.
		m_size = size;
	}

private:
	Size m_size;

	Color* m_data;
};