#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <string>
#include <string_view>
#include <utility>

namespace OK
{
static constexpr std::string_view operators_in_sv {"><+-[].,"};

static constexpr uint16_t TAPE_SIZE {30'000U};

class BrainFuck final
{
public:
	BrainFuck();
	explicit BrainFuck(const std::string_view);
	explicit BrainFuck(const std::string&);

	bool parse();

	static std::string& strip_non_bf_characters(std::string&);

private:
	std::array<uint8_t, TAPE_SIZE> m_tape;
	std::uint16_t m_data_pointer;
	std::string_view m_str;

	size_t handle_operator(const size_t);
	inline size_t find_previous_open_bracket(size_t);
	inline size_t find_next_close_bracket(size_t);
};
}	 // namespace OK
