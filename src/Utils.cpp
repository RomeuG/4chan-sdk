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

auto create_media_path(std::string const& dir, long long const tim, std::string const& extension) -> std::string
{
	auto absolute_path = std::filesystem::absolute(dir);
    absolute_path.append(std::to_string(tim) + extension);

	return absolute_path;
}

auto create_media_url(std::string const& board, long long const tim, std::string const& extension) -> std::string
{
	return channer::endpoints::URL_IMG + board + "/" + std::to_string(tim) + extension;
}

#ifdef MOCKDATA
auto load_file(std::string const& path) -> std::string
{
    std::ifstream infile{ path };
    std::string file_contents{
        std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()
    };

    return file_contents;
}
#endif
}
