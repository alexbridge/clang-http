#include "response.h"
#include "../http/header.h"

std::string HttpResponse::frameHttpResponse(
    std::string status_code,
    std::string status_message,
    std::map<std::string, std::string> headers,
    std::string body,
    std::string mimetype)
{
    // TODO
    //  status code , status msg , headers , body ko response formate me frame krna hai.

    headers[httpheader::CONTENT_TYPE] = mimetype;
    headers[httpheader::CONTENT_LENGTH] = std::to_string(body.length());

    std::ostringstream buffer;
    buffer << "HTTP/1.1 " << status_code << " " << status_message << "\r\n";
    for (auto x : headers)
    {
        buffer << x.first << ": " << x.second << "\r\n";
    }
    buffer << "\r\n"
           << body;

    return buffer.str();
}