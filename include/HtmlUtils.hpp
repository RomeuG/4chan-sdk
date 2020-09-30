#ifndef _HTMLUTILS_HPP_
#define _HTMLUTILS_HPP_

#include <Text.hpp>
#include <Utils.hpp>
#include <json.hpp>
#include <libxml++-3.0/libxml++/libxml++.h>
#include <libxml2/libxml/HTMLparser.h>
#include <string>
#include <vector>

namespace channer::html
{
inline auto convert_to_xmltree(std::string& buffer, htmlDocPtr* document, xmlNode** root) -> bool
{
    *document = htmlReadMemory(buffer.c_str(), buffer.size(), nullptr, nullptr, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
    if (*document == nullptr) {
        std::printf("Error parsing html.\n");
        return false;
    }

    *root = xmlDocGetRootElement(*document);
    if (*root == nullptr) {
        std::printf("Error getting root element.\n");
        xmlFreeDoc(*document);
        return false;
    }

    return true;
}

inline auto _get_post_text(xmlpp::Element* element) -> std::vector<Text>
{
    std::vector<Text> vec_text;

    auto sibling = element->get_first_child();

    while (sibling) {
        auto sub_sibling = sibling->get_first_child();

        if (sibling->get_name() == "br") {
            vec_text.emplace_back(Text(TextType::NEWLINE, "\n"));
        }

        if (sibling->get_name() == "text") {
            auto text = dynamic_cast<xmlpp::TextNode*>(sibling);
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
                auto paragraph_element = dynamic_cast<xmlpp::Element*>(sub_sibling);
                if (paragraph_element) {
                    auto paragraph_text = dynamic_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                    vec_text.emplace_back(Text(TextType::PLAINTEXT, paragraph_text->get_content()));
                }
            }

            if (sub_sibling->get_name() == "i") {
                auto italic_element = dynamic_cast<xmlpp::Element*>(sub_sibling);
                if (italic_element) {
                    auto italic_text = dynamic_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                    vec_text.emplace_back(Text(TextType::ITALICS, italic_text->get_content()));
                }
            }

            if (sub_sibling->get_name() == "text") {
                auto text = dynamic_cast<xmlpp::TextNode*>(sub_sibling);
                if (text) {
                    std::string sanitized = text->get_content();
                    channer::utils::replace(sanitized, "\n", "");
                    channer::utils::replace(sanitized, "\r", "");
                    vec_text.emplace_back(Text(TextType::PLAINTEXT, sanitized));
                }
            }

            if (sub_sibling->get_name() == "a") {
                auto link_text = dynamic_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                if (link_text) {
                    vec_text.emplace_back(Text(TextType::LINK, link_text->get_content()));
                }

                auto link = dynamic_cast<xmlpp::Element*>(sub_sibling);
                if (link && link_text) {
                    auto href = link->get_attribute_value("href");

                    if (href != link_text->get_content()) {
                        // TODO: get href
                    }
                }
            }

            if (sub_sibling->get_name() == "span") {
                auto quote = dynamic_cast<xmlpp::TextNode*>(sub_sibling->get_first_child());
                if (quote) {
                    vec_text.emplace_back(Text(TextType::QUOTE, quote->get_content()));
                }
            }

            sub_sibling = sub_sibling->get_next_sibling();
        }

        sibling = sibling->get_next_sibling();
    }

    element->remove_node(element);

    return vec_text;
}

inline auto get_post_text(nlohmann::json const& post) -> std::vector<Text>
{
    std::vector<Text> text_list;

    auto str = post["com"].get<std::string>();

    // sanitize useless <wbr>
    channer::utils::replace(str, "<wbr>", "");

    htmlDocPtr doc = nullptr;
    xmlNode* root = nullptr;

    auto result = convert_to_xmltree(str, &doc, &root);
    if (!result) {
        std::printf("Failed converting into xmltree");
        exit(EXIT_FAILURE);
    }

    auto root_element = std::make_unique<xmlpp::Element>(root);
    auto body = std::make_unique<xmlpp::Node::NodeSet>(root_element->find("//body"));

    if (body->empty()) {
        return std::vector<Text>();
    }

    auto body_element = dynamic_cast<xmlpp::Element*>(body->at(0));
    text_list = _get_post_text(body_element);

    xmlFreeDoc(doc);

    return text_list;
}
}

#endif
