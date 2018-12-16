#include "FileFormatError.h"

FileFormatError::FileFormatError(const string& error) : ArkanoidError(error) {

}

FileFormatError::~FileFormatError() {}
