#ifndef _POST_HPP_
#define _POST_HPP_

#include <File.hpp>
#include <HtmlUtils.hpp>
#include <Text.hpp>
#include <json.hpp>
#include <optional>
#include <string>
#include <vector>

namespace channer::json
{
template<typename T>
inline auto json_get_to(nlohmann::json const& json, std::string const& key, T& data) -> void
{
    if (json.contains(key)) {
        data = json.at(key).get<T>();
    }
}

template<>
inline auto json_get_to<std::vector<Text>>(nlohmann::json const& json, std::string const& key, std::vector<Text>& data) -> void
{
    if (json.contains(key)) {
        data = channer::html::get_post_text(json);
    }
}

template<>
inline auto json_get_to<std::optional<File>>(nlohmann::json const& json, std::string const& key, std::optional<File>& data) -> void
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
};

inline void to_json(nlohmann::json& j, const Post& p)
{
}

inline void from_json(const nlohmann::json& j, Post& p)
{
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
}
}

#endif
