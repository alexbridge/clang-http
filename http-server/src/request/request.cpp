#include "request.h"
#include "../http/mime-type.h"

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

std::string HttpRequest::readHtmlFile(const std::string &path)
{
    // TODO
    // ab html file me se content read krna hai.
    // iske liye hume fstream use krna padega.
    std::string file_name = path.substr(1, path.length());

    std::ifstream file("../" + file_name); // ifstream used for reading file if exists.
    int flag = 0;
    if (!file)
    {
        flag = 1;
        std::cerr << "File not found." << std::endl;
    }

    // std::cout<<"file found"<<std::endl;
    if (flag == 0)
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    return "";
}

std::string HttpRequest::getMimeType(const std::string &path)
{
    std::string fileExtension = path.substr(path.find_last_of(".") + 1);
    // std::cout<<fileExtension<<std::endl;
    return mimetype::MIME_TYPES[fileExtension];
}