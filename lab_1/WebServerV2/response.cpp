#include "response.h"

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

