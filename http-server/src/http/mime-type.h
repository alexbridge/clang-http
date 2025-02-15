#ifndef CLANG_HTTP_MIME_TYPE_H
#define CLANG_HTTP_MIME_TYPE_H

#include <map>
#include <string>

namespace mimetype
{
    std::map<std::string, std::string> MIME_TYPES = {
        {"html", "text/html"},
        {"css", "text/css"},
        {"js", "text/javascript"},
        {"jpg", "image/jpeg"},
        {"png", "image/png"}};
};

#endif