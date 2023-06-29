#include "fs/reader.hpp"
#include <vector>

int main(int argc, char **argv)
{
	try {
		auto args = parser::parse_args(argc, argv);
		auto files = reader::crawl_dir(args);
		reader::print_normal(files);
		return 0;
	} catch (parser::ParserException e) {
		std::cout << e.what() << std::endl;
	} catch (std::filesystem::filesystem_error e) {
		std::cout << e.what() << std::endl;
	} catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	return 1;
}
