#ifndef CLANG_HTTP_HEADER_H
#define CLANG_HTTP_HEADER_H

namespace httpheader
{
    // General
    const char *CONNECTION = "Connection";
    const char *DATE = "Date";
    const char *SERVER = "Server";
    const char *USER_AGENT = "User-Agent";
    const char *ACCEPT = "Accept";
    const char *ACCEPT_CHARSET = "Accept-Charset";
    const char *ACCEPT_ENCODING = "Accept-Encoding";
    const char *ACCEPT_LANGUAGE = "Accept-Language";
    const char *HOST = "Host";
    const char *REFERER = "Referer";

    // Request
    const char *AUTHORIZATION = "Authorization";
    const char *CACHE_CONTROL = "Cache-Control";
    const char *COOKIE = "Cookie";
    const char *EXPECT = "Expect";
    const char *FROM = "From";
    const char *IF_MODIFIED_SINCE = "If-Modified-Since";
    const char *IF_NONE_MATCH = "If-None-Match";
    const char *IF_UNMODIFIED_SINCE = "If-Unmodified-Since";
    const char *MAX_FORWARDS = "Max-Forwards";
    const char *RANGE = "Range";
    const char *TE = "TE";
    const char *VIA = "Via";
    const char *WARNING = "Warning";

    // Response
    const char *AGE = "Age";
    const char *ALLOW = "Allow";
    const char *CACHE_CONTROL_RESPONSE = "Cache-Control"; // Renamed for clarity
    const char *CONTENT_DISPOSITION = "Content-Disposition";
    const char *CONTENT_ENCODING_RESPONSE = "Content-Encoding"; // Renamed for clarity
    const char *CONTENT_LANGUAGE = "Content-Language";
    const char *CONTENT_LOCATION = "Content-Location";
    const char *CONTENT_RANGE = "Content-Range";
    const char *ETAG = "ETag";
    const char *EXPIRES = "Expires";
    const char *LAST_MODIFIED = "Last-Modified";
    const char *LOCATION = "Location";
    const char *PROXY_AUTHENTICATE = "Proxy-Authenticate";
    const char *RETRY_AFTER = "Retry-After";
    const char *SERVER_RESPONSE = "Server"; // Renamed for clarity
    const char *SET_COOKIE = "Set-Cookie";
    const char *TRANSFER_ENCODING = "Transfer-Encoding";
    const char *VARY = "Vary";
    const char *WWW_AUTHENTICATE = "WWW-Authenticate";

    // Entity Headers
    const char *ALLOW_METHODS = "Allow";
    const char *CONTENT_MD5 = "Content-MD5";
    const char *CONTENT_TYPE = "Content-Type";
    const char *CONTENT_LENGTH = "Content-Length";
    const char *EXPIRES_ENTITY = "Expires"; // Renamed for clarity
};

#endif