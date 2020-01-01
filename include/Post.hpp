#ifndef _POST_HPP_
#define _POST_HPP_

#include <File.hpp>
#include <optional>
#include <string>

struct Post {
    int postnumber;
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

    int bumplimit;
    int imagelimit;

    int replies;
    int images;
    int unique_ips;
    int tail_size;

    Post();
    ~Post();
};

#endif
