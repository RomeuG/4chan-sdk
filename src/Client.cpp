#include <Client.hpp>
#include <cstdio>

static auto get_thread(std::string const& board, std::string const& thread, bool file_only = false) -> Thread
{
    auto website = channer::endpoints::URL_THREAD + board + channer::endpoints::TYPE_THREAD + thread + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        return Thread();
    }

    auto json = nlohmann::json::parse(download);
    return _get_thread(json, board, file_only);
}

auto get_catalog(std::string const& board) -> Catalog
{
    auto website = channer::endpoints::URL_THREAD + board + "/catalog" + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        return Catalog();
    }

    auto json = nlohmann::json::parse(download);
    return _get_catalog(json, board);
}

static auto get_media(std::string const& url, std::string const& thread, long long const tim, std::string const& extension) -> void
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

static auto get_media(std::string const& url, int const thread, long long const tim, std::string const& extension) -> bool
{
    auto t = std::to_string(thread);
    auto res = true;

    std::printf("Getting media: %s\n", t.c_str());

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

static auto get_images_from_thread(Thread const& thread) -> bool
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

static auto get_images_from_thread(std::string const& board, std::string const& thread) -> bool
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

static auto get_images_from_thread_ff(Thread const& thread) -> void
{
    for (auto& post : thread.posts) {
        if (post.file.has_value()) {
            auto f = post.file.value();
            std::async(std::launch::async, [&]() {
                get_media(f.url, thread.posts[0].postnumber, f.tim, f.ext);
            });
        }
    }
}

auto get_images_from_thread_ff(std::string const& board, std::string const& thread) -> void
{
    auto t = get_thread(board, thread, true);

    for (auto& post : t.posts) {
        if (post.file.has_value()) {
            auto f = post.file.value();
            std::async(std::launch::async, [&]() {
                get_media(f.url, t.posts[0].postnumber, f.tim, f.ext);
            });
        }
    }
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

auto get_catalog(std::string const& board, std::function<void(std::optional<Catalog>)> success, std::function<void(void)> failure) -> void
{
    std::async(std::launch::async, [&]() {
        auto catalog = get_catalog(board);
        if (!catalog.catalog_entries.empty()) {
            success(std::optional<Catalog>(catalog));
        } else {
            failure();
        }
    });
}
