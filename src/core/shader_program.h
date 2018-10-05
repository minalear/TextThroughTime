//
// Created by Trevor Fisher on 1/19/2018.
//

#ifndef MINALEAR_SHADER_H
#define MINALEAR_SHADER_H

#include <map>
#include "glad/glad.h"
#include "glm.hpp"

typedef std::pair<const char*, int> ShaderUniformLoc;

namespace minalear {
    class shader_program {
    private:
        GLuint programID;

        std::map<const char*, int> uniform_map;
        int32_t get_uniform_location(const char* name);

    public:
        shader_program(const char *, const char *);
        GLuint id();
        void use();
        void load_shaders(const char *, const char *);

        void set_uniform(const char* name, bool value);
        void set_uniform(const char* name, glm::vec2 &value);
        void set_uniform(const char* name, glm::vec3 &value);
        void set_uniform(const char* name, glm::vec4 &value);
        void set_uniform(const char* name, glm::mat4 &matrix);
    };
}

#endif //MINALEAR_SHADER_H
