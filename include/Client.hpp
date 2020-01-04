#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <Constants.hpp>
#include <Download.hpp>
#include <HtmlUtils.hpp>
#include <Post.hpp>
#include <Text.hpp>
#include <Thread.hpp>
#include <Utils.hpp>
#include <json.hpp>
#include <string>

auto _get_post(nlohmann::json& post) -> Post;
auto _get_thread(nlohmann::json& thread) -> Thread;

auto get_thread(std::string const& board, std::string const& thread) -> Thread;

#endif