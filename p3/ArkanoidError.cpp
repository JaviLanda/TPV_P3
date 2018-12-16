#include "ArkanoidError.h"

ArkanoidError::ArkanoidError(const string& error) : logic_error(error) {

}

ArkanoidError::~ArkanoidError() {}