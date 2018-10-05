#include "core/window.h"
#include "core/font.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "text_renderer.h"

int main(int argc, char* argv[]) {
    minalear::GameWindow game_window("A Text Through Time", 800, 450);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClearColor(0.f, 0.f, 0.f, 1.f);

	TextRenderer text_renderer("Main");
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			// Break out of game loop
			if (windowEvent.type == SDL_QUIT) break;
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		text_renderer.draw_string(
		        "Dr. James Enderby Bidlack, born February 1, 1961, is a \n"
                "Professor of Biology and CURE-SEM Scholar at the \n"
                "University of Central Oklahoma,\n"
                "President of Metabolism Foundation,\n"
                "and Vice President of the Genome Registry.  He is a member\n"
                "of the MERLOT Editorial Board MERLOT-Biology, and a past\n"
                "co-sponsor for the Tri-Beta-Biology Club.\n"
                "Most notably, James 'Jim' Bidlack is known for his\n"
                "research, textbooks, and involvement with the\n"
                "Repository for Germinal Choice.",
		        glm::vec2(0.f), glm::vec2(1.f));
		
		game_window.dt();
		game_window.swap_buffers();
	} // End main game loop

    return 0;
}