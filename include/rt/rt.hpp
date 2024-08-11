#pragma once

// ToDo: I would like to have some kind of Async component, which provides a way to load the content
// asynchronously, e.g. if an extension for a Web-Downloaded-Image needs some time to load the content,
// the interface should not stall, it should continue and render the component when its loaded.

#include <rt/common.hpp>

#include <rt/components/body.hpp>
#include <rt/components/box.hpp>
#include <rt/components/buffer.hpp>
#include <rt/components/component.hpp>
#include <rt/components/expand.hpp>
#include <rt/components/grid.hpp>
#include <rt/components/h_align_r.hpp>
#include <rt/components/h_stack.hpp>
#include <rt/components/image.hpp>
#include <rt/components/v_align_b.hpp>
#include <rt/components/v_stack.hpp>

#include <rt/math/color.hpp>
#include <rt/math/point.hpp>
#include <rt/math/rect.hpp>
#include <rt/math/size.hpp>

#include <rt/render_targets/basic_render_target.hpp>
#include <rt/render_targets/render_target.hpp>