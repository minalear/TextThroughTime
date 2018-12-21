//
// Created by Trevor Fisher on 10/11/2018.
//

#include "log.h"

// Constructors/Destructors
Log::Log(int capacity) {
    this->capacity = capacity;
    size = 0;
    lines = new std::string[capacity];
}
Log::~Log() {
    delete [] lines;
}

// Private Functions
/// Shifts every item in the list up one
void Log::shift() {
    for (int i = capacity - 1; i > 0; i--) {
        lines[i] = lines[i - 1];
    }
    lines[0] = "";
}

// Public Functions
void Log::add(const std::string str) {
    shift(); // Shift all items up one
    lines[0] = str;
    size++;
}
void Log::remove(int i) {
    //TODO: Actually write this function wtf
}
void Log::clear() {
    for (int i = 0; i < capacity; i++) {
        lines[i] = "";
    }
}
int Log::count() {
    return size;
}

std::string Log::operator[](int i) {
    if (i < 0 || i >= capacity) {
        return "<NULL>";
    }

    return lines[i];
}
