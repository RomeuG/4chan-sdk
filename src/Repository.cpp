#include <Repository.hpp>

namespace channer::repo
{
auto get_thread(std::string const& board, std::string const& thread, bool file_only) -> Thread
{
    auto website = channer::endpoints::URL_THREAD + board + channer::endpoints::TYPE_THREAD + thread + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::get_thread(json, board, file_only);
}

auto get_catalog(std::string const& board, bool file_only) -> Catalog
{
    auto website = channer::endpoints::URL_THREAD + board + "/catalog" + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::get_catalog(json, board, file_only);
}

auto get_boards() -> Boards
{
#ifndef MOCKDATA
    auto website = channer::endpoints::URL_THREAD + std::string("boards") + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

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
    auto website = channer::endpoints::URL_THREAD + std::string("boards") + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    auto boards = channer::json::get_boards(json).boards;

    std::vector<Board> found;

    std::mutex m;
    std::for_each(std::execution::par_unseq, std::begin(boards), std::end(boards), [&](Board const& board) {
        auto valid = false;

        VALIDATE_OPTION(valid, board);
        VALIDATE_OPTION(valid, title);

        VALIDATE_OPTION(valid, ws_board);
        VALIDATE_OPTION(valid, per_page);
        VALIDATE_OPTION(valid, pages);
        VALIDATE_OPTION(valid, max_filesize);
        VALIDATE_OPTION(valid, max_webm_filesize);
        VALIDATE_OPTION(valid, max_comment_char);
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
            std::lock_guard<std::mutex> lock{ m };
            found.emplace_back(board);
        }
    });

    return found;
}
}
