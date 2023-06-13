#pragma once
#include <exception>

class HttpException : public std::exception {
public:
    explicit HttpException(const char * msg) : message(msg) {}

    const char* what() const noexcept{
        return message;
    }

private:
    const char * message;
};