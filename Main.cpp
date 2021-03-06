#include "BrainFuck.hpp"

#include <cxxopts/cxxopts.hpp>
#include <fmt/format.hpp>
#include <fstream>

std::pair<bool, bool> init_commandline_options(int& argc, char**& argv);

int handle_strip_case(int argc, char** argv, bool is_in_place);

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		std::string temp;
		fmt::print("> ");
		while(std::getline(std::cin, temp))
		{
			// TODO: Get the strings and push to a vector and capture \033[A or whatever is up/down
			// and do the thing
			OK::BrainFuck bf(temp);
			bf.parse();
			fmt::print("> ");
		}

		return 0;
	}

	const auto& [strip, in_place] = init_commandline_options(argc, argv);

	if(strip)
	{
		return handle_strip_case(argc, argv, in_place);
	}

	// Execute file
	if(!strip && !in_place && argc > 1)
	{
		std::ifstream bf_file(argv[1ULL]);
		const std::string code{std::istreambuf_iterator<char>(bf_file),
							   std::istreambuf_iterator<char>()};
		OK::BrainFuck bf(code);
		return !bf.parse();
	}

	return 1;
}

std::pair<bool, bool> init_commandline_options(int& argc, char**& argv)
{
	try
	{
		cxxopts::Options options("OKBrainFuck", "A bad BrainFuck interpreter written in C++");
		options.add_options()("s,strip", "Strip all commands and whitespace, leave only the 8 ops")(
			"i,in-place", "Change file in-place")("h,help", "Print usage");

		const auto args = options.parse(argc, argv);

		if(args.count("help"))
		{
			fmt::print(stderr, "{}\n", options.help());
			return {false, false};
		}

		return {args.count("strip"), args.count("in-place")};
	}
	catch(const cxxopts::OptionParseException& e)
	{
		fmt::print(stderr, "\033[31;1mUnknown {}!\033[m\n", e.what());
	}
	catch(...)
	{
		fmt::print(stderr, "\033[31;1mUnhandled Exception Thrown!\033[m\n");
	}
	return {false, false};
}

int handle_strip_case(int argc, char** argv, bool is_in_place)
{
	if(argc == 1)
	{
		fmt::print(stderr,
				   "\033[31;1mERROR! No file provided but the flag -s, --strip has been "
				   "passed\033[m\n");
		return 1;
	}

	std::ifstream bf_file(argv[1ULL]);

	if(!bf_file)
	{
		// Wow I should make this error printing into a function
		fmt::print(stderr, "\033[31;1mCouldn't open file {}\033[m\n", argv[1ULL]);
		return 1;
	}

	//	std::string temp((std::istreambuf_iterator<char>(bf_file)),
	//(std::istreambuf_iterator<char>()));
	std::string temp, code;
	code.reserve(256ULL);

	while(std::getline(bf_file, temp))
		code += temp;

	fmt::print("file: {}\n", code);
	bf_file.close();

	// Strip comments
	OK::BrainFuck::strip_non_bf_characters(code);
	fmt::print("After strip: {}\n", code);

	if(is_in_place)
	{
		std::ofstream bf_output(argv[1ULL]);
		if(!bf_output)
		{
			// Wow I should make this error printing into a function
			fmt::print(stderr, "\033[31;1mCouldn't open file {} for write\033[m\n", argv[1ULL]);
			return 1;
		}

		bf_output << code;
	}

	return 0;
}
