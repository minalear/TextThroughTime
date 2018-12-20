//
// Created by Trevor Fisher on 10/8/2018.
//

#include "window_manager.h"

// Constructor
WindowManager::WindowManager(minalear::GameWindow *window) :
    console(window),
    title_window(&console, 1, 1, 98, 1),
    log_window(&console, 1, 3, 98, 34),
    input_window(&console, 1, 38, 98, 1)
{
    draw_borders();
    input_window.print(">> ");
}

// Private functions
/// Draws the borders around the various windows
void WindowManager::draw_borders() {
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

    console.put(L'╠',  0,  2);
    console.put(L'╠',  0, 37);
    console.put(L'╣', 99,  2);
    console.put(L'╣', 99, 37);
}

// Public Functions
void WindowManager::set_title(std::string title) {
    title_window.clear(L'-');
    title_window.print(" " + title + " ", TextAlignment::Center, title_window.get_width() / 2, 0);
}

void WindowManager::render_to_screen() {
    console.draw();
}

void WindowManager::text_input(wchar_t ch) {
    input_text += ch;
    input_window.put(ch);
    console.update_buffer();
}
void WindowManager::keydown(SDL_Keycode keycode) {
    if (keycode == SDLK_BACKSPACE) {
        input_text = input_text.substr(0, input_text.size() - 1);
        input_window.clear();
        input_window.set(0);
        input_window.print(">> ");
        input_window.print(input_text);
    }
    else if (keycode == SDLK_RETURN) {
        print_to_log("\n\n\n");
        print_to_log(">> " + input_text);
        callback(input_text);
        input_text = "";
        input_window.clear();
        input_window.print(">> ");
    }

    console.update_buffer();
}

void WindowManager::print_to_log(const std::string &str) {
    // We must break up long strings into multiple log entries
    std::string buffer;
    for (auto& x : str) {
        if (x != '\n')
            buffer += x;

        if (buffer.size() == log_window.get_width() - 1 || x == '\n') {
            log_list.add(buffer);
            buffer.clear();
        }
    }
    if (!buffer.empty()) {
        log_list.add(buffer);
        buffer.clear();
    }

    //log_list.add(str);
    log_window.clear();

    for (int i = 0; i < log_window.get_height() && i < log_list.count(); i++) {
        log_window.set(0, log_window.get_height() - i - 1);
        log_window.print(log_list[i]);
    }
}

void WindowManager::clear_log() {
    log_window.clear();
    log_list.clear();
}

void WindowManager::set_callback(InputCallback callback) {
    this->callback = callback;
}
