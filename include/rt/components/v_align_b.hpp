#pragma once

#include <rt/common.hpp>
#include <rt/components/component.hpp>

class RenderTarget;

class VAlignB final : public Component {
public:
	RT_INLINE VAlignB(Component* content) noexcept : m_content(content) {

	}

	VAlignB(const VAlignB&) = delete;

	VAlignB(VAlignB&&) = delete;

	~VAlignB() noexcept;

	VAlignB& operator = (const VAlignB&) = delete;

	VAlignB& operator = (VAlignB&&) = delete;

	Size get_requested_size(const Size& provided_size) noexcept override;

	void layout(const Rect& provided_rect) noexcept override;

	void render(RenderTarget& rt) noexcept override;

private:
	Component* m_content;
};