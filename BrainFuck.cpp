#include "BrainFuck.hpp"

#include <fmt/format.hpp>

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

	str.erase(std::remove_if(str.begin(),
							 str.end(),
							 [](const char& chr) {
								 return operators_in_sv.find(chr) == std::string_view::npos;
							 }),
			  str.end());

	return str;
}

inline ssize_t do_square_brackets_match(const std::string_view str)
{
	ssize_t bracket_count = 0LL;

	bracket_count += std::count(str.cbegin(), str.cend(), '[');
	bracket_count -= std::count(str.cbegin(), str.cend(), ']');

	return bracket_count;
}

size_t BrainFuck::handle_operator(const size_t current_index)
{
	const char current_char_to_parse = m_str[current_index];
	switch(current_char_to_parse)
	{
		case '<': m_data_pointer = (m_data_pointer - 1U) % m_tape.size(); break;
		case '>': m_data_pointer = (m_data_pointer + 1U) % m_tape.size(); break;
		case '-': --m_tape[m_data_pointer]; break;
		case '+': ++m_tape[m_data_pointer]; break;
		case '.': std::putchar(m_tape[m_data_pointer]); break;
		case ',': m_tape[m_data_pointer] = static_cast<uint8_t>(std::getchar()); break;
		case '[': return find_next_close_bracket(current_index);
		case ']': return find_previous_open_bracket(current_index);
		default: break;
	}
	return current_index;
}

size_t BrainFuck::find_previous_open_bracket(size_t index)
{
	if(m_tape[m_data_pointer] == 0U)
		return index;

	size_t bracket_count = 0ULL;
	for(size_t i = index - 1ULL; ~i; --i)
	{
		if(m_tape[i] == ']')
			++bracket_count;
		else if(m_tape[i] == '[')
		{
			if(bracket_count == 0ULL)
				return i;
			--bracket_count;
		}
	}

	return index;
}

size_t BrainFuck::find_next_close_bracket(size_t index)
{
	if(m_tape[m_data_pointer] != 0U)
		return index;

	size_t bracket_count = 0ULL;
	for(size_t i = index + 1ULL; i < m_tape.size(); ++i)
	{
		if(m_tape[i] == '[')
			++bracket_count;
		else if(m_tape[i] == ']')
		{
			if(bracket_count == 0ULL)
				return i;
			--bracket_count;
		}
	}

	return index;
}

bool BrainFuck::parse()
{
	if(do_square_brackets_match(m_str) != 0LL)
		return false;

	size_t current_index = 0ULL;
	while(current_index < m_str.size())
	{
		std::putc(m_str[current_index], stdout);
		current_index = handle_operator(current_index) + 1ULL;
	}

	std::putchar('\n');

	return true;
}

}	 // namespace OK
