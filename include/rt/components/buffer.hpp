#pragma once

#include <rt/common.hpp>
#include <rt/components/component.hpp>
#include <rt/render_targets/render_target.hpp>

// The buffer class has its own render target and can be used to optimize the rendering process.
// In the future, components will only be re-rendered when its necessary.
// When you know that a component tree must be rerendered very often, but the tree itself has no changes
// e.g. due to transparency, then the buffer class provides a way to cache the rendering results of a component tree.

/*class Buffer : public Component {
public:
    RT_INLINE Buffer(RenderTarget* rt) noexcept : m_rt(rt) {
        
    }

    void render(RenderTarget& rt) noexcept override {
        if (m_rt) {

        }
    }

private:
    RenderTarget* m_rt;
};*/