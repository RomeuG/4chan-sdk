#ifndef _TEXT_HPP_
#define _TEXT_HPP_

#include <string>

enum TextType {
    NEWLINE = 0,
    PLAINTEXT,
    ITALICS,
    LINK,
    QUOTE
};

struct Text {
    TextType type;
    std::string text;

    Text(TextType type, std::string text) :
        type(type), text(text)
    {
    }
};

#endif
