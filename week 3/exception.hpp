#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP


#include <string>
#include <exception>


class end_of_file : public std::exception{
private:
	std::string message = "end of file reached";

public:
	const char* what() const noexcept override {
		return message.c_str();
	}

};

class unknown_shape : public std::exception{
private:
	std::string message;

public:
	unknown_shape(std::string name):
		message( std::string( "unknown_shape \'") + name + "\'" + "found in config.txt")
	{}

	const char* what() const noexcept override {
		return message.c_str();
	}

};


class unknown_color : public std::exception{
private:
	std::string message;

public:
	unknown_color( std::string name ):
		message( std::string( "unknown_color \'") + name + "\'" + "found in config.txt")
	{}

	const char* what() const noexcept override {
		return message.c_str();
	}
};


class invalid_position : public std::exception{
private:
	std::string message;

public:
	invalid_position( char c ):
		message( std::string( "invalid position \'") + c + "\'" + "found in config.txt")
	{}

	const char* what() const noexcept override {
		return message.c_str();
	}
};


#endif //EXCEPTION_HPP
