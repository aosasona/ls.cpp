#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace parser {

// exception class
class ParserException : public std::exception {
  private:
	std::string message;

  public:
	ParserException(std::string msg) : message(msg) {}
	const char *what() const noexcept
	{
		return message.c_str();
	}
};

struct args {
  public:
	fs::path path;
	bool show_hidden;
	bool long_format;
	// constructors are defined with the same name as the class or struct, with no return type;
	args() : path(fs::current_path()), show_hidden(false), long_format(false) {}

	void var_dump();

	bool validate_path();
};

// function declarations
args parse_args(int argc, char **argv);
std::string trim(const std::string &str);

};	// namespace parser
