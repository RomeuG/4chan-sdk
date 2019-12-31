#ifndef _DOWNLOAD_HPP_
#define _DOWNLOAD_HPP_

#include <cstdio>
#include <curl/curl.h>
#include <string>

namespace channer
{
static auto cb_curl_txt(char* data, size_t size, size_t nmemb, std::string* writer_data) -> std::size_t
{
    if (writer_data == nullptr) {
        return 0;
    }

    writer_data->append(data, size * nmemb);

    return size * nmemb;
}

static auto cb_curl_bin(void* data, size_t size, size_t nmemb, void* writer_data) -> std::size_t
{
    FILE* stream = (FILE*)writer_data;
    if (stream == nullptr) {
        // TODO better debug messages
        std::printf("ChannerSDK :: error :: no file input stream");
        return 0;
    }

    return (std::size_t)fwrite((FILE*)data, size, nmemb, stream);
}

auto download_json(const char* url) -> std::string
{
    CURL* curl_ctx = nullptr;
    CURLcode code;

    struct curl_slist* headers = nullptr;

    std::string buffer;
    char curl_error_buffer[CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_ctx = curl_easy_init();

    if (curl_ctx == nullptr) {
        std::printf("ChannerSDK :: error :: Failed to create CURL connection\n");
        return "";
    }

    // TODO: define headers in client api configuration
    headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3724.8 Safari/537.36");

    curl_easy_setopt(curl_ctx, CURLOPT_ERRORBUFFER, curl_error_buffer);
    curl_easy_setopt(curl_ctx, CURLOPT_URL, url);
    curl_easy_setopt(curl_ctx, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl_ctx, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl_ctx, CURLOPT_WRITEFUNCTION, curlcb_html);
    curl_easy_setopt(curl_ctx, CURLOPT_WRITEDATA, &buffer);

    code = curl_easy_perform(curl_ctx);

    if (code != CURLE_OK) {
        std::printf("ChannerSDK :: error :: Failed to get '%s' [%s]\n", url, curl_error_buffer);
        exit(EXIT_FAILURE);
    }

    auto res_code = 0;
    curl_easy_getinfo(curl_ctx, CURLINFO_RESPONSE_CODE, &res_code);

    if (!((res_code == 200 || res_code == 201 || res_code == 403))) {
        std::printf("ChannerSDK :: error :: Response code: %d\n", res_code);
        return "";
    }

	// TODO: check if all cleanup done
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl_ctx);

    return buffer;
}
}

#endif
