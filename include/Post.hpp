#ifndef _POST_HPP_
#define _POST_HPP_

#include <File.hpp>
#include <optional>
#include <string>

struct Post {
    int postnumber = -1;
    std::string date;
    std::string name;
    std::string subject;
    std::string tripcode;

    std::optional<File> file;

    int thread = -1;
    std::string id;
    std::string text;
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

    Post();
    ~Post();
};

#endif
