#pragma once

#include <memory>
#include <curl/curl.h>

namespace gtfs {

    class DatasetCurlClient {

    public:
        DatasetCurlClient();
        void download() const;

    private:
        std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl;
    };
}
