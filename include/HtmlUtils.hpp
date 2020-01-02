#ifndef _HTMLUTILS_HPP_
#define _HTMLUTILS_HPP_

#include <libxml++-3.0/libxml++/libxml++.h>
#include <libxml2/libxml/HTMLparser.h>
#include <string>

auto convert_to_xmltree(std::string& buffer, htmlDocPtr* document, xmlNode** root) -> bool;

#endif