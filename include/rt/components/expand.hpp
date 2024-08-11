#pragma once

#include <rt/common.hpp>
#include <rt/components/component.hpp>

class ExpandDesc {
public:
	bool m_expand_h;

	bool m_expand_v;


	RT_INLINE ExpandDesc() noexcept : m_expand_h(false), m_expand_v(false) {

	}

	RT_INLINE ExpandDesc(bool expand_h, bool expand_v) noexcept : m_expand_h(expand_h), m_expand_v(expand_v) {

	}

	RT_INLINE ExpandDesc(const ExpandDesc&) = default;

	RT_INLINE ExpandDesc(ExpandDesc&&) = default;

	RT_INLINE ~ExpandDesc() = default;

	RT_INLINE ExpandDesc& operator = (const ExpandDesc&) = default;
	
	RT_INLINE ExpandDesc& operator = (ExpandDesc&&) = default;

	RT_INLINE bool operator == (const ExpandDesc& rhs) const noexcept {
		return (m_expand_h == rhs.m_expand_h) && (m_expand_v == rhs.m_expand_v);
	}

	RT_INLINE bool operator != (const ExpandDesc& rhs) const noexcept {
		return (m_expand_h != rhs.m_expand_h) || (m_expand_v != rhs.m_expand_v);
	}

	// Okay, I am at this moment not 100% sure if its better or worse to provide default values here...^^
	RT_INLINE ExpandDesc& expand_h(bool expand_h = true) noexcept {
		m_expand_h = expand_h;
		return (*this);
	}

	RT_INLINE ExpandDesc& expand_v(bool expand_v = true) noexcept {
		m_expand_v = expand_v;
		return (*this);
	}
};

// The expand component is used to tell the content of the expand component
// to expand to the provided rect horizontally and/or vertically.
// ToDo: Not implemented yet.
class Expand : public Component {
public:
	RT_INLINE Expand(const ExpandDesc& desc, Component* content) noexcept : m_desc(desc), m_content(content) {

	}

	Expand(const Expand&) = delete;

	Expand(Expand&&) = delete;

	RT_INLINE ~Expand() noexcept = default;

	Expand& operator = (const Expand&) = delete;

	Expand& operator = (Expand&&) = delete;

	RT_INLINE Size get_requested_size(const Size& provided_size) noexcept override {
		// ToDo
		not_implemented();
	}

	RT_INLINE void layout(const Rect& provided_rect) noexcept override {
		// ToDo
		not_implemented();
	}

	RT_INLINE void render(RenderTarget& rt) noexcept override {
		// ToDo
		not_implemented();
	}

private:
	ExpandDesc m_desc;

	Component* m_content;
};