#ifndef MESSAGE_HTTP_PARSER_H
#define MESSAGE_HTTP_PARSER_H

#include "message.h"
#include "http.h"

namespace http
{
    namespace message
    {
        class MessageParser
        {
        public:
            MessageParser();

            HttpMessage parse(std::string_view body);
        };
    }
}

#endif
