//
// Created by minal on 1/2/2019.
//

#ifndef TEXTTHROUGHTIME_ERROR_HANDLING_H
#define TEXTTHROUGHTIME_ERROR_HANDLING_H

#include <string>
#include <exception>

struct ItemNotFoundException : public std::exception {
    std::string message;

    ItemNotFoundException(const char* item_id) {
        message = "Attempted to use an item not found in the mater table (" + std::string(item_id) + ").";
    }

    const char* what() const throw() {
        return message.c_str();
    }
};

#endif //TEXTTHROUGHTIME_ERROR_HANDLING_H
