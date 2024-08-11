#include <rt/rt.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <chrono>
#include <optional>
#include <iostream>
#include <list>
#include <vector>


class ADHSBox final : public Box {
public:
    ADHSBox(Component* content) noexcept : Box(BoxDesc().border_thickness(1).border_color(Color(0, 255, 0, 255)), content) {

    }

    void animate() noexcept  override {
        auto desc = get_desc();
        desc.m_margin = m_mar;
        set_desc(desc);
        if (m_mar == 100) {
            m_dir = -1;
        }
        if (m_mar == 0) {
            m_dir = +1;
        }
        m_mar += m_dir;
    }

private:
    int32_t m_dir = 1;
    int32_t m_mar = 0;
};

class HitImage final : public Image {
public:
	HitImage(const char* path) : Image(path) {

	}

	void on_hit() noexcept override {
		if (m_dst_margin == 0) {
			m_dst_margin = 100;
		}
		else {
			m_dst_margin = 0;
		}
	}

	void on_animate() noexcept override {
		if (get_parent()) {
			if (auto* parent = dynamic_cast<Box*>(get_parent()); parent) {
				auto box_desc = parent->get_desc();
				box_desc.m_margin = m_cur_margin;
				parent->set_desc(box_desc);
			}
		}
		if (m_dst_margin != m_cur_margin) {
			if (m_dst_margin > m_cur_margin) {
				m_cur_margin++;
			}
			else {
				m_cur_margin--;
			}
		}
	}

	void on_cursor_enter() noexcept override {
		if (auto* parent = dynamic_cast<Box*>(get_parent()); parent) {
			auto box_desc = parent->get_desc();
			box_desc.m_border_color.m_r = 0;
			box_desc.m_border_color.m_g = 0;
			box_desc.m_border_color.m_b = 255;
			box_desc.m_border_color.m_a = 255;
			parent->set_desc(box_desc);
		}
	}

	void on_cursor_leave() noexcept override {
		if (auto* parent = dynamic_cast<Box*>(get_parent()); parent) {
			auto box_desc = parent->get_desc();
			box_desc.m_border_color.m_r = 0;
			box_desc.m_border_color.m_g = 255;
			box_desc.m_border_color.m_b = 0;
			box_desc.m_border_color.m_a = 255;
			parent->set_desc(box_desc);
		}
	}

private:
	uint32_t m_dst_margin = 0;
	uint32_t m_cur_margin = 0;
};


int main(int argc, char* argv[]) {
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);

	Size rt_size(1000, 600);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		panic();
	}
	SDL_Window* window = SDL_CreateWindow("Test", 100, 100, rt_size.m_x, rt_size.m_y, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		panic();
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		panic();
	}
	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_BGRA8888,
		SDL_TEXTUREACCESS_STREAMING,
		rt_size.m_x,
		rt_size.m_y
	);
	if (texture == nullptr) {
		panic();
	}

	BasicRenderTarget rt(rt_size);

	

    auto* grid = new Grid;
    grid->push_row({
        new HAlignR(
			new Box(BoxDesc().padding(4).border_thickness(2).border_color(Color(0, 255, 0, 255)),
				new HitImage("C:/data/test.png")
			)
		),
        new Box(BoxDesc().padding(4).border_thickness(2).border_color(Color(0, 255, 0, 255)),
            new HitImage("C:/data/test.png")
        ),
        new Box(BoxDesc().padding(4).border_thickness(2).border_color(Color(0, 255, 0, 255)),
            new HitImage("C:/data/test.png")
        )
    });
    grid->push_row({
        new Box(BoxDesc().padding(4).border_thickness(2).border_color(Color(0, 255, 0, 255)),
            new HitImage("C:/data/test.png")
        ),
        new Box(BoxDesc().padding(4).border_thickness(2).border_color(Color(0, 255, 0, 255)),
            new HitImage("C:/data/test.png")
        ),
		new Box(BoxDesc().padding(4).border_thickness(2).border_color(Color(255, 0, 0, 255)).margin(4),
			new VStack({
				new Box(BoxDesc().padding(4).border_thickness(2).border_color(Color(0, 255, 0, 255)),
					new HitImage("C:/data/test.png")
				),
				new Box(BoxDesc().padding(4).border_thickness(2).border_color(Color(0, 255, 0, 255)),
					new HitImage("C:/data/test.png")
				)
			})
		)
    });

	Body body(rt_size,
		new Box(BoxDesc().border_thickness(10).margin(20),
            grid
        )
	);

	rt.clear(Color(45, 45, 45, 255));
	body.animate();
	body.layout();
	body.render(rt);

	//rt.to("C:/data/result.png");

	SDL_Event event;
	bool quit = false;



	bool was_event = false;


	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				body.hit(Point(event.button.x, event.button.y));
				was_event = true;
			}
			if (event.type == SDL_MOUSEMOTION) {
				body.cursor_move(Point(event.button.x, event.button.y));
				was_event = true;
			}
		}

		auto t_start = std::chrono::high_resolution_clock::now();

		if (was_event) {
			rt.clear(Color(45, 45, 45, 255));
			body.animate();
			body.layout();
			body.render(rt);
			//was_event = false;
		}

		auto t_end = std::chrono::high_resolution_clock::now();

		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();

		std::cout << elapsed_time_ms << std::endl;

		Color* texture_data = nullptr;
		int pitch = rt_size.m_x * 4;
		if (SDL_LockTexture(texture, nullptr, (void**)&texture_data, &pitch) < 0) {
			panic();
		}
		for (size_t i = 0; i < rt_size.get_area(); ++i) {
			texture_data[i].m_r = rt.get_data()[i].m_a;
			texture_data[i].m_g = rt.get_data()[i].m_r;
			texture_data[i].m_b = rt.get_data()[i].m_g;
			texture_data[i].m_a = rt.get_data()[i].m_b;
		}
		SDL_UnlockTexture(texture);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}