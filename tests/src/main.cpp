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
				auto b = arg->boards.front();

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

			SECTION("Fifth board information is correct")
			{
				auto b = arg->boards[4];

				REQUIRE(b.board == "an");
				REQUIRE(b.title == "Animals & Nature");
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

			SECTION("Eighth board information is correct")
			{
				auto b = arg->boards[7];

				REQUIRE(b.board == "bant");
				REQUIRE(b.title == "International/Random");
				REQUIRE(b.ws_board == 0);
				REQUIRE(b.per_page == 15);
				REQUIRE(b.pages == 10);
				REQUIRE(b.max_filesize == 2097152);
				REQUIRE(b.max_webm_filesize == 2097152);
				REQUIRE(b.max_comment_chars == 2000);
				REQUIRE(b.max_webm_duration == 120);
				REQUIRE(b.bump_limit == 300);
				REQUIRE(b.image_limit == 150);
				REQUIRE(b.cooldowns.threads == 60);
				REQUIRE(b.cooldowns.replies == 15);
				REQUIRE(b.cooldowns.images == 15);
				REQUIRE(b.user_ids == 1);
				REQUIRE(b.country_flags == 1);
			}

			SECTION("Last board information is correct")
			{
				auto b = arg->boards.back();

				REQUIRE(b.board == "y");
				REQUIRE(b.title == "Yaoi");
				REQUIRE(b.ws_board == 0);
				REQUIRE(b.per_page == 15);
				REQUIRE(b.pages == 10);
				REQUIRE(b.max_filesize == 4194304);
				REQUIRE(b.max_webm_filesize == 3145728);
				REQUIRE(b.max_comment_chars == 2000);
				REQUIRE(b.max_webm_duration == 120);
				REQUIRE(b.bump_limit == 300);
				REQUIRE(b.image_limit == 300);
				REQUIRE(b.cooldowns.threads == 600);
				REQUIRE(b.cooldowns.replies == 60);
				REQUIRE(b.cooldowns.images == 30);
				REQUIRE(b.is_archived == 1);
			}

			SECTION("Troll flags are correct")
			{
				auto tf = arg->troll_flags_list;

				REQUIRE(tf["AC"] == "Anarcho-Capitalist");
				REQUIRE(tf["AN"] == "Anarchist");
				REQUIRE(tf["CM"] == "Communist");
				REQUIRE(tf["PC"] == "Hippie");
			}
        },
        [](std::runtime_error const& e) {

        });
};

TEST_CASE("Get /po/ threads")
{
    channer::get_catalog("po",
        [](std::optional<Catalog> arg) {
			SECTION("First thread information is correct")
            {
				auto t = arg->entries.front();

				REQUIRE(t.postnumber == 570368);
				REQUIRE(t.sticky == 1);
				REQUIRE(t.closed == 1);
				REQUIRE(t.now == "12/31/18(Mon)17:05:48");
				REQUIRE(t.name == "Anonymous");
				REQUIRE(t.sub == "Welcome to /po/!");
				REQUIRE(t.resto == 0);
				REQUIRE(t.capcode == "mod");
				REQUIRE(t.semantic_url == "welcome-to-po");
				REQUIRE(t.replies == 2);
				REQUIRE(t.images == 2);
				REQUIRE(t.omitted_posts == 1);
				REQUIRE(t.omitted_images == 1);
				REQUIRE(t.last_modified == 1546294897);
            }
        },
        [](std::runtime_error const& e) {

        });
};
