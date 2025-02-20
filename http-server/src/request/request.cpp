#include "request.h"

void HttpRequest::parseRequest(const std::string &raw_request)
{
    // Todo
    // raw request se Get method se path nikalkr map me daalna hai.
    // uss path me rakhi file se html read krna hai.(hope i will make a new method for this.)
    // ab html file se content read krne ke baad string stream me store krna hai.
    // aur sara content ko http response ke format me frame krke browser ko bhejna hai.
    int curr_index = 0;
    while (curr_index < raw_request.length())
    {
        if (raw_request[curr_index] == ' ')
        {
            break;
        }
        method += raw_request[curr_index];
        curr_index++;
    }
    // std::cout<<method<<std::endl;
    headers["method"] = method;

    curr_index++;
    while (curr_index < raw_request.length())
    {
        if (raw_request[curr_index] == ' ')
        {
            break;
        }
        path += raw_request[curr_index];
        curr_index++;
    }

    headers["path"] = path;

    // mujhe ab method mil gya hai and path mil gya hai ab mai path me se file ka name nikaalunga aur
    // html file ko open karke uska content read karunga.
    // iske liye mai ek methon banaunga readhtmlFile().
}