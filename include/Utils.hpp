#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <string>

namespace channer::utils
{
	auto replace(std::string& str, std::string_view const from, std::string_view const to) -> void;
}

#endif