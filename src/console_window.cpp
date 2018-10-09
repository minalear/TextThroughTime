//
// Created by Trevor Fisher on 10/8/2018.
//

#include "console.h"

void ConsoleWindow::clear() {
    for (int k = 0; k < height; k++) {
        for (int j = 0; j < width; j++) {
            int ax = j + this->x;
            int ay = k + this->y;

            console->put(L' ', ax, ay);
        }
    }

    cursor = 0;
}
void ConsoleWindow::set(int x, int y) {
    cursor = x + y * width;
}
void ConsoleWindow::put(wchar_t ch) {
    int ax = cursor % width + this->x;
    int ay = cursor / width + this->y;

    console->put(ch, ax, ay);
    cursor++;
}
void ConsoleWindow::put(wchar_t ch, int x, int y) {
    int ax = x + this->x;
    int ay = y + this->y;

    console->put(ch, ax, ay);
}
void ConsoleWindow::print(const std::string &str) {
    for (auto& x : str) {
        put(x, cursor % width, cursor / width);
        cursor++;
    }

    console->update_buffer();
}

ConsoleWindow::ConsoleWindow(Console* console, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    this->console = console;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->cursor = 0;
}

int ConsoleWindow::get_cursor() {
    return cursor;
}

void ConsoleWindow::set(int c) {
    cursor = c;
}
