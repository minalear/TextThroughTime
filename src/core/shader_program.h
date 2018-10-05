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
        //TODO: Make this more robust and generic
        int32_t projLoc, viewLoc, modelLoc;

    public:
        shader_program(const char *, const char *);
        GLuint id();
        void use();
        void load_shaders(const char *, const char *);

        void init_uniforms();
        void set_proj_mat4(const glm::mat4 &proj);
        void set_view_mat4(const glm::mat4 &view);
        void set_model_mat4(const glm::mat4 &model);

        void set_uniform_vec3(const char *name, glm::vec3 value);
        void set_uniform_bool(const char *name, bool value);
    };
}

#endif //MINALEAR_SHADER_H
