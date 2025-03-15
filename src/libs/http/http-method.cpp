#include "../../../include/http.h"

namespace app
{
    std::string httpMethodToString(HttpMethod method)
    {

        auto it = httpMethodToStrMap.find(method);
        if (it != httpMethodToStrMap.end())
        {
            return it->second;
        }
        else
        {
            return "Unknown HttpMethod";
        }
    }

    HttpMethod stringToHttpMethod(const std::string &str)
    {

        auto it = httpStrToMethodMap.find(str);
        if (it != httpStrToMethodMap.end())
        {
            return it->second;
        }
        else
        {
            return HttpMethod::UNKNOWN;
        }
    }
}