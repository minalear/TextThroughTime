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

class Console {
    uint16_t width;
    uint16_t height;

    uint32_t vao;
    uint32_t vbo;

    ConsoleChar *cells;
    minalear::shader_program *console_shader;
    minalear::texture *charset;
    float *gl_buffer;

public:
    Console(minalear::GameWindow *game_window);
    ~Console();

    void print(const std::string &str);
    void draw();
};


#endif //TEXTTHROUGHTIME_CONSOLE_H
