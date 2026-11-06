#pragma once

#include <memory>
#include <string>
#include <curl/curl.h>

namespace gtfs {

    class ETagCurlClient {

    public:
        ETagCurlClient();
        [[nodiscard]] std::string fetch_e_tag() const;

    private:
        std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl;
    };
}
