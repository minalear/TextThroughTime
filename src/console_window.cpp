//
// Created by Trevor Fisher on 10/8/2018.
//

#include "console.h"

ConsoleWindow::ConsoleWindow(Console* console, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    this->console = console;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->cursor = 0;
}

void ConsoleWindow::clear() {
    clear(L' ');
}
void ConsoleWindow::clear(wchar_t ch) {
    for (int k = 0; k < height; k++) {
        for (int j = 0; j < width; j++) {
            int ax = j + this->x;
            int ay = k + this->y;

            console->put(ch, ax, ay);
        }
    }

    set(0);
}
void ConsoleWindow::set(int c) {
    // Ensure that the cursor remains in bounds of the window.
    cursor = (c >= 0 && c < width * height) ? c : cursor;
}
void ConsoleWindow::set(int x, int y) {
    set(x + y * width);
}
void ConsoleWindow::put(wchar_t ch) {
    put(ch, cursor % width, cursor / width);
    set(cursor+1);
}
void ConsoleWindow::put(wchar_t ch, int x, int y) {
    if (ch == '\n' || ch == '\r') {
        set(cursor + width - x - 1);
    } else {
        int ax = x + this->x;
        int ay = y + this->y;

        console->put(ch, ax, ay);
    }
}
void ConsoleWindow::print(const std::string &str) {
    for (auto& x : str) {
        put(x, cursor % width, cursor / width);
        set(cursor+1);
    }

    console->update_buffer();
}
void ConsoleWindow::print(const std::string &str, TextAlignment alignment, int x, int y) {
    set(x, y);
    if (alignment == TextAlignment::Center) {
        cursor -= str.size() / 2;
    } else if (alignment == TextAlignment::Right) {
        cursor -= str.size();
    }
    print(str);
}

int ConsoleWindow::get_cursor() {
    return cursor;
}

int ConsoleWindow::get_width() {
    return width;
}

int ConsoleWindow::get_height() {
    return height;
}
