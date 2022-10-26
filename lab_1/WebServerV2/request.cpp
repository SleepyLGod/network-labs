#include "request.h"

/**
 * @brief check out if the string a ends with string b
 * @param a
 * @param b
 * @return bool
 */
bool EndsWith(std::string a, std::string b) {
    if (a.length() >= b.length())
        return (0 == a.compare(a.length() - b.length(), b.length(), b));
    return false;
}

/**
 * @brief constructor
 * @param request
 */
Request::Request(std::string request) {
    std::istringstream istringstream(request);
    std::string line;
    getline(istringstream, line); // first line: request line
    std::istringstream words(line); // split the line into several words
    words >> this->request_type_;
    words >> this->request_url_;
    words >> this->http_version_;
    // request header:
    while (getline(istringstream, line, '\n')) {
        if (line == "\r") {
            break;
        }
        std::string key = line.substr(0, line.find_first_of(':'));
        std::string value = line.substr(line.find_first_of(':'), line.size() - line.find_first_of(':') - 1);
        this->request_header_.insert({key, value});
    }
}
