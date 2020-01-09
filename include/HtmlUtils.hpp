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
auto convert_to_xmltree(std::string& buffer, htmlDocPtr* document, xmlNode** root) -> bool;
auto _get_post_text(xmlpp::Element* element) -> std::vector<Text>;
auto get_post_text(nlohmann::json& post) -> std::vector<Text>;
}

#endif