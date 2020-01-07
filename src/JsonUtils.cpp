#include <JsonUtils.hpp>

auto _get_file(nlohmann::json& post, std::string const& board) -> File
{
    File file;

    file.name = post["filename"].get<std::string>();

    GET_VAL(post, "ext", file.ext, std::string);
    GET_VAL(post, "w", file.w, int);
    GET_VAL(post, "h", file.h, int);

    GET_VAL(post, "tn_w", file.tn_w, int);
    GET_VAL(post, "tn_h", file.tn_h, int);

    GET_VAL(post, "tim", file.tim, long long);
    GET_VAL(post, "time", file.time, int);

    GET_VAL(post, "md5", file.md5, std::string);

    GET_VAL(post, "fsize", file.size, int);

    // build the full url
    file.url = "http://i.4cdn.org/" + board + "/" + std::to_string(file.tim) + file.ext;

    return file;
}

auto _get_post(nlohmann::json& post, std::string const& board) -> Post
{
    Post post_obj;

    GET_VAL(post, "no", post_obj.postnumber, int);
    GET_VAL(post, "now", post_obj.date, std::string);
    GET_VAL(post, "name", post_obj.name, std::string);
    GET_VAL(post, "sub", post_obj.subject, std::string);

    if (!post["com"].empty()) {
        auto text_obj = _get_post_text(post);
        post_obj.text = text_obj;
    }

    if (!post["filename"].empty()) {
        auto file_obj = _get_file(post, board);
        post_obj.file = file_obj;
    }

    GET_VAL(post, "id", post_obj.id, std::string);
    GET_VAL(post, "country", post_obj.country, std::string);
    GET_VAL(post, "country_name", post_obj.country_name, std::string);
    GET_VAL(post, "replies", post_obj.replies, int);
    GET_VAL(post, "images", post_obj.images, int);
    GET_VAL(post, "unique_ips", post_obj.unique_ips, int);
    GET_VAL(post, "tail_size", post_obj.tail_size, int);
    GET_VAL(post, "archived", post_obj.archived, int);
    GET_VAL(post, "archived_on", post_obj.archived_on, int);

    return post_obj;
}

auto _get_post_file_only(nlohmann::json& post, std::string const& board) -> Post
{
    Post post_obj;

    GET_VAL(post, "no", post_obj.postnumber, int);

    if (!post["filename"].empty()) {
        auto file_obj = _get_file(post, board);
        post_obj.file = file_obj;
    }

    return post_obj;
}

auto _get_catalog_entry(nlohmann::json& catalog, std::string const& board) -> CatalogEntry
{
    CatalogEntry catalog_obj;

    GET_VAL(catalog, "no", catalog_obj.postnumber, int);
    GET_VAL(catalog, "sticky", catalog_obj.sticky, int);
    GET_VAL(catalog, "closed", catalog_obj.closed, int);
    GET_VAL(catalog, "now", catalog_obj.now, std::string);
    GET_VAL(catalog, "name", catalog_obj.name, std::string);
    GET_VAL(catalog, "sub", catalog_obj.sub, std::string);

    if (!catalog["com"].empty()) {
        auto text_obj = _get_post_text(catalog);
        catalog_obj.text = text_obj;
    }

    if (!catalog["filename"].empty()) {
        auto file_obj = _get_file(catalog, board);
        catalog_obj.file = file_obj;
    }

    GET_VAL(catalog, "resto", catalog_obj.resto, int);
    GET_VAL(catalog, "id", catalog_obj.id, std::string);
    GET_VAL(catalog, "capcode", catalog_obj.capcode, std::string);
    GET_VAL(catalog, "country", catalog_obj.country, std::string);
    GET_VAL(catalog, "bumplimit", catalog_obj.bumplimit, int);
    GET_VAL(catalog, "imagelimit", catalog_obj.imagelimit, int);
    GET_VAL(catalog, "semantic_url", catalog_obj.semantic_url, std::string);
    GET_VAL(catalog, "country_name", catalog_obj.country_name, std::string);
    GET_VAL(catalog, "replies", catalog_obj.replies, int);
    GET_VAL(catalog, "images", catalog_obj.images, int);

    // get last replies
    if (!catalog["last_replies"].empty()) {
        for (nlohmann::json& reply : catalog["last_replies"]) {
            auto post_obj = _get_post(reply, board);
            catalog_obj.last_replies.emplace_back(post_obj);
        }
    }

    GET_VAL(catalog, "last_modified", catalog_obj.last_modified, int);

    return catalog_obj;
}

auto _get_catalog(nlohmann::json& catalog, std::string const& board) -> Catalog
{
    Catalog catalog_obj;

    catalog_obj.catalog_entries.reserve(220);

    for (nlohmann::json& page : catalog) {
        for (nlohmann::json& entry : page["threads"]) {
            auto catalog_entry = _get_catalog_entry(catalog, board);
            catalog_obj.catalog_entries.emplace_back(catalog_entry);
        }
    }

    return catalog_obj;
}

auto _get_thread(nlohmann::json& thread, std::string const& board, bool file_only) -> Thread
{
    Thread thread_obj;

    thread_obj.posts.reserve(thread["posts"].size());

    for (nlohmann::json& post : thread["posts"]) {
        Post post_info;

        if (file_only) {
            post_info = _get_post_file_only(post, board);
        } else {
            post_info = _get_post(post, board);
        }

        thread_obj.posts.emplace_back(post_info);
    }

    return thread_obj;
}
