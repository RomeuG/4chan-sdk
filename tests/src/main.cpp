#include <Client.hpp>
#include <Utils.hpp>
#include <future>

auto main() -> int
{
    channer::get_catalog(
        "g",
        [](std::optional<Catalog> arg) {
            std::printf("Success: %d\n", arg->catalog_entries.size());
        },
        [](std::runtime_error const& e) {
            std::printf("Failure: %s\n", e.what());
        });

    return 0;
}
