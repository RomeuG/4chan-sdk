#include <Client.hpp>
#include <cstdio>

namespace channer
{
/**
 * @param board The board string (e.g.: "g")
 * @param thread
 * @param success Success callback with a [std::optional<Thread>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_thread(std::string const& board,
                std::string const& thread,
                std::function<void(std::optional<Thread>)>&& success,
                std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<Thread>(
        [&]() -> Thread {
            return channer::repo::get_thread(board, thread, false);
        },
        success, failure);
}

/**
 * @param board
 * @param thread
 * @param success Success callback with a [std::vector<File>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_thread_files(std::string const& board,
                      std::string const& thread,
                      std::function<void(std::vector<File>)>&& success,
                      std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<std::vector<File>>(
        [&]() -> std::vector<File> {
            std::vector<File> files;
            auto thread_obj = channer::repo::get_thread(board, thread, true);

            std::for_each(std::begin(thread_obj.posts), std::end(thread_obj.posts), [&](Post const& post) {
                if (post.file.has_value()) {
                    files.emplace_back(post.file.value());
                }
            });

            return files;
        },
        success, failure);
}

/**
 * @param board
 * @param success Success callback with a [std::optional<Catalog>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_catalog(std::string const& board,
                 std::function<void(std::optional<Catalog>)>&& success,
                 std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<Catalog>(
        [&]() -> Catalog {
            return channer::repo::get_catalog(board);
        },
        success, failure);
}

/**
 * @param board
 * @param success Success callback with a [std::vector<File>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_catalog_files(std::string const& board,
                       std::function<void(std::vector<File>)>&& success,
                       std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<std::vector<File>>(
        [&]() -> std::vector<File> {
            std::vector<File> files;
            auto catalog_obj = channer::repo::get_catalog(board, true);

            std::for_each(std::begin(catalog_obj.entries), std::end(catalog_obj.entries), [&](CatalogEntry const& entry) {
                if (entry.file.has_value()) {
                    files.emplace_back(entry.file.value());
                }
            });

            return files;
        },
        success, failure);
}

/**
 * @param success Success callback with a [std::optional<Boards>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_boards(std::function<void(std::optional<Boards>)>&& success,
                std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<Boards>(
        [&]() -> Boards {
            return channer::repo::get_boards();
        },
        success, failure);
}

/**
 * @param desired
 * @param success Success callback with a [std::vector<Board>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto search_board(Board const& desired,
                  std::function<void(std::vector<Board>)>&& success,
                  std::function<void(std::string const&)>&& failure) -> void
{
    execute_request<std::vector<Board>>(
        [&]() -> std::vector<Board> {
            return channer::repo::search_board(desired);
        },
        success, failure);
}

/**
 * @param board
 * @param tim
 * @param extension
 * @param filename
 * @param path
 * @param success Success callback with a [bool] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
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

/**
 * @param board
 * @param tim
 * @param extension
 * @param path
 * @param success Success callback with a [bool] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
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

/**
 * @param board
 * @param tim
 * @param extension
 * @param success Success callback with a [bool] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
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

/**
 * @param url
 * @param path
 * @param success Success callback with a [bool] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
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
