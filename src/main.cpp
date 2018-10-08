#include "core/window.h"
#include "core/font.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "text_renderer.h"
#include "console.h"

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
    std::string render_str = buffer.substr(0, cursor) + " I ";
    if (cursor < buffer.size()) {
        render_str += buffer.substr(cursor, buffer.size());
    }

    return render_str;
}

int main(int argc, char* argv[]) {
    minalear::GameWindow game_window("A Text Through Time", 800, 480);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//TextRenderer text_renderer("main");
	Console console(&game_window);
	console.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce molestie enim at nibh malesuada, sed imperdiet tortor ullamcorper. Donec fringilla cursus nulla vel mollis. Donec ac sollicitudin massa, porttitor rhoncus ex. Proin suscipit ut eros vel gravida. Sed eleifend augue vitae justo porta, vel porttitor orci lacinia. Nam id sapien sed ex viverra pretium sit amet et ligula. Integer in eros metus."
                  "Cras consectetur lacinia aliquet. Etiam mattis tristique velit, consequat convallis odio ultrices non. Vestibulum vitae enim consequat, faucibus lorem sit amet, feugiat dolor. Proin vitae sollicitudin mi. Phasellus ac massa quis turpis tempus dignissim. Nunc congue pellentesque tortor, eu maximus dolor aliquam ut. Aenean commodo lorem eget dui eleifend, in auctor enim accumsan. Sed eget cursus leo. Aenean vitae tempor massa, eget fringilla felis. Pellentesque dignissim scelerisque lacus, ac tempus ex tristique quis. Nullam id urna felis. Mauris sed sodales lorem. Mauris fringilla semper ligula, quis condimentum mi lacinia sed. Nunc ac eleifend arcu. Duis ut nibh lacinia, lacinia magna a, accumsan metus."
                  "Praesent massa metus, ullamcorper tempus mattis non, blandit et tortor. Nullam at mi non quam consequat fermentum ac sed mauris. Ut fringilla efficitur leo, eu tincidunt libero. Morbi vitae odio malesuada, dignissim risus non, cursus ipsum. Sed ac congue diam, non tincidunt ante. Donec ut sollicitudin ante, quis rutrum tortor. Morbi justo est, dictum eu dolor sit amet, commodo fringilla arcu. Fusce sed malesuada augue, ut ultricies sapien. Nam sollicitudin dolor vel ante pulvinar, in interdum mi lacinia. Vivamus porttitor magna non pharetra aliquam. Nunc quis lacus pulvinar, suscipit risus lobortis, finibus massa. Duis vulputate venenatis massa, sit amet porta lectus sodales aliquet. Suspendisse eu velit vel ligula eleifend maximus."
                  "Nam porta malesuada quam euismod semper. Curabitur ullamcorper, lorem non accumsan tristique, libero nunc vehicula ligula, non egestas erat massa non turpis. Sed id feugiat purus, sed commodo mauris. Donec suscipit eros ante, ac condimentum metus tristique non. Suspendisse at tellus id mi pellentesque hendrerit elementum tristique dolor. In sed volutpat ipsum, sit amet ultricies lorem. Suspendisse consectetur dolor diam, quis faucibus ante luctus in. Aenean neque felis, gravida id pretium et, ullamcorper ut tortor. Sed nec faucibus quam. Praesent dapibus dolor in velit gravida, quis vestibulum nisi mollis. Aliquam pretium nulla blandit ex varius, quis mattis elit ultrices."
                  "Curabitur eu pharetra sem. Ut euismod faucibus odio quis ullamcorper. Nunc id malesuada nisl, sollicitudin tincidunt nunc. Proin mattis elementum sapien, in tincidunt leo tincidunt id. Curabitur vel ullamcorper diam, sed efficitur sapien. Nullam rhoncus augue sit amet massa vehicula gravida. Vivamus pretium tempus nisi, ac mollis sem mollis ut. Integer vitae pretium metus. Ut id pharetra ex. Phasellus lacinia consectetur tellus, eget ullamcorper enim laoreet at. Nunc commodo id quam non dictum. Nulla eu augue interdum, molestie libero sed, finibus lectus. ");
	
	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			// Break out of game loop
			if (windowEvent.type == SDL_QUIT) break;
		}
		
		glClear(GL_COLOR_BUFFER_BIT);

		//text_renderer.draw_string(get_render_string(input_buffer, cursor), glm::vec2(0.f), glm::vec2(0.4f));
		//text_renderer.draw_string("Whatever shall I do.", glm::vec2(0.f), glm::vec2(0.5f));

		console.draw();

		game_window.dt();
		game_window.swap_buffers();
	} // End main game loop

    return 0;
}