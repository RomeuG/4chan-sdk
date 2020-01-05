#include <Client.hpp>
#include <future>

auto main() -> int
{
    //auto thread = get_thread("g", "74238065");

    // std::async(std::launch::async, []() {
    // get_images_from_thread(
    //     "g", "74238065",
    //     [](bool res) {
    //         std::printf("Success\n");
    //     },
    //     [](bool res) {
    //         std::printf("Failure\n");
    //     });
    //});

    //get_images_from_thread_ff("g", "74238065");
    get_catalog("g");

    return 0;
}