#ifndef CLANG_REQUEST_H
#define CLANG_REQUEST_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

class HttpRequest
{

public:
      std::string method;
      std::string path;
      std::map<std::string, std::string> headers;

      void parseRequest(const std::string &raw_request);
      std::string readHtmlFile(const std::string &path);
      std::string getMimeType(const std::string &path);
};

#endif