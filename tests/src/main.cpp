#include <Client.hpp>

auto main() -> int
{
    //auto thread = get_thread("g", "74238065");
    get_images_from_thread(
        "g", "74238065",
        [](bool res) {
            std::printf("Success\n");
        },
        [](bool res) {
            std::printf("Failure\n");
        });
    return 0;
}