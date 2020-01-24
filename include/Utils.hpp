#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <fstream>
#include <future>
#include <iostream>
#include <string>
#include <utility>

namespace channer::utils
{
auto replace(std::string& str, std::string_view const from, std::string_view const to) -> void;

#ifdef MOCKDATA
auto load_file(std::string const& path) -> std::string;
#endif
}

#endif
