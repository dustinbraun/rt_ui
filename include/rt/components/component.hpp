#pragma once

#include <rt/common.hpp>
#include <rt/components/component.hpp>
#include <rt/math/size.hpp>
#include <rt/math/rect.hpp>

class RenderTarget;

// ToDo: optimze multiple get_requested_size() calls by caching the results.
// Overhead:
// - ComponentSizeCache size per component
// - one virtual function more to maybe reset the salt value when it reached UINT32_T max. lets just panic then...
// - Rect and uint32_t comparison VS possible multiple get_requested_size() calls
// The problem is that get_requested_size() is also recursive for some nodes and for very deep UIs, it could become a performance
// problem because the layout() function must be called whenever there was a layout change in the ui, in any node!
// So this method must be as fast as possible, but the benefit is a responsive, dynamic and easy to extent UI.
// We actually dont need a parent pointer yet, lets see how far we get without one^^
class ComponentSizeCache {
public:
	Size m_provided;
	Size m_requested;
	uint32_t m_salt;
};

// The component class is the base class for all UI elements.
// It expects that derived classes override some basic methods so that
// new components can be integrated into the UI.
// Components can be subidived into:
// - Roots, e.g. Body
// - Constraints, e.g. VSize, HSize, ...
// - Leafs, e.g. Image, Text, ...
// - Layouts, e.g. VStack, VAlignB, ...
class Component {
public:
	RT_INLINE Component() : m_parent(nullptr) {

	}

	RT_INLINE Component(const Rect& rect) noexcept : m_rect(rect), m_parent(nullptr) {

	}

	Component(const Component&) = delete;

	Component(Component&&) = delete;

	virtual RT_INLINE ~Component() = default;

	Component& operator = (const Component&) = delete;

	Component& operator = (Component&&) = delete;

	RT_INLINE void set_parent(Component* parent) noexcept {
		m_parent = parent;
	}

	RT_INLINE Component* get_parent() noexcept {
		return m_parent;
	}

	RT_INLINE const Rect& get_rect() const noexcept {
		return m_rect;
	}

	// I give you some size, and you tell me how much you want of it.
	// Some components are less greedy than others.
	virtual Size get_requested_size(const Size& provided_size) noexcept = 0;

	// Realigns the component and its contents if exist.
	// The layout method is some kind of recursive handshake method...
	// It usually first provides its content components some provided size.
	// Then the content components respond with the size they would like to occupy from the provided size. This can be recursive...
	// Then the contents layout function itself becomes called with a provided rectancle where the content should be rendered.
	// The requested size from the content is just a hint for the parent how much space it should give the content.
	// The finally provided rect (and so also the size) can be bigger or smaller than the requested or originally provided size.
	// This way we can avoid some nasty error handling and edge cases and this "loose" handshake specification
	// allows to implement all kind of components which arrange or display something on the screen.
	virtual void layout(const Rect& provided_rect) noexcept = 0;

	// Renders the component into the provided render target.
	// ToDo: Provide some destination rect for rendering, so that frames can be implemented.
	virtual void render(RenderTarget& rt) noexcept = 0;

	// ToDo: Collect all animated components and store them in a vector.
	// On every frame, call animate() of all components in the vector.
	// Do not animate recursively. The overhead is huge in case there are many components but just a few animated components.
	virtual void animate() noexcept {

	}

	virtual void on_animate() noexcept {

	}

	// ToDo: I am not sure yet if it's better to use an Event union type for messaging,
	// or many virtual methods, one for each event type.
	// I expect using virtual methods for each event type is a little bit faster because there will be
	// only an additional v-table lookup to get to the right code, but the v-table will grow.
	// Also, if the user implements their own component, there will be more work to do. Using an
	// union class will also have one v-table lookup but additionally we need a switch which hopefully compiles
	// down to a LUT jumper. In the worst case the compiler will generate lots of if/else.
	
	// virtual void on_event(const Event& event) noexcept {
	//
	// }

	virtual void on_hit() noexcept {

	}

	virtual Component* cursor_move(const Point& point) noexcept {
		(void)point;
		return nullptr;
	}

	virtual void on_cursor_move(const Point& point) noexcept {
		(void)point;
	}

	virtual bool hit(const Point& point) noexcept {
		(void)point;
		return false;
	}

	virtual void on_cursor_enter() noexcept {

	}

	virtual void on_cursor_leave() noexcept {
		
	}

protected:
	Rect m_rect;

	Component* m_parent;
};