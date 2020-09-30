#include <JsonUtils.hpp>

namespace channer::json
{
auto get_file(nlohmann::json& post, std::string const& board) -> File
{
    File file;

    file.name = post["filename"].get<std::string>();

    GET_VAL<std::string>(post, "ext", file.ext);

    GET_VAL<int>(post, "w", file.w);
    GET_VAL<int>(post, "h", file.h);

    GET_VAL<int>(post, "tn_w", file.tn_w);
    GET_VAL<int>(post, "tn_h", file.tn_h);

    GET_VAL<long long>(post, "tim", file.tim);
    GET_VAL<int>(post, "time", file.time);

    GET_VAL<std::string>(post, "md5", file.md5);

    GET_VAL<int>(post, "fsize", file.size);

    // build the full url
    file.url = "http://i.4cdn.org/" + board + "/" + std::to_string(file.tim) + file.ext;

    return file;
}

auto get_post(nlohmann::json const& json, std::string const& board) -> Post
{
    //auto post = json.get<Post>();
    auto post = Post::from_json(json);

    if (post.file.has_value()) {
        post.file->url = "http://i.4cdn.org/" + board + "/" + std::to_string(post.file->tim) + post.file->ext;
    }

    return post;
}

auto get_catalog_entry(nlohmann::json& catalog, std::string const& board) -> CatalogEntry
{
    CatalogEntry catalog_obj;

    GET_VAL<int>(catalog, "no", catalog_obj.postnumber);
    GET_VAL<int>(catalog, "sticky", catalog_obj.sticky);
    GET_VAL<int>(catalog, "closed", catalog_obj.closed);

    GET_VAL<std::string>(catalog, "now", catalog_obj.now);
    GET_VAL<std::string>(catalog, "name", catalog_obj.name);
    GET_VAL<std::string>(catalog, "sub", catalog_obj.sub);

    if (!catalog["com"].empty()) {
        auto text_obj = channer::html::get_post_text(catalog);
        catalog_obj.text = text_obj;
    }

    if (!catalog["filename"].empty()) {
        auto file_obj = get_file(catalog, board);
        catalog_obj.file = file_obj;
    }

    GET_VAL<int>(catalog, "resto", catalog_obj.resto);

    GET_VAL<std::string>(catalog, "id", catalog_obj.id);
    GET_VAL<std::string>(catalog, "capcode", catalog_obj.capcode);
    GET_VAL<std::string>(catalog, "country", catalog_obj.country);

    GET_VAL<int>(catalog, "bumplimit", catalog_obj.bumplimit);
    GET_VAL<int>(catalog, "imagelimit", catalog_obj.imagelimit);

    GET_VAL<std::string>(catalog, "semantic_url", catalog_obj.semantic_url);
    GET_VAL<std::string>(catalog, "country_name", catalog_obj.country_name);

    GET_VAL<int>(catalog, "replies", catalog_obj.replies);
    GET_VAL<int>(catalog, "images", catalog_obj.images);
    GET_VAL<int>(catalog, "omitted_posts", catalog_obj.omitted_posts);
    GET_VAL<int>(catalog, "omitted_images", catalog_obj.omitted_images);

    // get last replies
    if (!catalog["last_replies"].empty()) {
        for (nlohmann::json& reply : catalog["last_replies"]) {
            auto post_obj = get_post(reply, board);
            catalog_obj.last_replies.emplace_back(post_obj);
        }
    }

    GET_VAL<int>(catalog, "last_modified", catalog_obj.last_modified);

    return catalog_obj;
}

auto get_board(nlohmann::json& board) -> Board
{
    Board board_obj;

    GET_VAL<std::string>(board, "board", board_obj.board);
    GET_VAL<std::string>(board, "title", board_obj.title);

    GET_VAL<int>(board, "ws_board", board_obj.ws_board);
    GET_VAL<int>(board, "per_page", board_obj.per_page);
    GET_VAL<int>(board, "pages", board_obj.pages);
    GET_VAL<int>(board, "max_filesize", board_obj.max_filesize);
    GET_VAL<int>(board, "max_webm_filesize", board_obj.max_webm_filesize);
    GET_VAL<int>(board, "max_comment_chars", board_obj.max_comment_chars);
    GET_VAL<int>(board, "max_webm_duration", board_obj.max_webm_duration);
    GET_VAL<int>(board, "bump_limit", board_obj.bump_limit);
    GET_VAL<int>(board, "image_limit", board_obj.image_limit);

    if (!board["cooldowns"].empty()) {
        board_obj.cooldowns.images = board["cooldowns"]["images"].get<int>();
        board_obj.cooldowns.replies = board["cooldowns"]["replies"].get<int>();
        board_obj.cooldowns.threads = board["cooldowns"]["threads"].get<int>();
    }

    GET_VAL<std::string>(board, "meta_description", board_obj.meta_description);

    GET_VAL<int>(board, "user_ids", board_obj.user_ids);
    GET_VAL<int>(board, "country_flags", board_obj.country_flags);
    GET_VAL<int>(board, "forced_anon", board_obj.forced_anon);
    GET_VAL<int>(board, "spoilers", board_obj.spoilers);
    GET_VAL<int>(board, "custom_spoilers", board_obj.custom_spoilers);
    GET_VAL<int>(board, "is_archived", board_obj.is_archived);
    GET_VAL<int>(board, "require_subject", board_obj.require_subject);
    GET_VAL<int>(board, "sjis_tags", board_obj.sjis_tags);
    GET_VAL<int>(board, "oekaki", board_obj.oekaki);
    GET_VAL<int>(board, "troll_flags", board_obj.troll_flags);
    GET_VAL<int>(board, "webm_audio", board_obj.webm_audio);
    GET_VAL<int>(board, "min_image_width", board_obj.min_image_width);
    GET_VAL<int>(board, "min_image_height", board_obj.min_image_height);
    GET_VAL<int>(board, "math_tags", board_obj.math_tags);

    return board_obj;
}

auto get_thread(nlohmann::json& thread, std::string const& board) -> Thread
{
    Thread thread_obj;

    thread_obj.posts.reserve(thread["posts"].size());

    for (nlohmann::json& post : thread["posts"]) {
        Post post_info;

        post_info = get_post(post, board);

        thread_obj.posts.emplace_back(post_info);
    }

    return thread_obj;
}

auto get_catalog(nlohmann::json& catalog, std::string const& board) -> Catalog
{
    Catalog catalog_obj;

    catalog_obj.entries.reserve(220);

    for (nlohmann::json& page : catalog) {
        for (nlohmann::json& entry : page["threads"]) {
            auto catalog_entry = get_catalog_entry(entry, board);
            catalog_obj.entries.emplace_back(catalog_entry);
        }
    }

    return catalog_obj;
}

auto get_boards(nlohmann::json& boards) -> Boards
{
    Boards boards_obj;

    boards_obj.boards.reserve(100);

    for (nlohmann::json& board : boards["boards"]) {
        auto board_obj = get_board(board);
        boards_obj.boards.emplace_back(board_obj);
    }

    for (auto& el : boards["troll_flags"].items()) {
        boards_obj.troll_flags_list[el.key()] = el.value();
    }

    return boards_obj;
}

auto dump_thread(nlohmann::json& thread) -> std::string
{
    return thread.dump(4);
}

auto dump_catalog(nlohmann::json& catalog) -> std::string
{
    return catalog.dump(4);
}
}
