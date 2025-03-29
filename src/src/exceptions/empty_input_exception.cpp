#include "empty_input_exception.h"

EmptyInputException::
EmptyInputException( ) {
    /// Nothing Here yet.

}

const char* EmptyInputException::
what() const noexcept {
    return this->mMessage.c_str();
}

