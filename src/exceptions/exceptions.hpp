#pragma once
#include <string>

namespace excep {
	class HomePathNotFoundedException : public std::exception {
		public:
			HomePathNotFoundedException(const std::string& message);
			
			virtual const char* what() const throw();

		private:
			std::string message_;
	};
	
	class FileOpenException : public std::exception {
	public:
		FileOpenException(const std::string& message): message_(message) {}
		
		virtual const char* what() const throw() {
			return message_.c_str();
		}

	private:
		std::string message_;
	};
}