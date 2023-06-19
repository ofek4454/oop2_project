#pragma once
#include <exception>

class GameException : public std::exception {
public:
    explicit GameException(const char * msg) : message(msg) {}

    const char* what() const noexcept{
        return message;
    }

private:
    const char * message;
};