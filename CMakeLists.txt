cmake_minimum_required(VERSION 3.12)
project(TextThroughTime)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-O2 -static-libgcc -static-libstdc++ -static -lpthread -msse3")
set(CMAKE_CXX_FLAGS "-pg -gdwarf-3 -static-libgcc -static-libstdc++ -static -lpthread -msse3")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

file(GLOB SOURCE_FILES
        src/*.cpp src/*.h
        src/core/*.cpp src/core/*.h
        src/game/*.cpp src/game/*.h
        C:/Libraries/OpenGL/GLAD/src/glad.c)
file(GLOB FONT_FILES fonts/*.fnt fonts/*.png)
file(GLOB SHADER_FILES shaders/*.glsl)
file(GLOB SCRIPT_FILES scripts/*.lua)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/fonts)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/scripts)
file(COPY ${FONT_FILES} DESTINATION ${PROJECT_BINARY_DIR}/fonts)
file(COPY ${SHADER_FILES} DESTINATION ${PROJECT_BINARY_DIR}/shaders)
file(COPY ${SCRIPT_FILES} DESTINATION ${PROJECT_BINARY_DIR}/scripts)

find_package(MINGW32 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Lua REQUIRED)

add_executable(TextThroughTime ${SOURCE_FILES})
target_link_libraries(TextThroughTime ${MINGW32_LIB} ${SDL2_MAIN_LIB} ${SDL2_LIB} ${OPENGL_LIB} ${LUA_LIB})

add_custom_command(
        TARGET TextThroughTime POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Libraries/SDL2/x86/bin/SDL2.dll"
        $<TARGET_FILE_DIR:TextThroughTime>
)
add_custom_command(
        TARGET TextThroughTime POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Libraries/lua-5.3.5/bin/lua53.dll"
        $<TARGET_FILE_DIR:TextThroughTime>
)