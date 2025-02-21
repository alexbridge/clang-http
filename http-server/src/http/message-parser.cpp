#include "message-parser.h"

namespace http
{
    namespace message
    {
        MessageParser::MessageParser() {}
        HttpMessage MessageParser::parse(std::istream body)
        {
            return HttpMessage{
                http::method::GET,
                "/",
                {{http::header::CONTENT_TYPE, "application/json"}},
                ""};
        }
    }
}
