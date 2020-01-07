#include <Client.hpp>
#include <future>

auto main() -> int
{
    //auto thread = get_thread("g", "74238065");

    get_catalog(
        "g",
        [](bool res) {
            std::printf("Success\n");
        },
        [](bool res) {
            std::printf("Failure\n");
        });

    return 0;
}