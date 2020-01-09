#ifndef _DOWNLOAD_HPP_
#define _DOWNLOAD_HPP_

#include <array>
#include <cstdio>
#include <curl/curl.h>
#include <filesystem>
#include <future>
#include <string>

namespace channer
{
auto cb_curl_txt(char* data, size_t size, size_t nmemb, std::string* writer_data) -> std::size_t;

auto cb_curl_bin(void* data, size_t size, size_t nmemb, void* writer_data) -> std::size_t;

auto download_json(const char* url) -> std::string;

auto download_media(std::string const& url, std::filesystem::path const& path) -> bool;

auto download_json_async(const char* url) -> std::future<std::string>;

auto download_media_async_ff(std::string& url, std::filesystem::path& path) -> void;
}

#endif
