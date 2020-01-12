#ifndef _JSON_UTILS_HPP_
#define _JSON_UTILS_HPP_

#include <Boards.hpp>
#include <Catalog.hpp>
#include <CatalogEntry.hpp>
#include <File.hpp>
#include <HtmlUtils.hpp>
#include <Post.hpp>
#include <Thread.hpp>
#include <json.hpp>
#include <string>

template<typename T>
constexpr auto GET_VAL(nlohmann::json& post, std::string const& key, T& data) -> void
{
    if (!post[key].empty()) {
        data = post[key].get<T>();
    }
}

namespace channer::json
{
auto get_file(nlohmann::json& post, std::string const& board) -> File;

auto get_post(nlohmann::json& post, std::string const& board) -> Post;
auto get_post_file_only(nlohmann::json& post, std::string const& board) -> Post;

auto get_catalog(nlohmann::json& catalog) -> Catalog;
auto get_catalog(nlohmann::json& catalog, std::string const& board, bool file_only = false) -> Catalog;

auto get_thread(nlohmann::json& thread, std::string const& board, bool file_only) -> Thread;

auto get_boards(nlohmann::json& boards) -> Boards;
}

#endif
