#include "core/window.h"
#include "core/font.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "text_renderer.h"
#include "console.h"

int main(int argc, char* argv[]) {
    minalear::GameWindow game_window("A Text Through Time", 800, 480);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClearColor(0.f, 0.f, 0.f, 1.f);

	Console console(&game_window);
	ConsoleWindow window(&console, 3, 3, 8, 1);
	window.print("Hello");
	ConsoleWindow input_box(&console, 0, 39, 80, 1);
	input_box.print("What the hek");
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			// Break out of game loop
			if (windowEvent.type == SDL_QUIT) break;
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		console.draw();

		game_window.dt();
		game_window.swap_buffers();
	} // End main game loop

    return 0;
}