//
// Created by minal on 1/5/2019.
//

#include "error_handling.h"

LuaError::LuaError(lua_State *L) {
    ML = L;
}
LuaError::~LuaError() {}
const char* LuaError::what() const throw() {
    const char *str = lua_tostring(ML, -1);
    if (str == nullptr) {
        str = "Unrecognized LUA error.";
    }

    return str;
}