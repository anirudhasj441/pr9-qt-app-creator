#ifndef EMPTY_INPUT_EXCEPTION_H
#define EMPTY_INPUT_EXCEPTION_H

#include <exception>
#include <string>


class EmptyInputException: public std::exception {

public:
    EmptyInputException();

    const char* what() const noexcept override;

private:
    std::string mMessage{"Empty value not allowed!"};

};

#endif //EMPTY_INPUT_EXCEPTION_H
