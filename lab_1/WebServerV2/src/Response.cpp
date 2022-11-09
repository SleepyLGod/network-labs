#include "../include/Response.h"
using namespace std;

Response::Response(int status, string http_version) {
    this->status = status;
    this->http_version = http_version;
}

Response::Response(Request request) {
    this->http_version = request.http_version;
}

void Response::set_http_version(string http_version) {
    this->http_version = http_version;
}

void Response::set_status(int status) {
    this->status = status;
    this->word = this->status_words.find(status)->second; // 同时设置状态字
}

string Response::to_string() {
    string result = "";
    result += this->http_version;
    result += " ";
    result += ::to_string(this->status);
    result += " ";
    result += word;
    for (auto const & x : header) {
        result += "\r\n";
        result += (x.first + ": " + x.second);
    }
    result += "\r\n\r\n";
    return result;
}

void Response::add_header(string key, string value) {
    this->header.insert({key, value});
}
