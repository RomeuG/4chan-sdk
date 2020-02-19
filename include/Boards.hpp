#ifndef _BOARDS_HPP_
#define _BOARDS_HPP_

#include <Board.hpp>
#include <vector>

struct Boards {
    /**
	 * std::vector of Board
	 */
    std::vector<Board> boards;

    /**
	 * std::unordered_map of all available troll flags
	 */
    std::unordered_map<std::string, std::string> troll_flags_list;
};

#endif
