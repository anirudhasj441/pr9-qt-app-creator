/// @file: empty_input_exception.h
///
/// Declaration of EmptyInputException class
/// 
/// @author: Anirudha Jadhav(Devil) <anirudhasj441@gmail.com>
///
/// @version: 1.0
/// 
/// (C)2025 Coding Devil.
/// https://www.codingdevil.com/

#ifndef EMPTY_INPUT_EXCEPTION_H
#define EMPTY_INPUT_EXCEPTION_H

#include <exception>
#include <string>


class EmptyInputException: public std::exception {

public:
    /// constructor
    EmptyInputException();

    /// returns the error message
    const char* what() const noexcept override;

private:
    std::string mMessage{"Empty value not allowed!"}; // Error messahe

};

#endif //EMPTY_INPUT_EXCEPTION_H
