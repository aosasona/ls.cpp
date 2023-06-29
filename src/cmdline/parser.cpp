#include <cctype>
#include <filesystem>
#include <string>

#include "parser.hpp"

namespace fs = std::filesystem;

namespace parser {

const std::string CURRENT_PATH = fs::current_path().string();

std::string trim(const std::string &str)
{
	std::size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos) return "";	// Handle empty string or all whitespace

	std::size_t last = str.find_last_not_of(' ');
	return str.substr(first, last - first + 1);
}

bool args::validate_path()
{
	if (!fs::exists(path)) { throw ParserException("Directory `" + path.string() + "` does not exist"); }

	if (!fs::is_directory(path)) { throw ParserException("`" + path.string() + "` is not a directory"); }

	return true;
}

void args::var_dump()
{
	std::cout << "filename: " << path << std::endl;
	std::cout << "show_hidden: " << show_hidden << std::endl;
	std::cout << "long_format: " << long_format << std::endl;
}

args parse_args(int argc, char *argv[])
{
	auto parsed_args = args();

	for (int i = 1; i < argc; i++) {
		auto arg = std::string(argv[i]);
		if (arg[0] == '-') {
			if (arg == "-l") {
				parsed_args.long_format = true;
			} else if (arg == "-a") {
				parsed_args.show_hidden = true;
			} else if (arg == "-la" || arg == "-al") {
				parsed_args.show_hidden = true;
				parsed_args.long_format = true;
			} else {
				throw ParserException("Unknown argument: " + arg);
			}

			continue;
		}

		parsed_args.path = trim(arg) == "" ? CURRENT_PATH : trim(arg);
	}

	if (parsed_args.path == "") { parsed_args.path = CURRENT_PATH; }

	parsed_args.path = fs::absolute(parsed_args.path);

	parsed_args.validate_path();

	return parsed_args;
};

};	// namespace parser
