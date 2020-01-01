#include <Utils.hpp>

namespace channer::utils
{
auto replace(std::string& str, std::string_view const from, std::string_view const to) -> void
{
    if (from.empty()) {
        return;
    }

    std::size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
}