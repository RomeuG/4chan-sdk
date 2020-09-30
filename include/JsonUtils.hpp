#ifndef _JSON_UTILS_HPP_
#define _JSON_UTILS_HPP_

#include <HtmlUtils.hpp>
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

struct Post;
struct Thread;
struct Catalog;
struct CatalogEntry;
struct Boards;
struct Board;
struct File;

auto get_file(nlohmann::json& post, std::string const& board) -> File;

auto get_post(nlohmann::json const& post, std::string const& board) -> Post;

auto get_catalog(nlohmann::json& catalog) -> Catalog;
auto get_catalog(nlohmann::json& catalog, std::string const& board) -> Catalog;

auto get_thread(nlohmann::json& thread, std::string const& board) -> Thread;

auto get_boards(nlohmann::json& boards) -> Boards;

auto dump_thread(nlohmann::json& thread) -> std::string;
auto dump_catalog(nlohmann::json& catalog) -> std::string;

struct File {
    std::string name;
    std::string ext;
    int w;
    int h;
    int tn_w;
    int tn_h;
    long long tim;
    int time;
    std::string md5;
    int size;

    std::string url;
};

struct Cooldowns {
    int threads = -1;
    int replies = -1;
    int images = -1;
};

struct Board {
    std::string board;
    std::string title;

    int ws_board = -1;
    int per_page = -1;
    int pages = -1;
    int max_filesize = -1;
    int max_webm_filesize = -1;
    int max_comment_chars = -1;
    int max_webm_duration = -1;
    int bump_limit = -1;
    int image_limit = -1;

    Cooldowns cooldowns;

    std::string meta_description;
    int user_ids = -1;
    int country_flags = -1;
    int forced_anon = -1;
    int spoilers = -1;
    int custom_spoilers = -1;
    int is_archived = -1;
    int require_subject = -1;
    int sjis_tags = -1;
    int oekaki = -1;
    int troll_flags = -1;
    int webm_audio = -1;
    int min_image_width = -1;
    int min_image_height = -1;
    int math_tags = -1;
};

struct Boards {
    /**
	 * std::vector of Board
	 */
    std::vector<Board> boards;

    /**
	 * std::unordered_map of all available troll flags
	 */
    std::unordered_map<std::string, std::string> troll_flags_list;
};

struct Post {
    int postnumber = -1;
    std::string date;
    std::string name;
    std::string subject;
    std::string tripcode;

    std::optional<File> file = std::nullopt;

    int thread = -1;
    std::string id;
    std::vector<Text> text;
    std::string country;
    std::string country_name;

    int bumplimit = -1;
    int imagelimit = -1;

    int archived = -1;
    int archived_on = -1;

    int replies = -1;
    int images = -1;
    int unique_ips = -1;
    int tail_size = -1;

    static Post from_json(nlohmann::json const& j);
};

struct CatalogEntry {
    int postnumber = -1;
    int sticky = -1;
    int closed = -1;

    std::string now;
    std::string name;
    std::string sub;

    std::vector<Text> text;
    std::optional<File> file = std::nullopt;

    int resto = -1;
    std::string id;
    std::string capcode;
    std::string country;
    int bumplimit = -1;
    int imagelimit = -1;
    int m_img = -1;
    std::string semantic_url;
    std::string country_name;
    std::string tripcode;
    int replies = -1;
    int images = -1;
    int omitted_posts = -1;
    int omitted_images = -1;

    std::vector<Post> last_replies;

    int last_modified = -1;

    static CatalogEntry from_json(nlohmann::json const& j);
};

struct Catalog {
    /**
	 * std::vector of CatalogEntry
	 */
    std::vector<CatalogEntry> entries;
};

struct Thread {
    /**
	 * std::vector of Post
	 */
    std::vector<Post> posts;
};

template<typename T>
inline auto json_get_to(nlohmann::json const& json, std::string const& key, T& data, std::string extra = "") -> void
{
    if (json.contains(key)) {
        data = json.at(key).get<T>();
    }
}

template<>
inline auto json_get_to<std::vector<Text>>(nlohmann::json const& json, std::string const& key, std::vector<Text>& data, std::string extra) -> void
{
    if (json.contains(key)) {
        data = channer::html::get_post_text(json);
    }
}

