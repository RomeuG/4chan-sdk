#ifndef _POST_HPP_
#define _POST_HPP_

#include <File.hpp>
#include <Text.hpp>
#include <optional>
#include <string>
#include <vector>

struct Post {
    int postnumber = -1;
    std::string date;
    std::string name;
    std::string subject;
    std::string tripcode;

    std::optional<File> file = std::nullopt;

    int thread = -1;
    std::string id;
    std::vector<Text> text;
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
};

#endif
