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
    // Load our charset (bitmap)
    charset = new minalear::texture("fonts/charset.png");

    // The dimensions of each individual console cell
    const int CELL_WIDTH  = 8;
    const int CELL_HEIGHT = 12;

    // The buffer width and height of our entire console
    width  = (uint16_t)(game_window->width() / 8);
    height = (uint16_t)(game_window->width() / 12);

    // The total number of characters in our character set
    const int num_chars = sizeof(CHAR_SET_STRING) / sizeof(wchar_t);
    char_data = new ConsoleChar[num_chars]; // Data is stored in char_data

    // Initialize char_data with their relevant information (UV position)
    for (int i = 0; i < num_chars; i++) {
        ConsoleChar ch = char_data[i];
        int x = i % 16;
        int y = i / 16;

        char_data[i].x = (x * CELL_WIDTH) / (float)charset->getWidth();
        char_data[i].y = (y * CELL_HEIGHT) / (float)charset->getHeight();
        char_data[i].ch = CHAR_SET_STRING[i];
    }

    // Generate OpenGL variables
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    const int num_cells = width * height;
    gl_buffer = new float[num_cells * 24];

    glBufferData(GL_ARRAY_BUFFER, num_cells * 24 * sizeof(float), gl_buffer, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // UV

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Initialize cells to default values (' ')
    cursor = 0;
    cells = new CellData[num_cells];
    for (int i = 0; i < num_cells; i++) {
        put(L' ', i % width, i / width);
    }
    update_buffer();

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
    delete [] char_data;
    delete [] cells;
    delete console_shader;
    delete charset;
    delete [] gl_buffer;
}

void Console::print(const std::string &str) {
    for (auto& x : str) {
        put(x, cursor % width, cursor / width);
        cursor++;
    }

    update_buffer();
}
void Console::print(const std::string &str, TextAlignment alignment, int x, int y) {
    set(x, y);
    if (alignment == TextAlignment::Center) {
        cursor -= str.size() / 2;
    } else if (alignment == TextAlignment::Right) {
        cursor -= str.size();
    }
    print(str);
}

void Console::draw() {
    charset->bind();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, width * height * 6);
    glBindVertexArray(0);
}

ConsoleChar Console::find_char_data(wchar_t ch) {
    for (int i = 0; i < 257; i++) {
        if (char_data[i].ch == ch) {
            return char_data[i];
        }
    }

    return char_data[0]; //TODO: Replace with a throw
}
void Console::update_buffer() {
    const float mod = 1.f / 16.f;
    for (int i = 0; i < width * height; i++) {
        auto cell = cells[i];
        auto data = find_char_data(cell.ch);

        float x = (i % width) * 8.f;
        float y = (i / width) * 12.f;

        // region *** gl_buffer update ***
        gl_buffer[i * 24 +  0] = x;
        gl_buffer[i * 24 +  1] = y;
        gl_buffer[i * 24 +  2] = data.x;
        gl_buffer[i * 24 +  3] = data.y;

        gl_buffer[i * 24 +  4] = x;
        gl_buffer[i * 24 +  5] = y + 12.f;
        gl_buffer[i * 24 +  6] = data.x;
        gl_buffer[i * 24 +  7] = data.y + mod;

        gl_buffer[i * 24 +  8] = x + 8.f;
        gl_buffer[i * 24 +  9] = y;
        gl_buffer[i * 24 + 10] = data.x + mod;
        gl_buffer[i * 24 + 11] = data.y;


        gl_buffer[i * 24 + 12] = x + 8.f;
        gl_buffer[i * 24 + 13] = y;
        gl_buffer[i * 24 + 14] = data.x + mod;
        gl_buffer[i * 24 + 15] = data.y;

        gl_buffer[i * 24 + 16] = x;
        gl_buffer[i * 24 + 17] = y + 12.f;
        gl_buffer[i * 24 + 18] = data.x;
        gl_buffer[i * 24 + 19] = data.y + mod;

        gl_buffer[i * 24 + 20] = x + 8.f;
        gl_buffer[i * 24 + 21] = y + 12.f;
        gl_buffer[i * 24 + 22] = data.x + mod;
        gl_buffer[i * 24 + 23] = data.y + mod;
        // endregion
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, width * height * 24 * sizeof(float), gl_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Console::set(int x, int y) {
    cursor = x + y * width;
}
void Console::put(wchar_t ch, int x, int y) {
    cells[x + y * width].ch = ch;
}
