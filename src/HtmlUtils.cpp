#include <HtmlUtils.hpp>

auto convert_to_xmltree(std::string& buffer, htmlDocPtr* document, xmlNode** root) -> bool
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