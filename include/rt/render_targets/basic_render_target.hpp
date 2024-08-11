#pragma once

#include <rt/render_targets/render_target.hpp>

class BasicRenderTarget final : public RenderTarget {
public:
	static BasicRenderTarget from(const char* path) noexcept;

	BasicRenderTarget(const Size& size) noexcept;

	BasicRenderTarget(const BasicRenderTarget&) = delete;

	BasicRenderTarget(BasicRenderTarget&& rhs) noexcept : RenderTarget(rhs.m_size), m_data(rhs.m_data) {
		rhs.m_data = nullptr;
	}

	~BasicRenderTarget() noexcept;

	// We need this one for test-cases.
	bool operator == (const BasicRenderTarget& rhs) const noexcept;

	RT_INLINE bool operator != (const BasicRenderTarget& rhs) const noexcept {
		return !((*this) == rhs);
	}

	RT_INLINE const Color* get_data() const noexcept {
		return m_data;
	}

	void clear(const Color& color) noexcept override;

	void render_rect(const Rect& rect, const Color& color) noexcept override;

	void render_point(const Point& point, const Color& color) noexcept override;

	void render_image(const Rect& rect, const Color* image) noexcept override;

	void render_bitmap(const Rect& rect, const uint8_t* bitmap) noexcept override;

	void to(const char* path) noexcept;

private:
	Color* m_data;


	BasicRenderTarget(const Size& size, Color* data) : RenderTarget(size), m_data(data) {

	}


	void render_tborder(
		const Rect& content_rect,
		uint32_t border_thickness,
		const Color& border_color
	) noexcept;

	void render_lborder(
		const Rect& content_rect,
		uint32_t border_thickness,
		const Color& border_color
	) noexcept;

	void render_bborder(
		const Rect& content_rect,
		uint32_t border_thickness,
		const Color& border_color
	) noexcept;

	void render_rborder(
		const Rect& content_rect,
		uint32_t border_thickness,
		const Color& border_color
	) noexcept;

	void render_border(
		const Rect& content_rect,
		uint32_t border_thickness,
		const Color& border_color
	) noexcept;
};