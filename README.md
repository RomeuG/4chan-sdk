4chan-sdk
=========

A 4Chan SDK in C++ to interface with its API.

Example usage
-------------

``` c++
auto main() -> int
{
	Boards g_boards;

	channer::get_boards(
        [&](std::optional<Boards> arg) {
			g_boards = arg;
        },
        [](std::string const& e) {
            std::printf("Exception: %s\n", e.c_str());
        });

	return 0;
}
```