template<>
inline auto json_get_to<std::optional<File>>(nlohmann::json const& json, std::string const& key, std::optional<File>& data, std::string extra) -> void
{
    if (json.contains(key)) {
        File file;

        json_get_to(json, "filename", file.name);
        json_get_to(json, "ext", file.ext);
        json_get_to(json, "w", file.w);
        json_get_to(json, "h", file.h);
        json_get_to(json, "tn_w", file.tn_w);
        json_get_to(json, "tn_h", file.tn_h);
        json_get_to(json, "tim", file.tim);
        json_get_to(json, "time", file.time);
        json_get_to(json, "md5", file.md5);
        json_get_to(json, "fsize", file.size);

        data = file;
    }
}

template<>
inline auto json_get_to<std::vector<Post>>(nlohmann::json const& json, std::string const& key, std::vector<Post>& data, std::string extra) -> void
{
    if (json.contains(key)) {
        for (nlohmann::json const& reply : json[key]) {
            auto post_obj = get_post(reply, extra);
            data.emplace_back(post_obj);
        }
    }
}

inline Post Post::from_json(nlohmann::json const& j)
{
    Post p;

    json_get_to(j, "no", p.postnumber);
    json_get_to(j, "now", p.date);
    json_get_to(j, "name", p.name);
    json_get_to(j, "sub", p.subject);

    json_get_to(j, "trip", p.tripcode);

    json_get_to(j, "filename", p.file);

    json_get_to(j, "id", p.id);

    json_get_to(j, "com", p.text);

    json_get_to(j, "country", p.country);
    json_get_to(j, "country_name", p.country_name);

    json_get_to(j, "bumplimit", p.bumplimit);
    json_get_to(j, "imagelimit", p.imagelimit);
    json_get_to(j, "archived", p.archived);
    json_get_to(j, "archived_on", p.archived_on);

    json_get_to(j, "replies", p.replies);
    json_get_to(j, "images", p.images);
    json_get_to(j, "unique_ips", p.unique_ips);
    json_get_to(j, "tail_size", p.tail_size);

    return p;
}

inline CatalogEntry CatalogEntry::from_json(nlohmann::json const& j)
{
    CatalogEntry ce;

    json_get_to(j, "no", ce.postnumber);
    json_get_to(j, "sticky", ce.sticky);
    json_get_to(j, "closed", ce.closed);

    json_get_to(j, "now", ce.now);
    json_get_to(j, "name", ce.name);
    json_get_to(j, "sub", ce.sub);

    json_get_to(j, "com", ce.text);

    json_get_to(j, "filename", ce.file);

    json_get_to(j, "resto", ce.resto);

    json_get_to(j, "id", ce.id);
    json_get_to(j, "capcode", ce.capcode);
    json_get_to(j, "country", ce.country);

    json_get_to(j, "bumplimit", ce.bumplimit);
    json_get_to(j, "imagelimit", ce.imagelimit);

    json_get_to(j, "semantic_url", ce.semantic_url);
    json_get_to(j, "country_name", ce.country_name);

    json_get_to(j, "replies", ce.replies);
    json_get_to(j, "images", ce.images);
    json_get_to(j, "omitted_posts", ce.omitted_posts);
    json_get_to(j, "omitted_images", ce.omitted_images);

    json_get_to(j, "last_replies", ce.last_replies);

    json_get_to(j, "last_modified", ce.last_modified);
}

inline auto get_file(nlohmann::json& post, std::string const& board) -> File
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

inline auto get_post(nlohmann::json const& json, std::string const& board) -> Post
{
    //auto post = json.get<Post>();
    auto post = Post::from_json(json);

    if (post.file.has_value()) {
        post.file->url = "http://i.4cdn.org/" + board + "/" + std::to_string(post.file->tim) + post.file->ext;
    }

    return post;
}

inline auto get_catalog_entry(nlohmann::json& catalog, std::string const& board) -> CatalogEntry
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

inline auto get_board(nlohmann::json& board) -> Board
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

inline auto get_thread(nlohmann::json& thread, std::string const& board) -> Thread
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

inline auto get_catalog(nlohmann::json& catalog, std::string const& board) -> Catalog
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

inline auto get_boards(nlohmann::json& boards) -> Boards
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

inline auto dump_thread(nlohmann::json& thread) -> std::string
{
    return thread.dump(4);
}

inline auto dump_catalog(nlohmann::json& catalog) -> std::string
{
    return catalog.dump(4);
}
}

#endif
