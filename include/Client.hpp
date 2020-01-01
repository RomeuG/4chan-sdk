#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <Download.hpp>
#include <Post.hpp>
#include <Thread.hpp>
#include <json.hpp>

auto _get_post(nlohmann::json& post) -> Post;
auto _get_thread(nlohmann::json& thread) -> Thread;

auto get_thread(std::string const& board, std::string const& thread) -> Thread;

#endif