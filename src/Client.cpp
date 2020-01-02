#include <Client.hpp>
#include <cstdio>

#define GET_VAL(a, b, c, d) \
    if (!a[b].empty()) {    \
        c = a[b].get<d>();  \
    }

#define GET_VAL_STR(a, b, c)         \
    if (!a[b].empty()) {             \
        c = a[b].get<std::string>(); \
    }

#define GET_VAL_INT(a, b, c) \
    if (!a[b].empty()) {     \
        c = a[b].get<int>(); \
    } else {                 \
        c = -1;              \
    }

auto _get_file(nlohmann::json& post) -> File
{
    File file;

    file.name = post["filename"].get<std::string>();

    GET_VAL(post, "ext", file.ext, std::string);
    GET_VAL(post, "w", file.w, int);
    GET_VAL(post, "h", file.h, int);

    GET_VAL(post, "tn_w", file.tn_w, int);
    GET_VAL(post, "tn_h", file.tn_h, int);

    GET_VAL(post, "tim", file.tim, int);
    GET_VAL(post, "time", file.time, int);

    GET_VAL(post, "md5", file.md5, std::string);

    GET_VAL(post, "fsize", file.size, int);

    return file;
}

auto __get_post_text(xmlpp::Element* element) -> std::vector<Text>
{
    std::vector<Text> vec_text;

    auto sibling = element->get_first_child();

    while (sibling) {
        auto sub_sibling = sibling->get_first_child();

        if (sibling->get_name() == "br") {
            vec_text.emplace_back(Text(0, "\n"));
        }

        if (sibling->get_name() == "text") {
            auto text = reinterpret_cast<xmlpp::TextNode*>(sibling);
            if (text) {
                std::string sanitized = text->get_content();
                channer::utils::replace(sanitized, "\n", "");
                channer::utils::replace(sanitized, "\r", "");
                vec_text.emplace_back(Text(1, sanitized));
            }
        }

        while (sub_sibling) {
            if (sub_sibling->get_name() == "br") {
                vec_text.emplace_back(Text(0, "\n"));
            }

            if (sub_sibling->get_name() == "p") {
                auto paragraph_element = reinterpret_cast<xmlpp::Element*>(sub_sibling);
                if (paragraph_element) {
                    auto paragraph_text = reinterpret_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                    vec_text.emplace_back(Text(1, paragraph_text->get_content()));
                }
            }

            if (sub_sibling->get_name() == "i") {
                auto italic_element = reinterpret_cast<xmlpp::Element*>(sub_sibling);
                if (italic_element) {
                    auto italic_text = reinterpret_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                    vec_text.emplace_back(Text(2, italic_text->get_content()));
                }
            }

            if (sub_sibling->get_name() == "text") {
                auto text = reinterpret_cast<xmlpp::TextNode*>(sub_sibling);
                if (text) {
                    std::string sanitized = text->get_content();
                    channer::utils::replace(sanitized, "\n", "");
                    channer::utils::replace(sanitized, "\r", "");
                    vec_text.emplace_back(Text(1, sanitized));
                }
            }

            if (sub_sibling->get_name() == "a") {
                auto link_text = reinterpret_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                if (link_text) {
                    //post += link_text->get_content();
                    vec_text.emplace_back(Text(3, link_text->get_content()));
                }

                auto link = reinterpret_cast<xmlpp::Element*>(sub_sibling);
                if (link && link_text) {
                    auto href = link->get_attribute_value("href");

                    if (href != link_text->get_content()) {
                        // TODO: get href
                    }
                }
            }

            if (sub_sibling->get_name() == "span") {
                auto quote = reinterpret_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                if (quote) {
                    vec_text.emplace_back(Text(4, quote->get_content()));
                }
            }

            sub_sibling = sub_sibling->get_next_sibling();
        }

        sibling = sibling->get_next_sibling();
    }

    return vec_text;
}

auto _get_post_text(nlohmann::json& post) -> std::vector<Text>
{
    std::vector<Text> text_list;

    auto str = post["com"].get<std::string>();

    htmlDocPtr doc = nullptr;
    xmlNode* root = nullptr;

    auto result = convert_to_xmltree(str, &doc, &root);
    if (!result) {
        std::printf("Failed converting into xmltree");
        exit(EXIT_FAILURE);
    }

    auto root_element = std::make_unique<xmlpp::Element>(root);
    auto body = root_element->find("//body");

    if (body.empty()) {
        return std::vector<Text>();
    }

    auto body_element = reinterpret_cast<xmlpp::Element*>(body[0]);
    text_list = __get_post_text(body_element);

    xmlFreeDoc(doc);

    return text_list;
}

// TODO: finish this function
auto _get_post(nlohmann::json& post) -> Post
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
        auto file_obj = _get_file(post);
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

auto _get_thread(nlohmann::json& thread) -> Thread
{
    Thread thread_obj;

    thread_obj.posts.reserve(thread["posts"].size());

    for (nlohmann::json& post : thread["posts"]) {
        auto post_info = _get_post(post);
        thread_obj.posts.emplace_back(post_info);
    }

    return thread_obj;
}

auto get_thread(std::string const& board, std::string const& thread) -> Thread
{
    auto website = "http://a.4cdn.org/" + board + "/thread/" + thread + ".json";
    auto download = channer::download_json(website.c_str());

    auto json = nlohmann::json::parse(download);
    return _get_thread(json);
}