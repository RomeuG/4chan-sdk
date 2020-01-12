#include <Client.hpp>
#include <Utils.hpp>
#include <future>

auto main() -> int
{
    channer::get_thread(
        "g", "74261825",
        [](std::optional<Thread> arg) {
            std::printf("Success: %d\n", arg->posts.size());
        },
        [](std::runtime_error const& e) {
            std::printf("Failure: %s\n", e.what());
        });

	channer::get_thread_files(
        "g", "74261825",
        [](std::vector<File> arg) {
            std::printf("Success: %d\n", arg.size());
        },
        [](std::runtime_error const& e) {
            std::printf("Failure: %s\n", e.what());
        });

    channer::get_catalog(
        "g",
        [](std::optional<Catalog> arg) {
            std::printf("Success: %d\n", arg->entries.size());
        },
        [](std::runtime_error const& e) {
            std::printf("Failure: %s\n", e.what());
        });

	channer::get_catalog_files(
        "g",
        [](std::vector<File> arg) {
            std::printf("Success: %d\n", arg.size());
        },
        [](std::runtime_error const& e) {
            std::printf("Failure: %s\n", e.what());
        });

    return 0;
}
