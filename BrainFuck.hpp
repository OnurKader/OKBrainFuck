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
enum class BrainFuckOperators : uint8_t
{
	Right = '>',
	Left = '<',
	Add = '+',
	Sub = '-',
	Open = '[',
	Close = ']',
	Print = '.',
	Input = ','
};

static constexpr std::array operators_in_array {'>', '<', '+', '-', '[', ']', '.', ','};
static constexpr std::string_view operators_in_sv {"><+-[].,"};

static constexpr uint64_t TAPE_SIZE = 30000ULL;

class BrainFuck final
{
public:
	BrainFuck();
	explicit BrainFuck(const std::string_view);

	std::string_view& code();
	const std::string_view& code() const;

	static std::string& strip_non_bf_characters(std::string&);

private:
	std::array<uint8_t, TAPE_SIZE> m_tape;
	std::string_view m_str;
};
}	 // namespace OK
