/**
 * @author dong
 * @date 26/10/2022
 */

#pragma once
#ifndef WEBSERVERV1_RESPONSE_H
#define WEBSERVERV1_RESPONSE_H

#include <chrono>
#include <ctime>
#include "webserverv1/request.h"

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

/**
 * @brief constructor
 * @param request
 */
Response::Response(Request request) {
    this->http_version_ = request.http_version_;
}

/**
 * @brief constructor
 * @param status
 * @param http_version
 */
Response::Response(int status, std::string http_version) {
    this->response_status_ = status;
    this->http_version_ = http_version;
    // this->http_version_ = std::move(http_version);
}

/**
 * @brief add response header
 * @param key
 * @param value
 */
void Response::AddHeader(std::string key, std::string value) {
    this->response_header_.insert({key, value});
}

/**
 * @brief set response status code
 * @param status
 */
void Response::set_status(int status) {
    this->response_status_ = status;
    this->status_word_ = this->status_words_.find(status)->second;
}

/**
 * @brief set response http version
 * @param http_version
 */
void Response::set_http_version(std::string http_version) {
    this->http_version_ = http_version;
    // this->http_version_ = std::move(http_version);
}

/**
 * @brief turn the response to a string
 * @return string
 */
std::string Response::ToString() {
    std::string ans;
    ans += this->http_version_;
    ans += " ";
    ans += std::to_string(this->response_status_);
    ans += " ";
    ans += this->status_word_;
    for (auto const& tmp : response_header_) {
        ans += "\r\n";
        ans += (tmp.first + ": " + tmp.second);
    }
    ans += "\r\n\r\n";
    return ans;
}

/**
 * @brief print logs after response
 * @param response
 * @param request
 * @param ip
 */
void LogPrint(Response response, Request request, std::string ip) {
    auto current = std::chrono::system_clock::now();
    auto current_time = std::chrono::system_clock::to_time_t(current);
    auto out_put_time = std::string(std::ctime(&current_time));
    out_put_time = out_put_time.substr(0, out_put_time.size() - 1); // delete the '\n'
    std::cout << ip << " - - "
                  << " [" << out_put_time << "] \" "
                  << request.request_type_ << " "
                  << request.request_url_ << " "
                  << request.http_version_ << "\""
                  << response.response_status_ << " - " << std::endl;
}
#endif //WEBSERVERV1_RESPONSE_H
