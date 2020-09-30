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

    static File from_json(nlohmann::json const& json, std::string const& board);
};

struct Cooldowns {
    int threads = -1;
    int replies = -1;
    int images = -1;

    static Cooldowns from_json(nlohmann::json const& json, std::string const& key);
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

    static Board from_json(nlohmann::json& json);
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

    static Post from_json(nlohmann::json const& json, std::string const& board);
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

    static CatalogEntry from_json(nlohmann::json const& json, std::string const& board);
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
        data = File::from_json(json, extra);
    }
}

template<>
inline auto json_get_to<Cooldowns>(nlohmann::json const& json, std::string const& key, Cooldowns& data, std::string extra) -> void
{
    if (json.contains(key)) {
        data = Cooldowns::from_json(json, key);
    }
}

template<>
inline auto json_get_to<std::vector<Post>>(nlohmann::json const& json, std::string const& key, std::vector<Post>& data, std::string extra) -> void
{
    if (json.contains(key)) {
        for (nlohmann::json const& reply : json[key]) {
            auto post_obj = Post::from_json(reply, extra);
            data.emplace_back(post_obj);
        }
    }
}

inline Post Post::from_json(nlohmann::json const& json, std::string const& board)
{
    Post p;

    json_get_to(json, "no", p.postnumber);
    json_get_to(json, "now", p.date);
    json_get_to(json, "name", p.name);
    json_get_to(json, "sub", p.subject);

    json_get_to(json, "trip", p.tripcode);

    json_get_to(json, "filename", p.file, board);

    json_get_to(json, "id", p.id);

    json_get_to(json, "com", p.text);

    json_get_to(json, "country", p.country);
    json_get_to(json, "country_name", p.country_name);

    json_get_to(json, "bumplimit", p.bumplimit);
    json_get_to(json, "imagelimit", p.imagelimit);
    json_get_to(json, "archived", p.archived);
    json_get_to(json, "archived_on", p.archived_on);

    json_get_to(json, "replies", p.replies);
    json_get_to(json, "images", p.images);
    json_get_to(json, "unique_ips", p.unique_ips);
    json_get_to(json, "tail_size", p.tail_size);

    return p;
}

inline CatalogEntry CatalogEntry::from_json(nlohmann::json const& json, std::string const& board)
{
    CatalogEntry ce;

    json_get_to(json, "no", ce.postnumber);
    json_get_to(json, "sticky", ce.sticky);
    json_get_to(json, "closed", ce.closed);

    json_get_to(json, "now", ce.now);
    json_get_to(json, "name", ce.name);
    json_get_to(json, "sub", ce.sub);

    json_get_to(json, "com", ce.text);

    json_get_to(json, "filename", ce.file, board);

    json_get_to(json, "resto", ce.resto);

    json_get_to(json, "id", ce.id);
    json_get_to(json, "capcode", ce.capcode);
    json_get_to(json, "country", ce.country);

    json_get_to(json, "bumplimit", ce.bumplimit);
    json_get_to(json, "imagelimit", ce.imagelimit);

    json_get_to(json, "semantic_url", ce.semantic_url);
    json_get_to(json, "country_name", ce.country_name);

    json_get_to(json, "replies", ce.replies);
    json_get_to(json, "images", ce.images);
    json_get_to(json, "omitted_posts", ce.omitted_posts);
    json_get_to(json, "omitted_images", ce.omitted_images);

    json_get_to(json, "last_replies", ce.last_replies);

    json_get_to(json, "last_modified", ce.last_modified);

    return ce;
}

inline File File::from_json(nlohmann::json const& json, std::string const& board)
{
    File f;

    json_get_to(json, "filename", f.name);
    json_get_to(json, "ext", f.ext);
    json_get_to(json, "w", f.w);
    json_get_to(json, "h", f.h);
    json_get_to(json, "tn_w", f.tn_w);
    json_get_to(json, "tn_h", f.tn_h);
    json_get_to(json, "tim", f.tim);
    json_get_to(json, "time", f.time);
    json_get_to(json, "md5", f.md5);
    json_get_to(json, "fsize", f.size);

    f.url = "http://i.4cdn.org/" + board + "/" + std::to_string(f.tim) + f.ext;

    return f;
}

inline Board Board::from_json(nlohmann::json& json)
{
    Board b;

    json_get_to(json, "board", b.board);
    json_get_to(json, "title", b.title);

    json_get_to(json, "ws_board", b.ws_board);
    json_get_to(json, "per_page", b.per_page);
    json_get_to(json, "pages", b.pages);
    json_get_to(json, "max_filesize", b.max_filesize);
    json_get_to(json, "max_webm_filesize", b.max_webm_filesize);
    json_get_to(json, "max_comment_chars", b.max_comment_chars);
    json_get_to(json, "max_webm_duration", b.max_webm_duration);
    json_get_to(json, "bump_limit", b.bump_limit);
    json_get_to(json, "image_limit", b.image_limit);

    json_get_to(json, "cooldowns", b.cooldowns);

    json_get_to(json, "meta_description", b.meta_description);

    json_get_to(json, "user_ids", b.user_ids);
    json_get_to(json, "country_flags", b.country_flags);
    json_get_to(json, "forced_anon", b.forced_anon);
    json_get_to(json, "spoilers", b.spoilers);
    json_get_to(json, "custom_spoilers", b.custom_spoilers);
    json_get_to(json, "is_archived", b.is_archived);
    json_get_to(json, "require_subject", b.require_subject);
    json_get_to(json, "sjis_tags", b.sjis_tags);
    json_get_to(json, "oekaki", b.oekaki);
    json_get_to(json, "troll_flags", b.troll_flags);
    json_get_to(json, "webm_audio", b.webm_audio);
    json_get_to(json, "min_image_width", b.min_image_width);
    json_get_to(json, "min_image_height", b.min_image_height);
    json_get_to(json, "math_tags", b.math_tags);

    return b;
}

inline Cooldowns Cooldowns::from_json(nlohmann::json const& json, std::string const& key)
{
    Cooldowns c;

    json_get_to(json[key], "images", c.images);
    json_get_to(json[key], "replies", c.replies);
    json_get_to(json[key], "threads", c.threads);

    return c;
}

inline auto get_thread(nlohmann::json& thread, std::string const& board) -> Thread
{
    Thread thread_obj;

    thread_obj.posts.reserve(thread["posts"].size());

    for (nlohmann::json& post : thread["posts"]) {
        Post post_info;

        post_info = Post::from_json(post, board);

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
            auto catalog_entry = CatalogEntry::from_json(entry, board);
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
        auto board_obj = Board::from_json(board);
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
