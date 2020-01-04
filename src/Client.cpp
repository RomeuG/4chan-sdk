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

auto __get_post_text(xmlpp::Element* element) -> std::vector<Text>
{
    std::vector<Text> vec_text;

    auto sibling = element->get_first_child();

    while (sibling) {
        auto sub_sibling = sibling->get_first_child();

        if (sibling->get_name() == "br") {
            vec_text.emplace_back(Text(TextType::NEWLINE, "\n"));
        }

        if (sibling->get_name() == "text") {
            auto text = reinterpret_cast<xmlpp::TextNode*>(sibling);
            if (text) {
                std::string sanitized = text->get_content();
                channer::utils::replace(sanitized, "\n", "");
                channer::utils::replace(sanitized, "\r", "");
                vec_text.emplace_back(Text(TextType::PLAINTEXT, sanitized));
            }
        }

        while (sub_sibling) {
            if (sub_sibling->get_name() == "br") {
                vec_text.emplace_back(Text(TextType::NEWLINE, "\n"));
            }

            if (sub_sibling->get_name() == "p") {
                auto paragraph_element = reinterpret_cast<xmlpp::Element*>(sub_sibling);
                if (paragraph_element) {
                    auto paragraph_text = reinterpret_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                    vec_text.emplace_back(Text(TextType::PLAINTEXT, paragraph_text->get_content()));
                }
            }

            if (sub_sibling->get_name() == "i") {
                auto italic_element = reinterpret_cast<xmlpp::Element*>(sub_sibling);
                if (italic_element) {
                    auto italic_text = reinterpret_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                    vec_text.emplace_back(Text(TextType::ITALICS, italic_text->get_content()));
                }
            }

            if (sub_sibling->get_name() == "text") {
                auto text = reinterpret_cast<xmlpp::TextNode*>(sub_sibling);
                if (text) {
                    std::string sanitized = text->get_content();
                    channer::utils::replace(sanitized, "\n", "");
                    channer::utils::replace(sanitized, "\r", "");
                    vec_text.emplace_back(Text(TextType::PLAINTEXT, sanitized));
                }
            }

            if (sub_sibling->get_name() == "a") {
                auto link_text = reinterpret_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                if (link_text) {
                    vec_text.emplace_back(Text(TextType::LINK, link_text->get_content()));
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
                    vec_text.emplace_back(Text(TextType::QUOTE, quote->get_content()));
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

auto _get_thread(nlohmann::json& thread, std::string const& board, bool file_only = false) -> Thread
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

auto get_thread(std::string const& board, std::string const& thread, bool file_only = false) -> Thread
{
    auto website = channer::endpoints::URL_THREAD + board + channer::endpoints::TYPE_THREAD + thread + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        return Thread();
    }

    auto json = nlohmann::json::parse(download);
    return _get_thread(json, board, file_only);
}

auto get_media(std::string const& url, std::string const& thread, long long const tim, std::string const& extension) -> void
{
    if (!std::filesystem::exists(thread)) {
        if (!std::filesystem::create_directory(thread)) {
            std::printf("Error creating directory.\n");
        }
    }

    auto absolute_path = std::filesystem::absolute(thread);
    absolute_path.append(std::to_string(tim) + extension);

    if (!std::filesystem::exists(absolute_path)) {
        channer::download_media(url, absolute_path);
    }
}

auto get_media(std::string const& url, int const thread, long long const tim, std::string const& extension) -> bool
{
    auto t = std::to_string(thread);
    auto res = true;

    if (!std::filesystem::exists(t)) {
        if (!std::filesystem::create_directory(t)) {
            std::printf("Error creating directory.\n");
        }
    }

    auto absolute_path = std::filesystem::absolute(t);
    absolute_path.append(std::to_string(tim) + extension);

    if (!std::filesystem::exists(absolute_path)) {
        res = channer::download_media(url, absolute_path);
    }

    return res;
}

auto get_images_from_thread(Thread const& thread) -> bool
{
    auto res = true;

    for (auto& post : thread.posts) {
        if (post.file.has_value()) {
            auto f = post.file.value();
            res = get_media(f.url, thread.posts[0].postnumber, f.tim, f.ext);
        }
    }

    return res;
}

auto get_images_from_thread(std::string const& board, std::string const& thread) -> bool
{
    auto res = true;
    auto t = get_thread(board, thread, true);

    for (auto& post : t.posts) {
        if (post.file.has_value()) {
            auto f = post.file.value();
            res = get_media(f.url, t.posts[0].postnumber, f.tim, f.ext);
        }
    }

    return res;
}

auto get_images_from_thread(Thread const& thread, std::function<void(bool)> success, std::function<void(bool)> failure) -> void
{
    auto t = get_images_from_thread(thread);

    if (t) {
        success(t);
    } else {
        failure(t);
    }
}

auto get_images_from_thread(std::string const& board, std::string const& thread, std::function<void(bool)> success, std::function<void(bool)> failure) -> void
{
    auto t = get_images_from_thread(board, thread);

    if (t) {
        success(t);
    } else {
        failure(t);
    }
}