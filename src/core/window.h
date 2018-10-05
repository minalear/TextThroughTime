//
// Created by Trevor Fisher on 2/3/2018.
//

#ifndef MINALEAR_WINDOW_H
#define MINALEAR_WINDOW_H

namespace minalear {
    void init_game_window(const char win_name[], int window_width, int window_height);
    void init_opengl();
    void swap_buffers();
    void finalize_window();
    float dt();

    int get_window_width();
    int get_window_height();
}

#endif //MINALEAR_WINDOW_H
