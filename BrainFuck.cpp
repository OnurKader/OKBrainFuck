#include "BrainFuck.hpp"

#include <cstdio>

namespace OK
{
BrainFuck::BrainFuck() : m_tape {0U}, m_data_pointer {0U}, m_str {} {}

BrainFuck::BrainFuck(const std::string_view str) : m_tape {0U}, m_data_pointer {0U}, m_str {str} {}

BrainFuck::BrainFuck(const std::string& str) : m_tape {0U}, m_data_pointer {0U}, m_str(str) {}

std::string& BrainFuck::strip_non_bf_characters(std::string& str)
{
	const size_t character_check = str.find_first_not_of(operators_in_sv);
	if(character_check == str.npos)
		return str;

	size_t index = 0ULL;
	while(index < str.size())
	{
		str.erase(index, str.find_first_of(operators_in_sv));

		++index;

		if(str.find_first_not_of(operators_in_sv, index) == str.npos)
		{
			break;
		}
	}

	return str;
}

bool do_square_brackets_match(const std::string_view str)
{
	size_t bracket_count = 0ULL;

	bracket_count += std::count(str.cbegin(), str.cend(), '[');
	bracket_count -= std::count(str.cbegin(), str.cend(), ']');

	return bracket_count == 0ULL;
}

void BrainFuck::handle_operator(const size_t current_index)
{
	const char current_char = m_str[current_index];
	switch(current_char)
	{
		case '<': m_data_pointer = (m_data_pointer - 1U) % m_tape.size(); break;
		case '>': m_data_pointer = (m_data_pointer + 1U) % m_tape.size(); break;
		case '-': --m_tape[m_data_pointer]; break;
		case '+': ++m_tape[m_data_pointer]; break;
		case '.': std::putchar(m_tape[m_data_pointer]); break;
		case ',': m_tape[m_data_pointer] = std::getchar(); break;
		case '[': /* TODO: Make a function to deal with these */ break;
		case ']': /* TODO: Make a function to deal with these */ break;
		default: break;
	}
}

bool BrainFuck::parse()
{
	if(!do_square_brackets_match(m_str))
		return false;

	size_t current_index = 0ULL;
	while(current_index < m_str.size())
	{
		handle_operator(current_index);
	}

	return true;
}

}	 // namespace OK
