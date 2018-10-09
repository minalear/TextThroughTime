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
    console.put(L'╔',  0,  0);
    console.put(L'╗', 99,  0);
    console.put(L'╚',  0, 39);
    console.put(L'╝', 99, 39);

    for (int x = 1; x < 99; x++) {
        console.put(L'═', x,  0);
        console.put(L'═', x,  2);
        console.put(L'═', x, 37);
        console.put(L'═', x, 39);
    }
    for (int y = 1; y < 39; y++) {
        console.put(L'║',  0, y);
        console.put(L'║', 99, y);
    }

    console.print("Title Text", TextAlignment::Center, 50, 1);

    ConsoleWindow window(&console, 1, 38, 98, 1);

    console.update_buffer();
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			// Break out of game loop
			if (windowEvent.type == SDL_QUIT) break;
			else if (windowEvent.type == SDL_TEXTINPUT) {
			    window.put(windowEvent.text.text[0]);
			    console.update_buffer();
			}
			else if (windowEvent.type == SDL_KEYDOWN) {
			    if (windowEvent.key.keysym.sym == SDLK_BACKSPACE) {
			        window.set(window.get_cursor() - 1);
			        window.put(L' ');
			        window.set(window.get_cursor() - 1);
			    }

			    console.update_buffer();
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		console.draw();

		game_window.dt();
		game_window.swap_buffers();
	} // End main game loop

    return 0;
}