#include <Repository.hpp>

namespace channer::repo
{
auto get_thread(std::string const& board, std::string const& thread, bool file_only) -> Thread
{
    auto website = channer::endpoints::URL_THREAD + board + channer::endpoints::TYPE_THREAD + thread + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::get_thread(json, board, file_only);
}

auto get_catalog(std::string const& board, bool file_only) -> Catalog
{
    auto website  = channer::endpoints::URL_THREAD + board + "/catalog" + channer::endpoints::FORMAT_JSON;
    auto download = channer::download_json(website.c_str());

    if (download == "") {
        throw std::runtime_error("Download error");
    }

    auto json = nlohmann::json::parse(download);
    return channer::json::get_catalog(json, board, file_only);
}

auto get_boards() -> Boards
{
	auto website = channer::endpoints::URL_THREAD + std::string("boards") + channer::endpoints::FORMAT_JSON;
	auto download = channer::download_json(website.c_str());

	if (download == "") {
		throw std::runtime_error("Download error");
	}

	auto json = nlohmann::json::parse(download);
	return channer::json::get_boards(json);
}

// auto search_board() -> std::vector<Board>
// {
// 	auto website = channer::endpoints::URL_THREAD + std::string("boards") + channer::endpoints::FORMAT_JSON;
// 	auto download = channer::download_json(website.c_str());

// 	if (download == "") {
// 		throw std::runtime_error("Download error");
// 	}

// 	auto json = nlohmann::json::parse(download);
// 	auto boards = channer::json::get_boards(json).boards;

// 	auto found = std::find_if(std::begin(boards), std::end(boards), [&](Board const & board) {

// 	});
// }
}
