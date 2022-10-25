/**
 * @author dong
 * @date 26/10/2022
 */

#pragma once
#ifndef WEBSERVERV1_RESPONSE_H
#define WEBSERVERV1_RESPONSE_H

#include "request.h"

class Response {
public:
    std::map<std::string, std::string> response_header_;
    std::string http_version_;
    int response_status_; // status code
    std::string status_word_; // status word

    Response(int status, std::string http_version);
    Response(Request);
    void AddHeader(std::string key, std::string value);
    void SetStatus(int status);
    void SetHttpVersion(std::string http_version);
    std::string ToString(); // the return string of the response

private:
    const std::map<int, std::string> status_words_ = {
            {200, "OK"},
            {400, "Bad Request"},
            {404, "Not Found"}
    };
};

Response::Response(Request request) {
    this->http_version_ = request.http_version_;
}

Response::Response(int status, std::string http_version) {
    this->response_status_ = status;
    this->http_version_ = http_version;
}

void Response::AddHeader(std::string key, std::string value) {
    this->response_header_.insert({key, value});
}

void Response::SetStatus(int status) {
    this->response_status_ = status;
    this->status_word_ = this->status_words_.find(status)->second;
}

void Response::SetHttpVersion(std::string http_version) {
    this->http_version_ = http_version;
}

std::string Response::ToString() {
    std::string ans = "";
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

#endif //WEBSERVERV1_RESPONSE_H
