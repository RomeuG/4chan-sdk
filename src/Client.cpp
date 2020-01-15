#include <Client.hpp>
#include <cstdio>

namespace channer
{
// static auto get_media(std::string const& url, std::string const& thread, long long const tim, std::string const& extension) -> void
// {
//     if (!std::filesystem::exists(thread)) {
//         if (!std::filesystem::create_directory(thread)) {
//             std::printf("Error creating directory.\n");
//         }
//     }

//     auto absolute_path = std::filesystem::absolute(thread);
//     absolute_path.append(std::to_string(tim) + extension);

//     if (!std::filesystem::exists(absolute_path)) {
//         channer::download_media(url, absolute_path);
//     }
// }

// static auto get_media(std::string const& url, int const thread, long long const tim, std::string const& extension) -> bool
// {
//     auto t = std::to_string(thread);
//     auto res = true;

//     std::printf("Getting media: %s\n", t.c_str());

//     if (!std::filesystem::exists(t)) {
//         if (!std::filesystem::create_directory(t)) {
//             std::printf("Error creating directory.\n");
//         }
//     }

//     auto absolute_path = std::filesystem::absolute(t);
//     absolute_path.append(std::to_string(tim) + extension);

//     if (!std::filesystem::exists(absolute_path)) {
//         res = channer::download_media(url, absolute_path);
//     }

//     return res;
// }

// static auto get_images_from_thread(Thread const& thread) -> bool
// {
//     auto res = true;

//     for (auto& post : thread.posts) {
//         if (post.file.has_value()) {
//             auto f = post.file.value();
//             res = get_media(f.url, thread.posts[0].postnumber, f.tim, f.ext);
//         }
//     }

//     return res;
// }

// static auto get_images_from_thread(std::string const& board, std::string const& thread) -> bool
// {
//     auto res = true;
//     auto t = get_thread(board, thread, true);

//     for (auto& post : t.posts) {
//         if (post.file.has_value()) {
//             auto f = post.file.value();
//             res = get_media(f.url, t.posts[0].postnumber, f.tim, f.ext);
//         }
//     }

//     return res;
// }

// static auto get_images_from_thread_ff(Thread const& thread) -> void
// {
//     for (auto& post : thread.posts) {
//         if (post.file.has_value()) {
//             auto f = post.file.value();
//             std::async(std::launch::async, [&]() {
//                 get_media(f.url, thread.posts[0].postnumber, f.tim, f.ext);
//             });
//         }
//     }
// }

// auto get_images_from_thread_ff(std::string const& board, std::string const& thread) -> void
// {
//     auto t = get_thread(board, thread, true);

//     for (auto& post : t.posts) {
//         if (post.file.has_value()) {
//             auto f = post.file.value();
//             std::async(std::launch::async, [&]() {
//                 get_media(f.url, t.posts[0].postnumber, f.tim, f.ext);
//             });
//         }
//     }
// }

// auto get_images_from_thread(Thread const& thread, std::function<void(bool)> success, std::function<void(bool)> failure) -> void
// {
//     auto t = get_images_from_thread(thread);

//     if (t) {
//         success(t);
//     } else {
//         failure(t);
//     }
// }

// auto get_images_from_thread(std::string const& board, std::string const& thread, std::function<void(bool)> success, std::function<void(bool)> failure) -> void
// {
//     auto t = get_images_from_thread(board, thread);

//     if (t) {
//         success(t);
//     } else {
//         failure(t);
//     }
// }

auto get_thread(std::string const& board, std::string const& thread, std::function<void(std::optional<Thread>)>&& success, std::function<void(std::runtime_error)>&& failure) -> void
{
    try {
        execute_request<Thread>([&]() -> Thread {
            return channer::repo::get_thread(board, thread, false);
        },
                                success, failure);
    } catch (std::runtime_error const& e) {
        failure(e);
    }
}

auto get_thread_files(std::string const& board, std::string const& thread, std::function<void(std::vector<File>)>&& success, std::function<void(std::runtime_error)>&& failure) -> void
{
    try {
        execute_request<std::vector<File>>([&]() -> std::vector<File> {
            std::vector<File> files;
            auto thread_obj = channer::repo::get_thread(board, thread, true);

            std::for_each(std::begin(thread_obj.posts), std::end(thread_obj.posts), [&](Post const& post) {
                if (post.file.has_value()) {
                    files.emplace_back(post.file.value());
                }
            });

            return files;
        },
                                           success, failure);
    } catch (std::runtime_error const& e) {
        failure(e);
    }
}

auto get_catalog(std::string const& board, std::function<void(std::optional<Catalog>)>&& success, std::function<void(std::runtime_error)>&& failure) -> void
{
    try {
        execute_request<Catalog>([&]() -> Catalog {
            return channer::repo::get_catalog(board);
        },
                                 success, failure);
    } catch (std::runtime_error const& e) {
        failure(e);
    }
}

auto get_catalog_files(std::string const& board, std::function<void(std::vector<File>)>&& success, std::function<void(std::runtime_error)>&& failure) -> void
{
    try {
        execute_request<std::vector<File>>([&]() -> std::vector<File> {
            std::vector<File> files;
            auto catalog_obj = channer::repo::get_catalog(board, true);

            std::for_each(std::begin(catalog_obj.entries), std::end(catalog_obj.entries), [&](CatalogEntry const& entry) {
                if (entry.file.has_value()) {
                    files.emplace_back(entry.file.value());
                }
            });

            return files;
        },
                                           success, failure);
    } catch (std::runtime_error const& e) {
        failure(e);
    }
}

auto get_boards(std::function<void(std::optional<Boards>)>&& success, std::function<void(std::runtime_error)>&& failure) -> void
{
    try {
        execute_request<Boards>([&]() -> Boards {
            return channer::repo::get_boards();
        },
                                 success, failure);
    } catch (std::runtime_error const& e) {
        failure(e);
    }
}

auto search_board(Board &desired, std::function<void(std::vector<Board>)>&& success, std::function<void(std::runtime_error)>&& failure) -> void
{
	try {
		execute_request<std::vector<Board>>([&]() -> std::vector<Board> {
				return channer::repo::search_board(desired);
			}, success, failure);
	} catch (std::runtime_error const& e) {
		failure(e);
	}
}
}
