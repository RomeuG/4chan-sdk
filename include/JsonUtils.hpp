#ifndef _JSON_UTILS_HPP_
#define _JSON_UTILS_HPP_

#include <Catalog.hpp>
#include <CatalogEntry.hpp>
#include <File.hpp>
#include <HtmlUtils.hpp>
#include <Post.hpp>
#include <Thread.hpp>
#include <json.hpp>
#include <string>

#define GET_VAL(a, b, c, d) \
    if (!a[b].empty()) {    \
        c = a[b].get<d>();  \
    }

#define GET_VAL_STR(a, b, c)         \
    if (!a[b].empty()) {             \
        c = a[b].get<std::string>(); \
    }

#define GET_VAL_INT(a, b, c) \
    if (!a[b].empty()) {     \
        c = a[b].get<int>(); \
    } else {                 \
        c = -1;              \
    }

auto _get_file(nlohmann::json& post, std::string const& board) -> File;

auto _get_post(nlohmann::json& post, std::string const& board) -> Post;
auto _get_post_file_only(nlohmann::json& post, std::string const& board) -> Post;

auto _get_catalog(nlohmann::json& catalog) -> Catalog;
auto _get_catalog(nlohmann::json& catalog, std::string const& board) -> Catalog;

auto _get_thread(nlohmann::json& thread, std::string const& board, bool file_only) -> Thread;

#endif
