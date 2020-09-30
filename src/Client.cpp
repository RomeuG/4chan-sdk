#include "Repository.hpp"

#include <Client.hpp>
#include <cstdio>

namespace channer
{
auto get_thread(std::string const& board,
                std::string const& thread,
                std::function<void(std::optional<json::Thread>)>&& success,
                std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<json::Thread>(
        [&]() -> json::Thread {
            return channer::repo::get_thread(board, thread);
        },
        success, failure);
}

auto get_thread_json(std::string const& board,
                     std::string const& thread,
                     std::function<void(std::string)>&& success,
                     std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<std::string>(
        [&]() -> std::string {
            return channer::repo::get_thread_json(board, thread);
        },
        success, failure);
}

auto get_catalog(std::string const& board,
                 std::function<void(std::optional<json::Catalog>)>&& success,
                 std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<json::Catalog>(
        [&]() -> json::Catalog {
            return channer::repo::get_catalog(board);
        },
        success, failure);
}

auto get_catalog_json(std::string const& board,
                      std::function<void(std::string)>&& success,
                      std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<std::string>(
        [&]() -> std::string {
            return channer::repo::get_catalog_json(board);
        },
        success, failure);
}

auto get_boards(std::function<void(std::optional<json::Boards>)>&& success,
                std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<json::Boards>(
        [&]() -> json::Boards {
            return channer::repo::get_boards();
        },
        success, failure);
}

auto search_board(channer::json::Board const& desired,
                  std::function<void(std::vector<channer::json::Board>)>&& success,
                  std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<std::vector<channer::json::Board>>(
        [&]() -> std::vector<channer::json::Board> {
            return channer::repo::search_board(desired);
        },
        success, failure);
}

auto download_media(std::string const& board, long long const tim,
                    std::string const& extension, std::string const& filename,
                    std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<bool>(
        [&]() -> bool {
            return channer::repo::download_media(board, tim, extension, filename, path);
        },
        success, failure);
}

auto download_media(std::string const& board, long long const tim,
                    std::string const& extension, std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<bool>(
        [&]() -> bool {
            return channer::repo::download_media(board, tim, extension, path);
        },
        success, failure);
}

auto download_media(std::string const& board, std::string const& thread,
                    long long const tim, std::string const& extension,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<bool>(
        [&]() -> bool {
            return channer::repo::download_media(board, thread, tim, extension);
        },
        success, failure);
}

auto download_media(std::string const& url, std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<bool>(
        [&]() -> bool {
            return channer::repo::download_media(url, path);
        },
        success, failure);
}
}
