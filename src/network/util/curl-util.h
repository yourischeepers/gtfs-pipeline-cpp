#pragma once

#include <curl/curl.h>

namespace gtfs {

    void curl_setopt_secure(CURL* handle, CURLoption opt, long param);
    void curl_setopt_secure(CURL* handle, CURLoption opt, const char* param);
    void curl_setopt_secure(CURL* handle, CURLoption opt, FILE* param);
}
