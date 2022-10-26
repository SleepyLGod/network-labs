/**
 * @author dong
 * @date 26/10/2022
 */

#pragma once
#ifndef WEBSERVERV1_RESPONSE_H
#define WEBSERVERV1_RESPONSE_H

#include <chrono>
#include <ctime>
#include "request.h"

/**
 * @brief the class to process response data
 */
class Response {
public:
    std::map<std::string, std::string> response_header_;
    std::string http_version_;
    int response_status_{}; // status code
    std::string status_word_; // status word

    Response(int status, std::string http_version);
    explicit Response(Request);
    void AddHeader(std::string key, std::string value);
    void set_status(int status);
    void set_http_version(std::string http_version);
    std::string ToString(); // the return string of the response

private:
    const std::map<int, std::string> status_words_ = {
            {200, "OK"},
            {400, "Bad Request"},
            {404, "Not Found"}
    };
};


#endif //WEBSERVERV1_RESPONSE_H
