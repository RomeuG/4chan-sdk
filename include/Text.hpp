#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include <string>

struct Text {
    int type;
    std::string text;

    Text(int type, std::string text);
    ~Text();
};

#endif