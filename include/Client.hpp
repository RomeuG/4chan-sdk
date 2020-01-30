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

auto get_thread(std::string const& board, std::string const& thread, std::function<void(std::optional<Thread>)>&& success, std::function<void(std::string const&)>&& failure) -> void;
auto get_thread_files(std::string const& board, std::string const& thread, std::function<void(std::vector<File>)>&& success, std::function<void(std::string const&)>&& failure) -> void;
auto get_catalog(std::string const& board, std::function<void(std::optional<Catalog>)>&& success, std::function<void(std::string const&)>&& failure) -> void;
auto get_catalog_files(std::string const& board, std::function<void(std::vector<File>)>&& success, std::function<void(std::string const&)>&& failure) -> void;
auto get_boards(std::function<void(std::optional<Boards>)>&& success, std::function<void(std::string const&)>&& failure) -> void;
auto search_board(Board const& desired, std::function<void(std::vector<Board>)>&& success, std::function<void(std::string const&)>&& failure) -> void;

auto download_media(std::string const& board, long long const tim,
                    std::string const& extension, std::string const& filename,
                    std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void;

auto download_media(std::string const& board, long long const tim,
                    std::string const& extension, std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void;

auto download_media(std::string const& board, std::string const& thread,
                    long long const tim, std::string const& extension,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void;

auto download_media(std::string const& url, std::filesystem::path const& path,
                    std::function<void(bool)>&& success,
                    std::function<void(std::string const&)>&& failure) -> void;
}
#endif
