//
// Created by Trevor Fisher on 1/19/2018.
//

#include <cstdio>
#include "glad/glad.h"
#include "shader_program.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

bool checkShaderCompilation(GLuint shaderID) {
    GLint compileStatus = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {
        GLchar errorMessage[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, errorMessage);
        printf("Shader Compilation Error, %s\n", errorMessage);
    }
}

minalear::shader_program::shader_program(const char *vertexSource, const char *fragmentSource) {
    programID = glCreateProgram();
    load_shaders(vertexSource, fragmentSource);
}
GLuint minalear::shader_program::id() {
    return programID;
}
void minalear::shader_program::use() {
    glUseProgram(programID);
}
void minalear::shader_program::load_shaders(const char *vertexSource, const char *fragmentSource) {
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexSource, nullptr);
    glCompileShader(vertexShaderID);
    checkShaderCompilation(vertexShaderID);

    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShaderID);
    checkShaderCompilation(fragmentShaderID);

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

int32_t minalear::shader_program::get_uniform_location(const char *name) {
    // Inserts the name and returns the uniform location if the name isn't already in the map
    if (uniform_map.find(name) == uniform_map.end()) {
        int loc = glGetUniformLocation(programID, name);
        uniform_map.insert(ShaderUniformLoc(name, loc));

        return loc;
    }

    return uniform_map[name];
}

void minalear::shader_program::set_uniform(const char *name, bool value) {
    glUniform1i(get_uniform_location(name), value);
}

void minalear::shader_program::set_uniform(const char *name, glm::vec2 &value) {
    glUniform2f(get_uniform_location(name), value.x, value.y);
}

void minalear::shader_program::set_uniform(const char *name, glm::vec3 &value) {
    glUniform3f(get_uniform_location(name), value.x, value.y, value.z);
}

void minalear::shader_program::set_uniform(const char *name, glm::vec4 &value) {
    glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w);
}

void minalear::shader_program::set_uniform(const char *name, glm::mat4 &matrix) {
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(matrix));
}