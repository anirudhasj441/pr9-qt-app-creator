/// @file: empty_input_exception.cpp
///
/// Implementation of EmptyInputException class
/// This class is inherited from std::exception.
/// It is used to throw exception when user input is empty.
/// 
/// @author: Anirudha Jadhav(Devil) <anirudhasj441@gmail.com>
///
/// @version: 1.0
/// 
/// (C)2025 Coding Devil.
/// https://www.codingdevil.com/


#include "empty_input_exception.h"

EmptyInputException::
EmptyInputException( ) {
    /// Nothing Here yet.

}

const char* EmptyInputException::
what() const noexcept {
    return this->mMessage.c_str();
}

