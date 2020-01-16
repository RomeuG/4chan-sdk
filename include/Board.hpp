#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <Cooldowns.hpp>
#include <unordered_map>
#include <string>

struct Board
{
	std::string board;
	std::string title;

	int ws_board = -1;
	int per_page = -1;
	int pages = -1;
	int max_filesize = -1;
	int max_webm_filesize = -1;
	int max_comment_chars = -1;
	int max_webm_duration = -1;
	int bump_limit = -1;
	int image_limit = -1;

	Cooldowns cooldowns;

	std::string meta_description;
	int user_ids = -1;
	int country_flags = -1;
	int forced_anon = -1;
	int spoilers = -1;
	int custom_spoilers = -1;
	int is_archived = -1;
	int require_subject = -1;
	int sjis_tags = -1;
	int oekaki = -1;
	int troll_flags = -1;
	int webm_audio = -1;
	int min_image_width = -1;
	int min_image_height = -1;
	int math_tags = -1;
};

#endif
