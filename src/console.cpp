//
// Created by Trevor Fisher on 10/7/2018.
//

#include <iostream>
#include "console.h"
#include "core/file_handler.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "glad/glad.h"

const wchar_t CHAR_SET_STRING[] =
       L" ☺☻♥♦♣♠•◘○◙♂♀♪♫☼"
        "►◄↕‼¶§▬↨↑↓→←∟↔▲▼"
        " !\"#$%&'()*+,-./"
        "0123456789:;<=>?"
        "@ABCDEFGHIJKLMNO"
        "PQRSTUVWXYZ[\\]^_"
        "`abcdefghijklmno"
        "pqrstuvwxyz{|}~⌂"
        "ÇüéâäàåçêëèïîìÄÅ"
        "ÉæÆôöòûùÿÖÜ¢£¥₧ƒ"
        "áíóúñÑªº¿⌐¬½¼¡«»"
        "░▒▓│┤╡╢╖╕╣║╗╝╜╛┐"
        "└┴┬├─┼╞╟╚╔╩╦ⁿ═╬╧"
        "╨╤╥╙╘╒╓╫╪┘┌█▄▌▐▀"
        "αßΓπΣσµτΦΘΩδ∞φε∩"
        "≡±≥≤⌠⌡÷≈°∙·√ⁿ²■╠";

Console::Console(minalear::GameWindow *game_window) {
    charset = new minalear::texture("fonts/charset.png");

    const int CELL_WIDTH  = 8;
    const int CELL_HEIGHT = 12;

    width  = (uint16_t)(game_window->width() / 8);
    height = (uint16_t)(game_window->width() / 12);

    const int num_chars = sizeof(CHAR_SET_STRING) / sizeof(wchar_t);
    cells = new ConsoleChar[num_chars];

    for (int i = 0; i < num_chars; i++) {
        ConsoleChar ch = cells[i];
        int x = i % 16;
        int y = i / 16;

        cells[i].x = (x * CELL_WIDTH) / (float)charset->getWidth();
        cells[i].y = (y * CELL_HEIGHT) / (float)charset->getHeight();
        cells[i].ch = CHAR_SET_STRING[i];
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    const int num_cells = width * height;
    gl_buffer = new float[num_cells * 24];
    for (int i = 0; i < num_cells; i++) {
        int x = i % width;
        int y = i / width;

        // TL
        gl_buffer[i * 24 + 0] = x * CELL_WIDTH;  // X
        gl_buffer[i * 24 + 1] = y * CELL_HEIGHT; // Y
        gl_buffer[i * 24 + 2] = 0.f;             // UV X
        gl_buffer[i * 24 + 3] = 0.f;             // UV Y

        // BL
        gl_buffer[i * 24 + 4] = x * CELL_WIDTH;
        gl_buffer[i * 24 + 5] = y * CELL_HEIGHT + CELL_HEIGHT;
        gl_buffer[i * 24 + 6] = 0.f;
        gl_buffer[i * 24 + 7] = 0.f;

        // TR
        gl_buffer[i * 24 + 8] = x * CELL_WIDTH + CELL_WIDTH;
        gl_buffer[i * 24 + 9] = y * CELL_HEIGHT;
        gl_buffer[i * 24 + 10] = 0.f;
        gl_buffer[i * 24 + 11] = 0.f;


        // TR
        gl_buffer[i * 24 + 12] = x * CELL_WIDTH + CELL_WIDTH;
        gl_buffer[i * 24 + 13] = y * CELL_HEIGHT;
        gl_buffer[i * 24 + 14] = 0.f;
        gl_buffer[i * 24 + 15] = 0.f;

        // BL
        gl_buffer[i * 24 + 16] = x * CELL_WIDTH;
        gl_buffer[i * 24 + 17] = y * CELL_HEIGHT + CELL_HEIGHT;
        gl_buffer[i * 24 + 18] = 0.f;
        gl_buffer[i * 24 + 19] = 0.f;

        // BR
        gl_buffer[i * 24 + 20] = x * CELL_WIDTH + CELL_WIDTH;
        gl_buffer[i * 24 + 21] = y * CELL_HEIGHT + CELL_HEIGHT;
        gl_buffer[i * 24 + 22] = 0.f;
        gl_buffer[i * 24 + 23] = 0.f;
    }

    glBufferData(GL_ARRAY_BUFFER, num_cells * 24 * sizeof(float), gl_buffer, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // UV

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Initialize shader
    console_shader = new minalear::shader_program(
            minalear::read_file("shaders/console_vert.glsl"),
            minalear::read_file("shaders/console_frag.glsl"));
    console_shader->use();

    glm::mat4 proj, view, model;
    proj = glm::ortho(0.f, (float)game_window->width(), (float)game_window->height(), 0.f, -1.f, 1.f);
    view = glm::mat4(1.f);
    model = glm::mat4(1.f);

    console_shader->set_uniform("proj", proj);
    console_shader->set_uniform("view", view);
    console_shader->set_uniform("model", model);
}

Console::~Console() {
    delete [] cells;
    delete console_shader;
    delete charset;
    delete [] gl_buffer;
}

void Console::print(const std::string &str) {
    int cursor = 0;

    for (auto& x : str) {
        // Set letter buffer
        for (int i = 0; i < 257; i++) {
            if (x == cells[i].ch) {
                float x_mod = 1.f / 16.f;
                float y_mod = 1.f / 16.f;

                gl_buffer[cursor * 24 + 0] = (cursor % width) * 8.f;
                gl_buffer[cursor * 24 + 1] = (cursor / width) * 12.f;
                gl_buffer[cursor * 24 + 2] = cells[i].x;
                gl_buffer[cursor * 24 + 3] = cells[i].y;

                gl_buffer[cursor * 24 + 4] = (cursor % width) * 8.f;
                gl_buffer[cursor * 24 + 5] = (cursor / width) * 12.f + 12.f;
                gl_buffer[cursor * 24 + 6] = cells[i].x;
                gl_buffer[cursor * 24 + 7] = cells[i].y + y_mod;

                gl_buffer[cursor * 24 + 8] = (cursor % width) * 8.f + 8.f;
                gl_buffer[cursor * 24 + 9] = (cursor / width) * 12.f;
                gl_buffer[cursor * 24 + 10] = cells[i].x + x_mod;
                gl_buffer[cursor * 24 + 11] = cells[i].y;


                gl_buffer[cursor * 24 + 12] = (cursor % width) * 8.f + 8.f;
                gl_buffer[cursor * 24 + 13] = (cursor / width) * 12.f;
                gl_buffer[cursor * 24 + 14] = cells[i].x + x_mod;
                gl_buffer[cursor * 24 + 15] = cells[i].y;

                gl_buffer[cursor * 24 + 16] = (cursor % width) * 8.f;
                gl_buffer[cursor * 24 + 17] = (cursor / width) * 12.f + 12.f;
                gl_buffer[cursor * 24 + 18] = cells[i].x;
                gl_buffer[cursor * 24 + 19] = cells[i].y + y_mod;

                gl_buffer[cursor * 24 + 20] = (cursor % width) * 8.f + 8.f;
                gl_buffer[cursor * 24 + 21] = (cursor / width) * 12.f + 12.f;
                gl_buffer[cursor * 24 + 22] = cells[i].x + x_mod;
                gl_buffer[cursor * 24 + 23] = cells[i].y + y_mod;
                break;
            }
        }

        cursor++;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 6600 * 24 * sizeof(float), gl_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Console::draw() {
    charset->bind();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, width * height * 6);
    glBindVertexArray(0);
}
