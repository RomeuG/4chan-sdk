#ifndef _POST_HPP_
#define _POST_HPP_

#include <File.hpp>
#include <optional>
#include <string>

struct Post {
    std::string postnumber;
    std::string time;
    std::string name;
    std::string subject;
    std::string tripcode;

    std::optional<File> file;

    std::string thread;
    std::string id;
    std::string text;
    std::string country;
    std::string country_name;

    std::string replies;
    std::string images;
    std::string unique_ips;
    std::string tail_size;

    Post();
    ~Post();
};

#endif
