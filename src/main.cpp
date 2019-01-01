#include "core/window.h"
#include "core/font.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "text_renderer.h"
#include "console.h"
#include "window_manager.h"
#include "tokenizer.h"
#include "game/room.h"
#include "game/game_manager.h"

WindowManager *window_manager;
GameManager *game_manager;
//TODO: Find a more elegant solution than putting these in the global namespace

void callback(const std::string &str) {
    game_manager->handle_input(str);
}

int main(int argc, char* argv[]) {
    minalear::GameWindow game_window("A Text Through Time", 800, 480);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClearColor(0.f, 0.f, 0.f, 1.f);

	window_manager = new WindowManager(&game_window);
	window_manager->set_title("A Text Through Time");
	window_manager->set_callback(callback);

	game_manager = new GameManager(window_manager);
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			// Break out of game loop
			if (windowEvent.type == SDL_QUIT) break;
			else if (windowEvent.type == SDL_TEXTINPUT) {
			    window_manager->text_input(windowEvent.text.text[0]);
			}
			else if (windowEvent.type == SDL_KEYDOWN) {
			    window_manager->keydown(windowEvent.key.keysym);
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		window_manager->render_to_screen();

		game_window.dt();
		game_window.swap_buffers();
	} // End main game loop

	delete game_manager;
	delete window_manager;
    return 0;
}