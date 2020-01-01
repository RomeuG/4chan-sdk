#include <Client.hpp>
#include <cstdio>

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

auto _get_file(nlohmann::json& post) -> File
{
    File file;

    file.name = post["filename"].get<std::string>();

    GET_VAL(post, "ext", file.ext, std::string);
    GET_VAL(post, "w", file.w, int);
    GET_VAL(post, "h", file.h, int);

    GET_VAL(post, "tn_w", file.tn_w, int);
    GET_VAL(post, "tn_h", file.tn_h, int);

    GET_VAL(post, "tim", file.tim, int);
    GET_VAL(post, "time", file.time, int);

    GET_VAL(post, "md5", file.md5, std::string);

    GET_VAL(post, "fsize", file.size, int);

    return file;
}

// TODO: finish this function
auto _get_post(nlohmann::json& post) -> Post
{
    Post post_obj;

    GET_VAL(post, "no", post_obj.postnumber, int);
    GET_VAL(post, "now", post_obj.date, std::string);
    GET_VAL(post, "name", post_obj.name, std::string);
    GET_VAL(post, "sub", post_obj.subject, std::string);

    // TODO: comment (parse the html inside it)
    GET_VAL(post, "com", post_obj.text, std::string);

    // TODO: file
    if (!post["filename"].empty()) {
        auto file_obj = _get_file(post);
        post_obj.file = file_obj;
    }

    GET_VAL(post, "id", post_obj.id, std::string);
    GET_VAL(post, "country", post_obj.country, std::string);
    GET_VAL(post, "country_name", post_obj.country_name, std::string);
    GET_VAL(post, "replies", post_obj.replies, int);
    GET_VAL(post, "images", post_obj.images, int);
    GET_VAL(post, "unique_ips", post_obj.unique_ips, int);
    GET_VAL(post, "tail_size", post_obj.tail_size, int);
    GET_VAL(post, "archived", post_obj.archived, int);
    GET_VAL(post, "archived_on", post_obj.archived_on, int);

    return post_obj;
}

auto _get_thread(nlohmann::json& thread) -> Thread
{
    Thread thread_obj;

    thread_obj.posts.reserve(thread["posts"].size());

    for (nlohmann::json& post : thread["posts"]) {
        auto post_info = _get_post(post);
        thread_obj.posts.push_back(post_info);
    }

    return thread_obj;
}

auto get_thread(std::string const& board, std::string const& thread) -> Thread
{
    auto website = "http://a.4cdn.org/" + board + "/thread/" + thread + ".json";
    auto download = channer::download_json(website.c_str());

    auto json = nlohmann::json::parse(download);
    return _get_thread(json);
}