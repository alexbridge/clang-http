#ifndef CLANG_HTTP_HEADER_H
#define CLANG_HTTP_HEADER_H

#include <string>

namespace http
{
    namespace header
    {
        // General
        const std::string CONNECTION = "Connection";
        const std::string DATE = "Date";
        const std::string SERVER = "Server";
        const std::string USER_AGENT = "User-Agent";
        const std::string ACCEPT = "Accept";
        const std::string ACCEPT_CHARSET = "Accept-Charset";
        const std::string ACCEPT_ENCODING = "Accept-Encoding";
        const std::string ACCEPT_LANGUAGE = "Accept-Language";
        const std::string HOST = "Host";
        const std::string REFERER = "Referer";

        // Request
        const std::string AUTHORIZATION = "Authorization";
        const std::string CACHE_CONTROL = "Cache-Control";
        const std::string COOKIE = "Cookie";
        const std::string EXPECT = "Expect";
        const std::string FROM = "From";
        const std::string IF_MODIFIED_SINCE = "If-Modified-Since";
        const std::string IF_NONE_MATCH = "If-None-Match";
        const std::string IF_UNMODIFIED_SINCE = "If-Unmodified-Since";
        const std::string MAX_FORWARDS = "Max-Forwards";
        const std::string RANGE = "Range";
        const std::string TE = "TE";
        const std::string VIA = "Via";
        const std::string WARNING = "Warning";

        // Response
        const std::string AGE = "Age";
        const std::string ALLOW = "Allow";
        const std::string CACHE_CONTROL_RESPONSE = "Cache-Control"; // Renamed for clarity
        const std::string CONTENT_DISPOSITION = "Content-Disposition";
        const std::string CONTENT_ENCODING_RESPONSE = "Content-Encoding"; // Renamed for clarity
        const std::string CONTENT_LANGUAGE = "Content-Language";
        const std::string CONTENT_LOCATION = "Content-Location";
        const std::string CONTENT_RANGE = "Content-Range";
        const std::string ETAG = "ETag";
        const std::string EXPIRES = "Expires";
        const std::string LAST_MODIFIED = "Last-Modified";
        const std::string LOCATION = "Location";
        const std::string PROXY_AUTHENTICATE = "Proxy-Authenticate";
        const std::string RETRY_AFTER = "Retry-After";
        const std::string SERVER_RESPONSE = "Server"; // Renamed for clarity
        const std::string SET_COOKIE = "Set-Cookie";
        const std::string TRANSFER_ENCODING = "Transfer-Encoding";
        const std::string VARY = "Vary";
        const std::string WWW_AUTHENTICATE = "WWW-Authenticate";

        // Entity Headers
        const std::string ALLOW_METHODS = "Allow";
        const std::string CONTENT_MD5 = "Content-MD5";
        const std::string CONTENT_TYPE = "Content-Type";
        const std::string CONTENT_LENGTH = "Content-Length";
        const std::string EXPIRES_ENTITY = "Expires"; // Renamed for clarity
    }
};

#endif