#define CATCH_CONFIG_MAIN

#include <Client.hpp>
#include <Utils.hpp>
#include <future>
#include <catch.hpp>

TEST_CASE("Get all boards")
{
    channer::get_boards(
        [](std::optional<Boards> arg) {
			SECTION("First board information is correct")
			{
				auto b = arg->boards[0];

				REQUIRE(b.board == "3");
				REQUIRE(b.title == "3DCG");
				REQUIRE(b.ws_board == 1);
				REQUIRE(b.per_page == 15);
				REQUIRE(b.pages == 10);
				REQUIRE(b.max_filesize == 4194304);
				REQUIRE(b.max_webm_filesize == 3145728);
				REQUIRE(b.max_comment_chars == 2000);
				REQUIRE(b.max_webm_duration == 120);
				REQUIRE(b.bump_limit == 310);
				REQUIRE(b.image_limit == 150);
				REQUIRE(b.cooldowns.threads == 600);
				REQUIRE(b.cooldowns.replies == 60);
				REQUIRE(b.cooldowns.images == 60);
				REQUIRE(b.is_archived == 1);
			}
        },
        [](std::runtime_error const& e) {

        });
};
