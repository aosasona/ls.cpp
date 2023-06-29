#include "../cmdline/parser.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

namespace reader {

enum file_type { file, directory, symlink, unknown };

struct file_entry {
	fs::path path;
	std::string base_name;
	int file_size;
	file_type type;

	file_entry(std::string name) : path(name), base_name(""), file_size(0), type(file_type::file) {}

	uintmax_t calculate_dir_size();

	bool is_dir()
	{
		return type == file_type::directory;
	}
	bool is_file()
	{
		return type == file_type::file;
	}
	bool is_symlink()
	{
		return type == file_type::symlink;
	}
	bool is_unknown()  // could be  a socket, a pipe, etc. - temporarily ignore these and use the yellow color
	{
		return type == file_type::unknown;
	}

	bool is_binary()
	{

		std::ifstream file(path, std::ios::binary);
		if (!file.is_open()) { return false; }

		const int bufferSize = 1024;
		std::vector<char> buffer(bufferSize);

		// Read a portion of the file into the buffer
		file.read(buffer.data(), bufferSize);

		// Check for non-printable characters in the buffer
		for (char ch : buffer) {
			if (ch < 7 || (ch > 13 && ch < 32)) {
				file.close();
				return true;  // File contains non-printable characters, indicating binary content
			}
		}

		file.close();
		return false;
	}
};

std::vector<file_entry> crawl_dir(parser::args opts);

void print_normal(std::vector<file_entry> files);

std::string with_color(std::string str, std::string color);

};	// namespace reader
