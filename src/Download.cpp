#include <Download.hpp>

namespace channer
{
auto cb_curl_txt(char* data, size_t size, size_t nmemb, std::string* writer_data) -> std::size_t
{
    if (writer_data == nullptr) {
        return 0;
    }

    writer_data->append(data, size * nmemb);

    return size * nmemb;
}

auto cb_curl_bin(void* data, size_t size, size_t nmemb, void* writer_data) -> std::size_t
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
    // char curl_error_buffer[CURL_ERROR_SIZE];
    std::array<char, CURL_ERROR_SIZE> curl_error_buffer{ 0 };

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_ctx = curl_easy_init();

    if (curl_ctx == nullptr) {
        std::printf("ChannerSDK :: error :: Failed to create CURL connection\n");
        return "";
    }

    // TODO: define headers in client api configuration
    headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3724.8 Safari/537.36");

    curl_easy_setopt(curl_ctx, CURLOPT_ERRORBUFFER, curl_error_buffer.data());
    curl_easy_setopt(curl_ctx, CURLOPT_URL, url);
    curl_easy_setopt(curl_ctx, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl_ctx, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl_ctx, CURLOPT_WRITEFUNCTION, cb_curl_txt);
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

auto download_media(std::string const& url, std::filesystem::path const& path) -> bool
{
    // NOTE: dirty hack because core is being dumped for
    // no apparent reason if this is not done.
    // stack smashing happens too.
    // probably a problem with std::filesystem::path ?
    auto const file = std::string(path.c_str());

    auto fp = std::fopen(file.c_str(), "wb");
    if (!fp) {
        std::printf("ChannerSDK :: error :: Failed to create file on the disk: %d\n", errno);
        return false;
    }

    auto curl_ctx = curl_easy_init();

    curl_easy_setopt(curl_ctx, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_ctx, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl_ctx, CURLOPT_WRITEFUNCTION, cb_curl_bin);
    curl_easy_setopt(curl_ctx, CURLOPT_FOLLOWLOCATION, 1);

    auto const rc = curl_easy_perform(curl_ctx);
    if (rc) {
        std::printf("ChannerSDK :: error :: Failed to download: %s\n", url.c_str());

        curl_easy_cleanup(curl_ctx);
        std::fclose(fp);
        return false;
    }

    auto res_code = 0;
    curl_easy_getinfo(curl_ctx, CURLINFO_RESPONSE_CODE, &res_code);

    if (!((res_code == 200 || res_code == 201))) {
        std::printf("ChannerSDK :: error :: Response code: %d\n", res_code);

        curl_easy_cleanup(curl_ctx);
        std::fclose(fp);

        // remove file because its useless
        std::filesystem::remove(path);

        return false;
    }

    curl_easy_cleanup(curl_ctx);
    std::fclose(fp);

    return true;
}

auto download_json_async(const char* url) -> std::future<std::string>
{
    return std::async(std::launch::async, [&]() -> std::string {
        return download_json(url);
    });
}

auto download_media_async_ff(std::string& url, std::filesystem::path& path) -> void
{
    std::async(std::launch::async, [&]() {
        auto success = download_media(url, path);

        if (!success) {
            std::printf("ChannerSDK :: error :: download from %s failed\n", url.c_str());
        }
    });
}
}