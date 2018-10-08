//
// Created by Trevor Fisher on 10/7/2018.
//

#ifndef TEXTTHROUGHTIME_CONSOLE_H
#define TEXTTHROUGHTIME_CONSOLE_H

#include <string>
#include "core/window.h"
#include "core/shader_program.h"
#include "core/texture.h"

struct ConsoleChar {
    float x, y;
    wchar_t ch;
};
struct CellData {
    wchar_t ch;
};

/// The primary console window that encapsulates the entire GameWindow
class Console {
    uint16_t width;
    uint16_t height;
    int cursor;

    uint32_t vao;
    uint32_t vbo;

    ConsoleChar *char_data;
    CellData *cells;
    minalear::shader_program *console_shader;
    minalear::texture *charset;
    float *gl_buffer;

    ConsoleChar find_char_data(wchar_t ch);

public:
    Console(minalear::GameWindow *game_window);
    ~Console();

    void put(wchar_t ch, int x, int y);
    void print(const std::string &str);

    void draw();
    void update_buffer();
};

/// Subwindows that are are subdivisions of the main console (think NCurses).
class ConsoleWindow {
    uint16_t x, y, width, height;
    Console *console;

    int cursor;

public:
    ConsoleWindow(Console *console, int x, int y, int width, int height);

    void clear();
    void set(int x, int y);
    void put(wchar_t ch, int x, int y);
    void print(const std::string &str);
};


#endif //TEXTTHROUGHTIME_CONSOLE_H
