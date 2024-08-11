#pragma once

#include <rt/common.hpp>
#include <rt/components/component.hpp>
#include <rt/render_targets/render_target.hpp>

// BoxDesc describes the boxes attributes.
// It is implemented using the builder-pattern so that it can be easier used, e.g.
// 
//     BoxDesc().set_padding(5).set_margin(5)
// 
// The default constructor populates the attributes with the default values, and the user
// must just chain the provided methods to change them.
// This way the BoxDesc can be completely constructed and set as a function/method parameter in one line.
// This is important because we want that the user can construct complete interfaces without intermediate variables, e.g.
// 
//		auto* body = new Body(Size(800, 600),
//  		new VStack({
//              new Box(BoxDesc().padding(5).border_thickness(2),
//					new Text(my_font, "Hello")
//              ),
//				new Text(my_font, "World!"),
//				new HStack({
//					new Image("my_image0.png"),
//					new Image("my_image1.png")
//				})
//			})
//		);
// 
// This is also the reason why we do not use unique_ptr yet, it complicates the construction a lot.
// It is a trade off between usability and security at the moment, until a solution is found.
// It is definitely intended to use std::unique_ptr to give ownership of a component to a parent component.
// But there is no implicit conversion from std::unique_ptr to *.

class BoxDesc {
public:
	uint32_t m_padding = 0;

	uint32_t m_border_thickness = 0;

	Color m_border_color = Color(0, 0, 0, 255);

	uint32_t m_margin = 0;

	Color m_background_color = Color(0, 0, 0, 0);


	RT_INLINE BoxDesc() = default;

	RT_INLINE BoxDesc(const BoxDesc&) noexcept = default;

	RT_INLINE BoxDesc(BoxDesc&&) noexcept = default;

	RT_INLINE ~BoxDesc() noexcept = default;

	RT_INLINE BoxDesc& operator = (const BoxDesc& rhs) noexcept = default;

	RT_INLINE BoxDesc& operator = (BoxDesc&&) noexcept = default;

	RT_INLINE BoxDesc& padding(uint32_t padding) noexcept {
		m_padding = padding;
		return (*this);
	}

	RT_INLINE BoxDesc& border_thickness(uint32_t border_thickness) noexcept {
		m_border_thickness = border_thickness;
		return (*this);
	}

	RT_INLINE BoxDesc& border_color(const Color& border_color) noexcept {
		m_border_color = border_color;
		return (*this);
	}

	RT_INLINE BoxDesc& margin(uint32_t margin) noexcept {
		m_margin = margin;
		return (*this);
	}

	RT_INLINE BoxDesc& background_color(const Color& background_color) noexcept {
		m_background_color = background_color;
		return (*this);
	}
};

// The box class is similar to the HTML box-model.
// A box may have a padding, a border and/or a margin.
// Currently padding and margin can only specified for all sides the same.
// In the future it should be possible to specify padding and margin for each side individually.
class Box : public Component {
public:
	RT_INLINE Box() : m_content(nullptr) {

	}
	
	RT_INLINE Box(const BoxDesc& desc, Component* content) noexcept : m_desc(desc), m_content(content) {
		m_content->set_parent(this);
	}

	Box(const Box&) = delete;

	Box(Box&&) = delete;

	virtual ~Box() noexcept;

	Box& operator = (const Box&) = delete;

	Box& operator = (Box&&) = delete;

	Size get_requested_size(const Size& provided_size) noexcept override;

	void layout(const Rect& provided_rect) noexcept override;

	void render(RenderTarget& rt) noexcept override;

	void animate() noexcept override;

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

	RT_INLINE Component* set_content(Component* content) noexcept {
		m_content = content;
		return m_content;
	}

	RT_INLINE void set_desc(const BoxDesc& desc) noexcept {
		m_desc = desc;
	}

	RT_INLINE const Component* get_content() const noexcept {
		return m_content;
	}

	RT_INLINE Component* get_content() noexcept {
		return m_content;
	}

	RT_INLINE const BoxDesc& get_desc() const noexcept {
		return m_desc;
	}

private:
	BoxDesc m_desc;

	Component* m_content;
};