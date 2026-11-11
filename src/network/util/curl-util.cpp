#include "curl-util.h"

#include <stdexcept>

namespace gtfs {

    void curl_setopt_secure(CURL* handle, CURLoption opt, long param) {
        CURLcode code = curl_easy_setopt(handle, opt, param);
        if (code != CURLE_OK) throw std::runtime_error(curl_easy_strerror(code));
    }

    void curl_setopt_secure(CURL* handle, CURLoption opt, const char* param) {
        CURLcode code = curl_easy_setopt(handle, opt, param);
        if (code != CURLE_OK) throw std::runtime_error(curl_easy_strerror(code));
    }

    void curl_setopt_secure(CURL* handle, CURLoption opt, FILE* param) {
        CURLcode code = curl_easy_setopt(handle, opt, param);
        if (code != CURLE_OK) throw std::runtime_error(curl_easy_strerror(code));
    }
}
