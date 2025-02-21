#ifndef MESSAGE_HTTP_PARSER_H
#define MESSAGE_HTTP_PARSER_H

#include "message.h"

namespace http
{
    namespace message
    {
        class MessageParser
        {
        public:
            MessageParser();

            HttpMessage parse(std::istream body);
        };
    }
}

#endif
