//
// Created by Trevor Fisher on 2/3/2018.
//

#include <iostream>
#include <cassert>
#include "window.h"
#include "SDL2/SDL.h"
#include "glad/glad.h"

minalear::GameWindow::GameWindow(const char *title, uint32_t width, uint32_t height) {
    // Initialize SDL and create a window
    SDL_Init(SDL_INIT_VIDEO);

    // Set SDL OpenGL attributes (Core Profile, OpenGL v4.0)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);

    // SDL_GL_SetSwapInterval(0); // VSYNC

    sdl_window = SDL_CreateWindow(title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL);
    client_width  = width;
    client_height = height;

    gl_context = SDL_GL_CreateContext(sdl_window);
    start_time = SDL_GetTicks(); // Used to calculate delta time for our update loop

    int gladLoadSuccess = gladLoadGLLoader(SDL_GL_GetProcAddress);
    assert(gladLoadSuccess);
}

minalear::GameWindow::~GameWindow() {
    SDL_GL_DeleteContext(gl_context);
    SDL_Quit();
}

int minalear::GameWindow::width(){
    return client_width;
}
int minalear::GameWindow::height() {
    return client_height;
}

/// Call once per frame to get the delta time from the previous frame.
float minalear::GameWindow::dt() {
    uint32_t ticks = SDL_GetTicks() - start_time;
    float dt = ticks * 0.001f;
    start_time = SDL_GetTicks();

    return dt;
}

void minalear::GameWindow::swap_buffers() {
    SDL_GL_SwapWindow(sdl_window);
}