#ifndef _DOWNLOAD_HPP_
#define _DOWNLOAD_HPP_

#include <cstdio>
#include <string>
#include <cstdio>

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
			std::printf("ChannerSDK :: error: no file input stream");
			return 0;
		}

		return (std::size_t)fwrite((FILE*)data, size, nmemb, stream);
	}
}

#endif
