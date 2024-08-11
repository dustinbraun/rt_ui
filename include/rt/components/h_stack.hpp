#pragma once

#include <vector>

#include <rt/common.hpp>
#include <rt/components/component.hpp>

class RenderTarget;

class HStack final : public Component {
public:
	RT_INLINE HStack() = default;

	RT_INLINE HStack(std::vector<Component*>&& contents) noexcept : m_contents(std::move(contents)) {
		for (auto* content : m_contents) {
			if (content) {
				content->set_parent_once(this);
			}
		}
	}

	HStack(const HStack&) = delete;

	HStack(HStack&&) = delete;

	virtual ~HStack() noexcept;

	HStack& operator = (const HStack&) = delete;

	HStack& operator = (HStack&&) = delete;

	RT_INLINE Component* push(Component* content) noexcept {
		return (Component*)m_contents.emplace_back(content);
	}

	Size get_requested_size(const Size& provided_size) noexcept override;

	void layout(const Rect& provided_rect) noexcept override;

	void render(RenderTarget& rt) noexcept override;

	void animate() noexcept override;

private:
	std::vector<Component*> m_contents;
};