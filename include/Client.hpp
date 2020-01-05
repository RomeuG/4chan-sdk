#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <Catalog.hpp>
#include <Constants.hpp>
#include <Download.hpp>
#include <HtmlUtils.hpp>
#include <JsonUtils.hpp>
#include <Post.hpp>
#include <Text.hpp>
#include <Thread.hpp>
#include <Utils.hpp>
#include <functional>
#include <json.hpp>
#include <string>

auto get_catalog(std::string const& board) -> Catalog;
auto get_thread(std::string const& board, std::string const& thread) -> Thread;
auto get_images_from_thread_ff(std::string const& board, std::string const& thread) -> void;
auto get_images_from_thread(std::string const& board, std::string const& thread, std::function<void(bool)> success, std::function<void(bool)> failure) -> void;

#endif