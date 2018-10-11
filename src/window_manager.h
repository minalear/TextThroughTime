//
// Created by Trevor Fisher on 10/8/2018.
//

#ifndef TEXTTHROUGHTIME_WINDOW_MANAGER_H
#define TEXTTHROUGHTIME_WINDOW_MANAGER_H

#include <iostream>
#include "console.h"
#include "core/window.h"
#include "log.h"

class WindowManager;
typedef void (*InputCallback)(WindowManager*, const std::string&);

/// Window Manager manages displaying text to the screen and processing input.
class WindowManager {
    Console console;
    ConsoleWindow title_window, log_window, input_window;
    Log log_list;

    std::string title, input_text;

    InputCallback callback;

    void draw_borders();

public:
    explicit WindowManager(minalear::GameWindow *window);

    void set_title(std::string title);
    void render_to_screen();
    void text_input(wchar_t ch);
    void keydown(SDL_Keycode keycode);
    void print_to_log(const std::string &str);
    void set_callback(InputCallback callback);
};


#endif //TEXTTHROUGHTIME_WINDOW_MANAGER_H
