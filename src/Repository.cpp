#include <Repository.hpp>

namespace channer::repo
{
auto get_thread(std::string const& board, std::string const& thread, bool file_only) -> Thread
{
    auto website = channer::endpoints::URL_THREAD + board + channer::endpoints::TYPE_THREAD + thread + channer::endpoints::FORMAT_JSON;
    auto download = channer::req::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::get_thread(json, board, file_only);
}

auto get_thread_json(std::string const& board, std::string const& thread) -> std::string
{
    auto website = channer::endpoints::URL_THREAD + board + channer::endpoints::TYPE_THREAD + thread + channer::endpoints::FORMAT_JSON;
    auto download = channer::req::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::dump_thread(json, false);
}

auto get_catalog(std::string const& board, bool file_only) -> Catalog
{
#ifndef MOCKDATA
    auto website = channer::endpoints::URL_THREAD + board + "/catalog" + channer::endpoints::FORMAT_JSON;
    auto download = channer::req::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::get_catalog(json, board, file_only);
#else
    auto mock = channer::utils::load_file("../dummy/catalog-po.json");
    auto json = nlohmann::json::parse(mock);
    return channer::json::get_catalog(json, board, file_only);
#endif
}

auto get_catalog_json(std::string const& board) -> std::string
{
#ifndef MOCKDATA
    auto website = channer::endpoints::URL_THREAD + board + "/catalog" + channer::endpoints::FORMAT_JSON;
    auto download = channer::req::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::dump_catalog(json, false);
#else
    auto mock = channer::utils::load_file("../dummy/catalog-po.json");
    auto json = nlohmann::json::parse(mock);
    return channer::json::sanitize_catalog(json);
#endif
}

auto get_boards() -> Boards
{
#ifndef MOCKDATA
    auto website = channer::endpoints::URL_THREAD + std::string("boards") + channer::endpoints::FORMAT_JSON;
    auto download = channer::req::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::get_boards(json);
#else
    auto mock = channer::utils::load_file("../dummy/boards.json");
    auto json = nlohmann::json::parse(mock);
    return channer::json::get_boards(json);
#endif
}

auto search_board(Board const& desired) -> std::vector<Board>
{
    auto boards = get_boards().boards;
    std::vector<Board> found;

    std::mutex m;
#ifndef MOCKDATA
    std::for_each(std::execution::par_unseq, std::begin(boards), std::end(boards), [&](Board const& board) {
#else
    std::for_each(std::execution::seq, std::begin(boards), std::end(boards), [&](Board const& board) {
#endif
        auto valid = false;

        VALIDATE_OPTION(valid, board);
        VALIDATE_OPTION(valid, title);

        VALIDATE_OPTION(valid, ws_board);
        VALIDATE_OPTION(valid, per_page);
        VALIDATE_OPTION(valid, pages);
        VALIDATE_OPTION(valid, max_filesize);
        VALIDATE_OPTION(valid, max_webm_filesize);
        VALIDATE_OPTION(valid, max_comment_chars);
        VALIDATE_OPTION(valid, max_webm_duration);
        VALIDATE_OPTION(valid, bump_limit);
        VALIDATE_OPTION(valid, image_limit);
        VALIDATE_OPTION(valid, meta_description);
        VALIDATE_OPTION(valid, user_ids);
        VALIDATE_OPTION(valid, country_flags);
        VALIDATE_OPTION(valid, forced_anon);
        VALIDATE_OPTION(valid, spoilers);
        VALIDATE_OPTION(valid, custom_spoilers);
        VALIDATE_OPTION(valid, is_archived);
        VALIDATE_OPTION(valid, require_subject);
        VALIDATE_OPTION(valid, sjis_tags);
        VALIDATE_OPTION(valid, oekaki);
        VALIDATE_OPTION(valid, troll_flags);
        VALIDATE_OPTION(valid, webm_audio);
        VALIDATE_OPTION(valid, min_image_width);
        VALIDATE_OPTION(valid, min_image_height);
        VALIDATE_OPTION(valid, math_tags);

        if (valid) {
#ifndef MOCKDATA
            std::lock_guard<std::mutex> lock{ m };
#endif
            found.emplace_back(board);
        }
    });

    return found;
}

auto download_media(std::string const& board, long long const tim, std::string const& extension, std::string const& filename, std::filesystem::path const& path) -> bool
{
    if (!std::filesystem::exists(path)) {
        if (!std::filesystem::create_directory(path)) {
            throw std::runtime_error("Error creating directory");
        }
    }

    auto absolute_path = channer::utils::create_media_path(path, filename, extension);
    if (!std::filesystem::exists(absolute_path)) {
        auto url = channer::utils::create_media_url(board, tim, extension);
        channer::req::download_media(url, absolute_path);
    }

    return true;
}

auto download_media(std::string const& board, long long const tim, std::string const& extension, std::filesystem::path const& path) -> bool
{
    if (!std::filesystem::exists(path)) {
        if (!std::filesystem::create_directory(path)) {
            throw std::runtime_error("Error creating directory");
        }
    }

    auto absolute_path = channer::utils::create_media_path(path, tim, extension);
    if (!std::filesystem::exists(absolute_path)) {
        auto url = channer::utils::create_media_url(board, tim, extension);
        channer::req::download_media(url, absolute_path);
    }

    return true;
}

auto download_media(std::string const& board, std::string const& thread,
                    long long const tim, std::string const& extension) -> bool
{
    if (!std::filesystem::exists(thread)) {
        if (!std::filesystem::create_directory(thread)) {
            throw std::runtime_error("Error creating directory");
        }
    }

    auto absolute_path = channer::utils::create_media_path(thread, tim, extension);
    if (!std::filesystem::exists(absolute_path)) {
        auto url = channer::utils::create_media_url(board, tim, extension);
        channer::req::download_media(url, absolute_path);
    }

    return true;
}

auto download_media(std::string const& url, std::filesystem::path const& path) -> bool
{
    channer::req::download_media(url, path);
    return true;
}
}
