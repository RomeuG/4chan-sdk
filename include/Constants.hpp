#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <unordered_map>

namespace channer
{
const std::unordered_map<std::string, std::string> chanlist{
    { "3", "https://boards.4channel.org/3/" },
    { "a", "https://boards.4channel.org/a/" },
    { "an", "https://boards.4channel.org/an/" },
    { "aco", "https://boards.4chan.org/aco/" },
    { "adv", "https://boards.4channel.org/adv/" },
    { "asp", "https://boards.4channel.org/asp/" },
    { "b", "https://boards.4chan.org/b/" },
    { "bant", "https://boards.4chan.org/bant/" },
    { "biz", "https://boards.4channel.org/biz/" },
    { "c", "https://boards.4channel.org/c/" },
    { "cgl", "https://boards.4channel.org/cgl/" },
    { "ck", "https://boards.4channel.org/ck/" },
    { "cm", "https://boards.4channel.org/cm/" },
    { "co", "https://boards.4channel.org/co/" },
    { "d", "https://boards.4chan.org/d/" },
    { "diy", "https://boards.4channel.org/diy/" },
    { "e", "https://boards.4chan.org/e/" },
    { "f", "https://boards.4chan.org/f/" },
    { "fa", "https://boards.4channel.org/fa/" },
    { "fit", "https://boards.4channel.org/fit/" },
    { "g", "https://boards.4channel.org/g/" },
    { "gd", "https://boards.4channel.org/gd/" },
    { "gif", "https://boards.4chan.org/gif/" },
    { "h", "https://boards.4chan.org/h/" },
    { "hc", "https://boards.4chan.org/hc/" },
    { "hm", "https://boards.4chan.org/hm/" },
    { "hr", "https://boards.4chan.org/hr/" },
    { "his", "https://boards.4channel.org/his/" },
    { "i", "https://boards.4chan.org/i/" },
    { "ic", "https://boards.4chan.org/ic/" },
    { "int", "https://boards.4channel.org/int/" },
    { "jp", "https://boards.4channel.org/jp/" },
    { "k", "https://boards.4channel.org/k/" },
    { "lgbt", "https://boards.4channel.org/lgbt/" },
    { "lit", "https://boards.4channel.org/lit/" },
    { "m", "https://boards.4channel.org/m/" },
    { "mu", "https://boards.4channel.org/mu/" },
    { "mlp", "https://boards.4channel.org/mlp/" },
    { "n", "https://boards.4channel.org/n/" },
    { "news", "https://boards.4channel.org/news/" },
    { "o", "https://boards.4channel.org/o/" },
    { "out", "https://boards.4channel.org/out/" },
    { "p", "https://boards.4channel.org/p/" },
    { "po", "https://boards.4channel.org/po/" },
    { "pol", "https://boards.4chan.org/pol/" },
    { "qst", "https://boards.4channel.org/qst/" },
    { "r", "https://boards.4chan.org/r/" },
    { "r9k", "https://boards.4chan.org/r9k/" },
    { "s", "https://boards.4chan.org/s/" },
    { "sp", "https://boards.4channel.org/sp/" },
    { "s4s", "https://boards.4chan.org/s4s/" },
    { "sci", "https://boards.4channel.org/sci/" },
    { "soc", "https://boards.4chan.org/soc/" },
    { "t", "https://boards.4chan.org/t/" },
    { "tg", "https://boards.4channel.org/tg/" },
    { "toy", "https://boards.4channel.org/toy/" },
    { "trv", "https://boards.4channel.org/trv/" },
    { "u", "https://boards.4chan.org/u/" },
    { "v", "https://boards.4channel.org/v/" },
    { "vg", "https://boards.4channel.org/vg/" },
    { "vp", "https://boards.4channel.org/vp/" },
    { "vr", "https://boards.4channel.org/vr/" },
    { "vip", "https://boards.4channel.org/vip/" },
    { "w", "https://boards.4channel.org/w/" },
    { "wg", "https://boards.4chan.org/wg/" },
    { "wsg", "https://boards.4channel.org/wsg/" },
    { "wsr", "https://boards.4channel.org/wsr/" },
    { "x", "https://boards.4channel.org/x/" },
    { "y", "https://boards.4chan.org/y/" },
};

namespace endpoints
{
    constexpr char URL_IMG[] = "https://i.4cdn.org/";
    constexpr char URL_THREAD[] = "https://a.4cdn.org/";

    constexpr char TYPE_THREAD[] = "/thread/";

    constexpr char FORMAT_JSON[] = ".json";

    constexpr char MEDIA[] = "https://i.4cdn.org/{board}/{tim}/{file}";
}
}

#endif
