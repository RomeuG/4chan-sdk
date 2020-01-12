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

auto get_post(nlohmann::json& post, std::string const& board) -> Post
{
    Post post_obj;

	GET_VAL<int>(post, "no", post_obj.postnumber);
    GET_VAL<std::string>(post, "now", post_obj.date);
    GET_VAL<std::string>(post, "name", post_obj.name);
    GET_VAL<std::string>(post, "sub", post_obj.subject);

    if (!post["com"].empty()) {
        auto text_obj = channer::html::get_post_text(post);
        post_obj.text = text_obj;
    }

    if (!post["filename"].empty()) {
        auto file_obj = get_file(post, board);
        post_obj.file = file_obj;
    }

    GET_VAL<std::string>(post, "id", post_obj.id);
    GET_VAL<std::string>(post, "country", post_obj.country);
    GET_VAL<std::string>(post, "country_name", post_obj.country_name);

    GET_VAL<int>(post, "replies", post_obj.replies);
    GET_VAL<int>(post, "images", post_obj.images);
    GET_VAL<int>(post, "unique_ips", post_obj.unique_ips);
    GET_VAL<int>(post, "tail_size", post_obj.tail_size);
    GET_VAL<int>(post, "archived", post_obj.archived);
    GET_VAL<int>(post, "archived_on", post_obj.archived_on);

    return post_obj;
}

auto get_post_file_only(nlohmann::json& post, std::string const& board) -> Post
{
    Post post_obj;

    GET_VAL<int>(post, "no", post_obj.postnumber);

    if (!post["filename"].empty()) {
        auto file_obj = get_file(post, board);
        post_obj.file = file_obj;
    }

    return post_obj;
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

auto get_catalog_entry_file_only(nlohmann::json& catalog, std::string const& board) -> CatalogEntry
{
    CatalogEntry catalog_obj;

    if (!catalog["filename"].empty()) {
        auto file_obj    = get_file(catalog, board);
        catalog_obj.file = file_obj;
    }

    return catalog_obj;
}

auto get_thread(nlohmann::json& thread, std::string const& board, bool file_only) -> Thread
{
    Thread thread_obj;

    thread_obj.posts.reserve(thread["posts"].size());

    for (nlohmann::json& post : thread["posts"]) {
        Post post_info;

        if (file_only) {
            post_info = get_post_file_only(post, board);
        } else {
            post_info = get_post(post, board);
        }

        thread_obj.posts.emplace_back(post_info);
    }

    return thread_obj;
}

auto get_catalog(nlohmann::json& catalog, std::string const& board, bool file_only) -> Catalog
{
    Catalog catalog_obj;

    catalog_obj.entries.reserve(220);

    for (nlohmann::json& page : catalog) {
        for (nlohmann::json& entry : page["threads"]) {
			if (file_only) {
				auto catalog_entry = get_catalog_entry_file_only(entry, board);
				catalog_obj.entries.emplace_back(catalog_entry);
			} else {
				auto catalog_entry = get_catalog_entry(entry, board);
				catalog_obj.entries.emplace_back(catalog_entry);
			}
        }
    }

    return catalog_obj;
}
}
