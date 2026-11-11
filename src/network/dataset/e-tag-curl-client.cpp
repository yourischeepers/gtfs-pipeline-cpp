#include "e-tag-curl-client.h"

#include <stdexcept>

#include "network/util/curl-util.h"

namespace gtfs {

    ETagCurlClient::ETagCurlClient() : curl(curl_easy_init(), &curl_easy_cleanup) {
        if (!curl) throw std::runtime_error("curl_easy_init failed");

        curl_setopt_secure(curl.get(), CURLOPT_URL, "https://gtfs.ovapi.nl/gtfs-nl.zip");
        curl_setopt_secure(curl.get(), CURLOPT_NOBODY, 1L);
        curl_setopt_secure(curl.get(), CURLOPT_FOLLOWLOCATION, 1L);
        curl_setopt_secure(curl.get(), CURLOPT_TIMEOUT, 10L);
        curl_setopt_secure(curl.get(), CURLOPT_USERAGENT, "YouriScheepers");
    }

    std::string ETagCurlClient::fetch_e_tag() const {
        const CURLcode perform_code = curl_easy_perform(curl.get());
        if (perform_code != CURLE_OK) throw std::runtime_error(curl_easy_strerror(perform_code));

        long status = 0;
        const CURLcode info_code = curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &status);
        if (info_code != CURLE_OK) throw std::runtime_error(curl_easy_strerror(info_code));
        if (status != 200) throw std::runtime_error("Unexpected HTTP status " + std::to_string(status));

        curl_header* header = nullptr;
        const CURLHcode fetch_code = curl_easy_header(curl.get(), "ETag", 0, CURLH_HEADER, -1, &header);

        if (fetch_code == CURLHE_OK) return header->value;
        if (fetch_code == CURLHE_MISSING) throw std::runtime_error("ETag header is missing");
        throw std::runtime_error("Failed to fetch ETag");
    }
}
