#include "BrainFuck.hpp"

#include <cxxopts/cxxopts.hpp>
#include <fmt/format.hpp>
#include <fstream>

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
}

int main(int argc, char** argv)
{
	OK::BrainFuck bf;
	const auto& [strip, in_place] = init_commandline_options(argc, argv);
	if(strip)
	{
		if(argc == 1)
		{
			fmt::print(stderr,
					   "\033[31;1mERROR! No file provided but the flag -s, --strip has been "
					   "passed\033[m\n");
			return 1;
		}

		std::string temp("[]+-,.<<<<<>,><.<.+.");
		OK::BrainFuck::strip_non_bf_characters(temp);
		fmt::print("Stripped: {}\n", temp);
	}

	return 0;
}
