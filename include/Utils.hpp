#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <string>
#include <utility>

#include <Constants.hpp>

namespace channer::utils
{
auto replace(std::string& str, std::string_view const from, std::string_view const to) -> void;
auto create_media_path(std::string const& dir, long long const tim, std::string const& extension) -> std::string;
auto create_media_url(std::string const& board, long long const tim, std::string const& extension) -> std::string;
#ifdef MOCKDATA
auto load_file(std::string const& path) -> std::string;
#endif
}

#endif
