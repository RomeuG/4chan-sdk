#define CATCH_CONFIG_MAIN

#include <Client.hpp>
#include <Utils.hpp>
#include <catch.hpp>
#include <future>

TEST_CASE("Get all boards")
{
    channer::get_boards(
        [](std::optional<Boards> arg) {
			REQUIRE(arg->boards.size() == 72);
			REQUIRE(arg->troll_flags_list.size() == 23);

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
    channer::get_catalog(
        "po",
        [](std::optional<Catalog> arg) {
			REQUIRE(arg->entries.size() == 151);

            SECTION("First thread information is correct")
            {
                auto t = arg->entries.front();

                REQUIRE(t.postnumber == 570368);
                REQUIRE(t.sticky == 1);
                REQUIRE(t.closed == 1);
                REQUIRE(t.now == "12/31/18(Mon)17:05:48");
                REQUIRE(t.name == "Anonymous");
                REQUIRE(t.sub == "Welcome to /po/!");

                SECTION("Last thread file information is correct")
                {
                    auto f = t.file;

                    REQUIRE(f->name == "yotsuba_folding");
                    REQUIRE(f->ext == ".png");
                    REQUIRE(f->w == 530);
                    REQUIRE(f->h == 449);
                    REQUIRE(f->tn_w == 250);
                    REQUIRE(f->tn_h == 211);
                    REQUIRE(f->tim == 1546293948883ll);
                    REQUIRE(f->time == 1546293948);
                    REQUIRE(f->md5 == "uZUeZeB14FVR+Mc2ScHvVA==");
                    REQUIRE(f->size == 516657);
                }

                REQUIRE(t.resto == 0);
                REQUIRE(t.capcode == "mod");
                REQUIRE(t.semantic_url == "welcome-to-po");
                REQUIRE(t.replies == 2);
                REQUIRE(t.images == 2);
                REQUIRE(t.omitted_posts == 1);
                REQUIRE(t.omitted_images == 1);
                REQUIRE(t.last_modified == 1546294897);
            }

			SECTION("Third thread information is correct")
            {
                auto t = arg->entries[2];

                REQUIRE(t.postnumber == 579035);
                REQUIRE(t.now == "01/16/20(Thu)05:17:09");
                REQUIRE(t.name == "Anonymous");
                REQUIRE(t.sub == "Voltron");
				REQUIRE(t.text[0].text == "Templates to this?");

                SECTION("Third thread file information is correct")
                {
                    auto f = t.file;

                    REQUIRE(f->name == "14fda025162991.56342593032f0");
                    REQUIRE(f->ext == ".jpg");
                    REQUIRE(f->w == 600);
                    REQUIRE(f->h == 750);
                    REQUIRE(f->tn_w == 200);
                    REQUIRE(f->tn_h == 250);
                    REQUIRE(f->tim == 1579169829196ll);
                    REQUIRE(f->time == 1579169829);
                    REQUIRE(f->md5 == "kxe/jgFYRhBb8f/FdIMScA==");
                    REQUIRE(f->size == 181179);
                }

                REQUIRE(t.resto == 0);
                REQUIRE(t.bumplimit == 0);
                REQUIRE(t.imagelimit == 0);
                REQUIRE(t.semantic_url == "voltron");
                REQUIRE(t.replies == 1);
                REQUIRE(t.images == 1);
                REQUIRE(t.last_modified == 1579170280);
            }

            SECTION("Last thread information is correct")
            {
                auto t = arg->entries.back();

                REQUIRE(t.postnumber == 577937);
                REQUIRE(t.now == "11/16/19(Sat)05:15:03");
                REQUIRE(t.name == "Anonymous");
                REQUIRE(t.sub == "Final Fantasy X Iron Giant");

                SECTION("Last thread file information is correct")
                {
                    auto f = t.file;

                    REQUIRE(f->name == "xirongiantauronlulurikku1");
                    REQUIRE(f->ext == ".jpg");
                    REQUIRE(f->w == 800);
                    REQUIRE(f->h == 600);
                    REQUIRE(f->tn_w == 250);
                    REQUIRE(f->tn_h == 187);
                    REQUIRE(f->tim == 1573899303849ll);
                    REQUIRE(f->time == 1573899303);
                    REQUIRE(f->md5 == "rWX7Zjf7/5UjBDG6z5FWMg==");
                    REQUIRE(f->size == 462244);
                }

                REQUIRE(t.resto == 0);
                REQUIRE(t.bumplimit == 0);
                REQUIRE(t.imagelimit == 0);
                REQUIRE(t.semantic_url == "final-fantasy-x-iron-giant");
                REQUIRE(t.replies == 1);
                REQUIRE(t.images == 0);
                REQUIRE(t.last_modified == 1573900140);
            }
        },
        [](std::runtime_error const& e) {

        });
};
