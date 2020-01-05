#include <Client.hpp>
#include <cstdio>

auto get_thread(std::string const& board, std::string const& thread, bool file_only = false) -> Thread
{
    auto website = channer::endpoints::URL_THREAD + board + channer::endpoints::TYPE_THREAD + thread + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        return Thread();
    }

    auto json = nlohmann::json::parse(download);
    return _get_thread(json, board, file_only);
}

auto get_media(std::string const& url, std::string const& thread, long long const tim, std::string const& extension) -> void
{
    if (!std::filesystem::exists(thread)) {
        if (!std::filesystem::create_directory(thread)) {
            std::printf("Error creating directory.\n");
        }
    }

    auto absolute_path = std::filesystem::absolute(thread);
    absolute_path.append(std::to_string(tim) + extension);

    if (!std::filesystem::exists(absolute_path)) {
        channer::download_media(url, absolute_path);
    }
}

auto get_media(std::string const& url, int const thread, long long const tim, std::string const& extension) -> bool
{
    auto t = std::to_string(thread);
    auto res = true;

    if (!std::filesystem::exists(t)) {
        if (!std::filesystem::create_directory(t)) {
            std::printf("Error creating directory.\n");
        }
    }

    auto absolute_path = std::filesystem::absolute(t);
    absolute_path.append(std::to_string(tim) + extension);

    if (!std::filesystem::exists(absolute_path)) {
        res = channer::download_media(url, absolute_path);
    }

    return res;
}

auto get_images_from_thread(Thread const& thread) -> bool
{
    auto res = true;

    for (auto& post : thread.posts) {
        if (post.file.has_value()) {
            auto f = post.file.value();
            res = get_media(f.url, thread.posts[0].postnumber, f.tim, f.ext);
        }
    }

    return res;
}

auto get_images_from_thread(std::string const& board, std::string const& thread) -> bool
{
    auto res = true;
    auto t = get_thread(board, thread, true);

    for (auto& post : t.posts) {
        if (post.file.has_value()) {
            auto f = post.file.value();
            res = get_media(f.url, t.posts[0].postnumber, f.tim, f.ext);
        }
    }

    return res;
}

auto get_images_from_thread(Thread const& thread, std::function<void(bool)> success, std::function<void(bool)> failure) -> void
{
    auto t = get_images_from_thread(thread);

    if (t) {
        success(t);
    } else {
        failure(t);
    }
}

auto get_images_from_thread(std::string const& board, std::string const& thread, std::function<void(bool)> success, std::function<void(bool)> failure) -> void
{
    auto t = get_images_from_thread(board, thread);

    if (t) {
        success(t);
    } else {
        failure(t);
    }
}
