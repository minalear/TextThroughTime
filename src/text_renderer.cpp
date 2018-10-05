//
// Created by Trevor Fisher on 10/5/2018.
//

#include "text_renderer.h"
#include "gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include "core/file_handler.h"

TextRenderer::TextRenderer(const std::string font_name) {
    const std::string image_path = "fonts/" + font_name + ".png";
    const std::string font_path  = "fonts/" + font_name + ".fnt";

    text_font = new minalear::font(image_path.c_str(), font_path.c_str());

    // Initialize vao and vbo
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Real buffer gets generated during font rendering
    float temp_buffer[4] = {0.f, 0.f, 0.f, 0.f};
    glBufferData(GL_ARRAY_BUFFER, sizeof(temp_buffer), temp_buffer, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // UV
    //TODO: Consider adding color for colored text?

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Initialize shader
    text_shader = new minalear::shader_program(
            minalear::read_file("shaders/text_vert.glsl"),
            minalear::read_file("shaders/text_frag.glsl"));
    text_shader->use();

    glm::mat4 proj, view, model;
    proj  = glm::ortho(0.f, 800.f, 450.f, 0.f, -1.f, 1.f);
    view  = glm::mat4(1.f);
    model = glm::mat4(1.f);

    text_shader->set_uniform("proj", proj);
    text_shader->set_uniform("view", view);
    text_shader->set_uniform("model", model);
}

TextRenderer::~TextRenderer() {
    delete text_font;
    delete text_shader;
}

void TextRenderer::draw_string(std::string str, glm::vec2 pos, glm::vec2 scale) {
    // TODO: Only recalculate buffers when the text changes

    // Set transform information
    glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(pos, 0.f)) *
                      glm::scale(glm::mat4(1.f), glm::vec3(scale, 1.f));
    text_shader->set_uniform("model", model);

    // Count the number of non-whitespace characters
    int valid_character_count = 0;
    for (auto& ch : str) {
        if (ch == ' ' || ch == '\n') continue;
        valid_character_count++;
    }

    // Initialize buffer data
    //TODO: Use a large array, rather than depend on new here
    auto buffer_data = new float[valid_character_count * 24];

    float cursor_x = 0.f;
    float cursor_y = 0.f;

    float bitmap_width  = text_font->bitmap->getWidth();
    float bitmap_height = text_font->bitmap->getHeight();

    int ch_index = 0;
    for (auto& ch : str) {
        // Skip spaces
        if (ch == ' ') {
            //cursor_x += text_font->info.font_size;
            cursor_x += 8.f; //TODO: Above line produced large spacing
            continue;
        }

        // Adjust cursor for new lines
        if (ch == '\n') {
            cursor_x = 0.f;
            cursor_y += text_font->common.line_height;
            continue;
        }

        auto char_data = text_font->get_char_info(ch);
        float pos_x = cursor_x + char_data.x_offset;
        float pos_y = cursor_y + char_data.y_offset;

        float uv_left   = char_data.x / bitmap_width;
        float uv_right  = uv_left + (char_data.width / bitmap_width);
        float uv_top    = char_data.y / bitmap_height;
        float uv_bottom = uv_top + (char_data.height / bitmap_height);

        buffer_data[ch_index * 24 +  0] = pos_x;
        buffer_data[ch_index * 24 +  1] = pos_y;
        buffer_data[ch_index * 24 +  2] = uv_left;
        buffer_data[ch_index * 24 +  3] = uv_top;

        buffer_data[ch_index * 24 +  4] = pos_x;
        buffer_data[ch_index * 24 +  5] = pos_y + char_data.height;
        buffer_data[ch_index * 24 +  6] = uv_left;
        buffer_data[ch_index * 24 +  7] = uv_bottom;

        buffer_data[ch_index * 24 +  8] = pos_x + char_data.width;
        buffer_data[ch_index * 24 +  9] = pos_y;
        buffer_data[ch_index * 24 + 10] = uv_right;
        buffer_data[ch_index * 24 + 11] = uv_top;


        buffer_data[ch_index * 24 + 12] = pos_x + char_data.width;
        buffer_data[ch_index * 24 + 13] = pos_y;
        buffer_data[ch_index * 24 + 14] = uv_right;
        buffer_data[ch_index * 24 + 15] = uv_top;

        buffer_data[ch_index * 24 + 16] = pos_x;
        buffer_data[ch_index * 24 + 17] = pos_y + char_data.height;
        buffer_data[ch_index * 24 + 18] = uv_left;
        buffer_data[ch_index * 24 + 19] = uv_bottom;

        buffer_data[ch_index * 24 + 20] = pos_x + char_data.width;
        buffer_data[ch_index * 24 + 21] = pos_y + char_data.height;
        buffer_data[ch_index * 24 + 22] = uv_right;
        buffer_data[ch_index * 24 + 23] = uv_bottom;

        cursor_x += char_data.x_advance;
        ch_index++;
    }

    // Update VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * valid_character_count * 24, buffer_data, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw buffer
    text_font->bitmap->bind();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, valid_character_count * 6);
    glBindVertexArray(0);

    delete[] buffer_data;
}

glm::vec2 TextRenderer::measure_string(std::string str, glm::vec2 scale) {
    float cursor_x = 0.f;
    float cursor_y = text_font->common.line_height;

    float max_width = 0.f;

    int ch_index = 0;
    for (auto& ch : str) {
        //Skip spaces
        if (ch == ' ') {
            cursor_x += text_font->info.font_size;
            continue;
        }

        //Adjust cursor for new lines
        if (ch == '\n') {
            if (cursor_x > max_width)
                max_width = cursor_x;

            cursor_x  = 0.f;
            cursor_y += text_font->common.line_height;
            continue;
        }

        minalear::font_char char_data = text_font->get_char_info(ch);
        cursor_x += char_data.x_advance;
        ch_index++;
    }

    return glm::vec2(cursor_x, cursor_y) * scale;

}
