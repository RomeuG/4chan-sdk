#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <Catalog.hpp>
#include <Constants.hpp>
#include <Download.hpp>
#include <HtmlUtils.hpp>
#include <JsonUtils.hpp>
#include <Post.hpp>
#include <Repository.hpp>
#include <Text.hpp>
#include <Thread.hpp>
#include <Utils.hpp>
#include <functional>
#include <json.hpp>
#include <string>

namespace channer
{
template<typename T, typename F>
auto execute_request(
    F&& request,
    std::function<void(T)> success,
    std::function<void(std::string const&)> failure) -> void
{
    try {
        auto res = std::async(std::launch::async,
                              [request = std::forward<F>(request)](auto&&... args) -> T {
                                  return request(std::forward<decltype(args)>(args)...);
                              });

        success(res.get());
    } catch (nlohmann::json::parse_error const& e) {
        failure(e.what());
    } catch (std::runtime_error const& e) {
        failure(e.what());
    }
}

template<typename T, typename F, typename G, typename H>
constexpr auto execute_request(
    F&& request,
    G&& success,
    H&& failure) -> void
{
    try {
        auto res = std::async(std::launch::async,
                              [request = std::forward<F>(request)](auto const&&... args) -> T {
                                  return request(std::forward<decltype(args)>(args)...);
                              });

        [success = std::forward<G>(success)](auto const&&... args) {
            success(std::forward<decltype(args)>(args)...);
        }(res.get());
    } catch (nlohmann::json::parse_error const& e) {
        [failure = std::forward<H>(failure), e]() {
            failure(std::forward<std::string const>(e.what()));
        }();
    } catch (std::runtime_error const& e) {
        [failure = std::forward<H>(failure), e]() {
            failure(std::forward<std::string const>(e.what()));
        }();
    }
}

/**
 * Get Thread information
 *
 * @param board The board string (e.g.: "g")
 * @param thread Thread value (e.g.: 74634876)
 * @param success Success callback with a [std::optional<Thread>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_thread(std::string const& board, std::string const& thread, std::function<void(std::optional<Thread>)>&& success, std::function<void(std::string const&)>&& failure) -> void;

/**
 * Get list of files in Thread
 *
 * @param board The board string (e.g.: "g")
 * @param thread Thread value (e.g.: 74634876)
 * @param success Success callback with a [std::vector<File>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_thread_files(std::string const& board, std::string const& thread, std::function<void(std::vector<File>)>&& success, std::function<void(std::string const&)>&& failure) -> void;

/**
 *
 *
 * @param board The board string (e.g.: "g")
 * @param success Success callback with a [std::optional<Catalog>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_catalog(std::string const& board, std::function<void(std::optional<Catalog>)>&& success, std::function<void(std::string const&)>&& failure) -> void;

/**
 * @param board The board string (e.g.: "g")
 * @param success Success callback with a [std::vector<File>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_catalog_files(std::string const& board, std::function<void(std::vector<File>)>&& success, std::function<void(std::string const&)>&& failure) -> void;

/**
 * @param success Success callback with a [std::optional<Boards>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto get_boards(std::function<void(std::optional<Boards>)>&& success, std::function<void(std::string const&)>&& failure) -> void;

/**
 * @param desired [Board] object with the desired fields set
 * @param success Success callback with a [std::vector<Board>] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto search_board(Board const& desired, std::function<void(std::vector<Board>)>&& success, std::function<void(std::string const&)>&& failure) -> void;

/**
 * @param board The board string (e.g.: "g")
 * @param tim Tim value
 * @param extension File extension
 * @param filename File name
 * @param path File directory
 * @param success Success callback with a [bool] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto download_media(std::string const& board, long long const tim,
                    std::string const& extension, std::string const& filename,
                    std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void;

/**
 * @param board The board string (e.g.: "g")
 * @param tim Tim value
 * @param extension File extension
 * @param path File directory
 * @param success Success callback with a [bool] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto download_media(std::string const& board, long long const tim,
                    std::string const& extension, std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void;

/**
 * @param board The board string (e.g.: "g")
 * @param tim Tim value
 * @param extension File extension
 * @param success Success callback with a [bool] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto download_media(std::string const& board, std::string const& thread,
                    long long const tim, std::string const& extension,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void;

/**
 * @param url File URL
 * @param path File path
 * @param success Success callback with a [bool] as parameter
 * @param failure Failure callback with a [std::string] as parameter
 */
auto download_media(std::string const& url, std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void;
}
#endif
