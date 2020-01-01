#include <Client.hpp>

// TODO: finish this function
auto _get_post(nlohmann::json& post) -> Post
{
    Post post_obj;

    if (!post["no"].empty()) {
        post_obj.postnumber = post["no"].get<int>();
    }

    if (!post["name"].empty()) {
        post_obj.name = post["name"].get<std::string>();
    }

    return post_obj;
}

auto _get_thread(nlohmann::json& thread) -> Thread
{
    Thread thread_obj;

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