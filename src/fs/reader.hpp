#include "../cmdline/parser.hpp"

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
};

std::vector<file_entry> crawl_dir(parser::args opts);

void print_normal(std::vector<file_entry> files);

};	// namespace reader
