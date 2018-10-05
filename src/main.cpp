#include "core/window.h"
#include "core/font.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "text_renderer.h"

std::string buffer_substr(std::string &buffer, const uint32_t cursor) {
    std::string str;
    if (cursor > 0) {
        str = buffer.substr(0, cursor - 1);
    }
    if (cursor < buffer.size()) {
        str += buffer.substr(cursor, buffer.size());
    }

    return str;
}
std::string get_render_string(std::string &buffer, const uint32_t cursor) {
    std::string render_str = buffer.substr(0, cursor) + " | ";
    if (cursor < buffer.size()) {
        render_str += buffer.substr(cursor, buffer.size());
    }

    return render_str;
}

int main(int argc, char* argv[]) {
    minalear::GameWindow game_window("A Text Through Time", 1280, 720);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClearColor(0.f, 0.f, 0.f, 1.f);

	TextRenderer text_renderer("Main");

	std::string input_buffer;
	uint32_t cursor = 0;
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			// Break out of game loop
			if (windowEvent.type == SDL_QUIT) break;
			if (windowEvent.type == SDL_KEYDOWN) {
			    switch(windowEvent.key.keysym.scancode) {
			        case SDL_SCANCODE_BACKSPACE:
                        input_buffer = buffer_substr(input_buffer, cursor);
                        cursor = (cursor > 0) ? cursor - 1 : 0;
			            break;
			        case SDL_SCANCODE_LEFT:
			            cursor = (cursor > 0) ? cursor - 1 : 0;
			            break;
			        case SDL_SCANCODE_RIGHT:
			            cursor = (cursor < input_buffer.size()) ? cursor + 1: input_buffer.size();
			            break;
                    default:
                        input_buffer += (char) windowEvent.key.keysym.sym;
                        cursor++;
                        break;
			    }
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		text_renderer.draw_string(get_render_string(input_buffer, cursor), glm::vec2(0.f), glm::vec2(1.f));
		
		game_window.dt();
		game_window.swap_buffers();
	} // End main game loop

    return 0;
}