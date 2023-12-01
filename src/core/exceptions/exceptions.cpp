#include <string>
#include "./exceptions.hpp"

using namespace excep;

HomePathNotFoundedException::HomePathNotFoundedException(const std::string& message): message_(message) {}
const char* HomePathNotFoundedException::what() const throw() {
	return message_.c_str();
}

BaseDirectoryCreationException::BaseDirectoryCreationException(const std::string& message): message_(message) {}
const char* BaseDirectoryCreationException::what() const throw() {
	return message_.c_str();
}

FileOpenException::FileOpenException(const std::string& message): message_(message) {}
const char* FileOpenException::what() const throw() {
	return message_.c_str();
}

FileCreationException::FileCreationException(const std::string& message): message_(message) {}
const char* FileCreationException::what() const throw() {
	return message_.c_str();
}