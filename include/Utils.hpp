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

template<typename T, typename F>
auto execute_request(
    F&& request,
    std::function<void(T)> success,
    std::function<void(void)> failure) -> void
{
    try {
        auto res = std::async(std::launch::async,
                              [request = std::forward<F>(request)](auto&&... args) -> T {
                                  return request(std::forward<decltype(args)>(args)...);
                              });

        success(res.get());
    } catch (std::exception const& e) {
        failure();
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
    } catch (std::exception const& e) {
        [failure = std::forward<H>(failure)](auto const&&... args) {
            failure(std::forward<decltype(args)>(args)...);
        }();
    }
}

#endif
