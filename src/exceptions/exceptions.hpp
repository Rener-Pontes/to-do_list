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

	class BaseDirectoryCreationException : public std::exception {
	public:
		BaseDirectoryCreationException(const std::string& message);
		
		virtual const char* what() const throw();

	private:
		std::string message_;
	};
	
	class FileOpenException : public std::exception {
	public:
		FileOpenException(const std::string& message);
		
		virtual const char* what() const throw();

	private:
		std::string message_;
	};

	class FileCreationException : public std::exception {
	public:
		FileCreationException(const std::string& message);
		
		virtual const char* what() const throw();

	private:
		std::string message_;
	};
}