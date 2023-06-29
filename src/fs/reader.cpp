#include <filesystem>
#include <iostream>
#include <vector>

#include "reader.hpp"

#define str std::string

namespace fs = std::filesystem;

struct colors {
	str reset = "\033[0m";
	str red = "\033[31m";
	str green = "\033[32m";
	str yellow = "\033[33m";
	str blue = "\033[34m";
	str cyan = "\033[36m";
};

namespace reader {

std::vector<file_entry> crawl_dir(parser::args opts)
{
	std::vector<file_entry> files;

	for (const auto &entry : fs::directory_iterator(opts.path)) {
		auto path = entry.path();

		if (path.empty() || path.filename().empty()) continue;
		if (path.filename().string()[0] == '.' && !opts.show_hidden) continue;

		auto file = file_entry(path);
		file.base_name = path.filename().string();

		if (entry.is_directory()) {
			file.type = file_type::directory;
		} else if (entry.is_symlink()) {
			file.type = file_type::symlink;
		} else if (entry.is_regular_file()) {
			file.type = file_type::file;
		} else {
			file.type = file_type::unknown;
		}

		file.file_size = file.type == file_type::directory ? file.calculate_dir_size() : entry.file_size();

		files.push_back(file);
	}

	return files;
}

uintmax_t file_entry::calculate_dir_size()
{
	size_t size = 0;

	for (const auto &entry : fs::recursive_directory_iterator(path)) {
		if (entry.is_regular_file()) { size += entry.file_size(); }
	}

	return size;
}

void print_normal(std::vector<file_entry> files)
{
	std::string text;

	for (auto file : files) {
		str file_text = "";

		if (file.is_dir()) {
			file_text = with_color(file.base_name, colors().cyan);
		} else if (file.is_symlink()) {
			file_text = with_color(file.base_name, colors().blue);
		} else if (file.is_binary()) {
			file_text = with_color(file.base_name, colors().red);
		} else if (file.is_unknown()) {
			file_text = with_color(file.base_name, colors().yellow);
		} else {
			file_text = file.base_name;
		}

		text += file_text + "\t";
	}

	std::cout << text << std::endl;
}

str with_color(str text, str color)
{
	return color + text + colors().reset;
}

}  // namespace reader
