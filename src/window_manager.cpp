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
void WindowManager::keydown(SDL_Keysym key) {
    auto keycode = key.sym;
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
    else if (keycode == SDLK_c && ((key.mod & KMOD_LCTRL) || (key.mod & KMOD_RCTRL))) {
        input_text = "";
        input_window.clear();
        input_window.print(">> ");
    }

    console.update_buffer();
}

void WindowManager::print_to_log(const std::string &str) {
    // Word wrap longer strings into multiple lines in the log
    const int buffer_width = log_window.get_width();
    std::string word_buffer, line_buffer;

    for (auto& ch : str) {
        // Words are delimited by spaces, when we hit one, check to ensure the total line_buffer length
        // does not exceed the buffer width.  If it does, split it there, otherwise add the word.
        if (ch == '\n') { // Split the line on newline characters
            if (!word_buffer.empty()) {
                line_buffer += word_buffer;
            }
            log_list.add(line_buffer);
            line_buffer.clear();
            word_buffer.clear();
        }
        else if (ch == ' ') {
            if (line_buffer.size() + word_buffer.size() + 1 > buffer_width) { // Split the line
                log_list.add(line_buffer);
                line_buffer = word_buffer + " ";
                word_buffer.clear();
            } else {
                line_buffer += word_buffer + " "; // Don't split the line
                word_buffer.clear();
            }
        } else {
            word_buffer += ch;
        }
    }
    if (!word_buffer.empty()) {
        line_buffer += word_buffer;
    }
    if (!line_buffer.empty()) {
        log_list.add(line_buffer);
        line_buffer.clear();
    }

    // Move the lines up along the window so the lines rise up
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
