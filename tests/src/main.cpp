#include <Client.hpp>
#include <Utils.hpp>
#include <future>

auto main() -> int
{
    //auto thread = get_thread("g", "74238065");

    // get_catalog(
    //     "g",
    //     [](bool res) {
    //         std::printf("Success\n");
    //     },
    //     [](bool res) {
    //         std::printf("Failure\n");
    //     });

    // execute_request<Catalog>([]() -> Catalog { return Catalog(); },
    //                          [](Catalog arg) {
    //                              std::printf("Success\n");
    //                          },
    //                          []() {
    //                              std::printf("Failure\n");
    //                          });

    execute_request<Catalog>([]() -> Catalog { return get_catalog("g"); },
                             [](Catalog arg) {
                                 std::printf("Success: %d\n", arg.catalog_entries.size());
                             },
                             []() {
                                 std::printf("Failure\n");
                             });

    return 0;
}
