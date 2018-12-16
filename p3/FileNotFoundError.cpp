#include "FileNotFoundError.h"

FileNotFoundError::FileNotFoundError(const string& error) : ArkanoidError(error) {

}

FileNotFoundError::~FileNotFoundError() {}
