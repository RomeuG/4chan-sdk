#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <future>
#include <iostream>
#include <string>
#include <utility>

namespace channer::utils
{
auto replace(std::string& str, std::string_view const from, std::string_view const to) -> void;
}

#endif
