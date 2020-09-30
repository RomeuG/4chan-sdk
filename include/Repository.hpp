#ifndef _REPOSITORY_HPP_
#define _REPOSITORY_HPP_

#include <Constants.hpp>
#include <Download.hpp>
#include <JsonUtils.hpp>
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

auto get_thread(std::string const& board, std::string const& thread) -> channer::json::Thread;
auto get_thread_json(std::string const& board, std::string const& thread) -> std::string;
auto get_catalog(std::string const& board) -> channer::json::Catalog;
auto get_catalog_json(std::string const& board) -> std::string;
auto get_boards() -> channer::json::Boards;
auto search_board(channer::json::Board const& desired) -> std::vector<channer::json::Board>;

auto download_media(std::string const& board, long long const tim, std::string const& extension, std::string const& filename, std::filesystem::path const& path) -> bool;
auto download_media(std::string const& board, long long const tim, std::string const& extension, std::filesystem::path const& path) -> bool;
auto download_media(std::string const& url, std::string const& thread, long long const tim, std::string const& extension) -> bool;
auto download_media(std::string const& url, std::filesystem::path const& path) -> bool;
}

#endif
