#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <string>

struct File {
    std::string name;
    std::string ext;
    int w;
    int h;
    int tn_w;
    int tn_h;
    int tim;
    int time;
    std::string md5;
    int size;
};

#endif