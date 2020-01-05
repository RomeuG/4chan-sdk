#ifndef _CATALOG_ENTRY_HPP_
#define _CATALOG_ENTRY_HPP_

#include <File.hpp>
#include <Post.hpp>
#include <Text.hpp>
#include <optional>
#include <string>
#include <vector>

struct CatalogEntry {
    int postnumber = -1;
    int sticky = -1;
    int closed = -1;

    std::string now;
    std::string name;
    std::string sub;

    std::vector<Text> text;
    std::optional<File> file;

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
};

#endif