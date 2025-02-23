#include "message-parser.h"

namespace http
{
    namespace message
    {
        MessageParser::MessageParser() {}
        HttpMessage MessageParser::parse(std::string_view body)
        {
            return HttpMessage{
                http::method::GET,
                "/",
                {{http::header::CONTENT_TYPE, "application/json"}},
                ""};
        }
    }
}
