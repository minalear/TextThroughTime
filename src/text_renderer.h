//
// Created by Trevor Fisher on 10/5/2018.
//

#ifndef MINALEAR_TEXT_RENDERER_H
#define MINALEAR_TEXT_RENDERER_H

#include <string>
#include "core/font.h"
#include "core/shader_program.h"
#include "glm.hpp"

enum struct TEXT_POSITIONING {
    Left, Center, Right
};

class TextRenderer {
private:
    uint32_t vao, vbo;
    minalear::shader_program *text_shader;

public:
    minalear::font *text_font;

    TextRenderer(const std::string font_name);
    ~TextRenderer();

    void draw_string(std::string str, glm::vec2 pos, glm::vec2 scale);
    glm::vec2 measure_string(std::string str, glm::vec2 scale);
};


#endif //MINALEAR_TEXT_RENDERER_H
