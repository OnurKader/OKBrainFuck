#include "BrainFuck.hpp"

namespace OK
{
BrainFuck::BrainFuck() : m_tape {0U}, m_str() {}

BrainFuck::BrainFuck(const std::string_view str) : m_tape {0U}, m_str(str) {}

std::string_view& BrainFuck::code() { return m_str; }
const std::string_view& BrainFuck::code() const { return m_str; }

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

}	 // namespace OK
