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

	return str;
}

}	 // namespace OK
