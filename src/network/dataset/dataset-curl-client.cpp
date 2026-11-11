#include "dataset-curl-client.h"

#include <fstream>

#include "network/util/curl-util.h"

namespace gtfs {

    DatasetCurlClient::DatasetCurlClient() : curl(curl_easy_init(), &curl_easy_cleanup) {
        if (!curl) throw std::runtime_error("curl_easy_init failed");

        curl_setopt_secure(curl.get(), CURLOPT_URL, "https://gtfs.ovapi.nl/gtfs-nl.zip");
        curl_setopt_secure(curl.get(), CURLOPT_FOLLOWLOCATION, 1L);
        curl_setopt_secure(curl.get(), CURLOPT_CONNECTTIMEOUT, 10L);
        curl_setopt_secure(curl.get(), CURLOPT_LOW_SPEED_LIMIT, 1024L);
        curl_setopt_secure(curl.get(), CURLOPT_LOW_SPEED_TIME, 30L);
        curl_setopt_secure(curl.get(), CURLOPT_USERAGENT, "YouriScheepers");
    }

    void DatasetCurlClient::download() const {
        FILE* file = fopen("./data/gtfs.zip.tmp", "wb");
        curl_setopt_secure(curl.get(), CURLOPT_WRITEDATA, file);

        const CURLcode perform_code = curl_easy_perform(curl.get());
        if (perform_code != CURLE_OK) throw std::runtime_error(curl_easy_strerror(perform_code));

        long status = 0;
        const CURLcode info_code = curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &status);
        if (info_code != CURLE_OK) throw std::runtime_error(curl_easy_strerror(info_code));
        if (status != 200) throw std::runtime_error("Unexpected HTTP status " + std::to_string(status));

        fflush(file);
        fclose(file);
        std::filesystem::rename("./data/gtfs.zip.tmp", "./data/gtfs.zip");
    }
}
