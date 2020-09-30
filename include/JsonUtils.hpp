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
}

#endif
