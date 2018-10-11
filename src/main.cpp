#include "core/window.h"
#include "core/font.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "text_renderer.h"
#include "console.h"
#include "window_manager.h"
#include "tokenizer.h"

void callback(WindowManager* manager, const std::string &str) {
    auto tokens = tokenize(str);
    manager->print_to_log(tokens.tokens[0]);
}

int main(int argc, char* argv[]) {
    minalear::GameWindow game_window("A Text Through Time", 800, 480);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClearColor(0.f, 0.f, 0.f, 1.f);

	WindowManager manager(&game_window);
	manager.set_title("A Text Through Time");
	manager.set_callback(callback);
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			// Break out of game loop
			if (windowEvent.type == SDL_QUIT) break;
			else if (windowEvent.type == SDL_TEXTINPUT) {
			    manager.text_input(windowEvent.text.text[0]);
			}
			else if (windowEvent.type == SDL_KEYDOWN) {
			    manager.keydown(windowEvent.key.keysym.sym);
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		manager.render_to_screen();

		game_window.dt();
		game_window.swap_buffers();
	} // End main game loop

    return 0;
}