find_library(MINGW32_LIB mingw32
        PATHS
        C:/MinGW/lib
        C:/MinGW/x86_64-w64-mingw32/lib
        C:/MinGW/i686-w64-mingw32/lib
        C:/msys64/mingw32/i686-w64-mingw32/lib)

#include_directories(${MINGW32_INCLUDE})