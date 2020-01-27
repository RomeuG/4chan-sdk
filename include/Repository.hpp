#ifndef _REPOSITORY_HPP_
#define _REPOSITORY_HPP_

#include <Catalog.hpp>
#include <Constants.hpp>
#include <Download.hpp>
#include <JsonUtils.hpp>
#include <Thread.hpp>
#include <execution>

namespace channer::repo
{
#define VALIDATE_OPTION(a, b) validate_option(a, desired.b, board.b);

template<typename T>
auto validate_option(bool& valid, T desired, T board) -> void
{
    return;
}

template<>
inline auto validate_option<int>(bool& valid, int desired, int board) -> void
{
    if (desired != -1) {
        valid = desired == board;
    }
}

template<>
inline auto validate_option<std::string>(bool& valid, std::string desired, std::string board) -> void
{
    if (desired != "") {
        valid = desired == board;
    }
}

auto get_thread(std::string const& board, std::string const& thread, bool file_only = false) -> Thread;
auto get_catalog(std::string const& board, bool file_only = false) -> Catalog;
auto get_boards() -> Boards;
auto search_board(Board const& desired) -> std::vector<Board>;
auto download_media(std::string const& url, std::string const& thread, long long const tim, std::string const& extension) -> bool;
}

#endif
