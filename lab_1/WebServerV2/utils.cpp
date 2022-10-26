#include "utils.h"

bool CheckIp(std::string ip) {
    if (ip == "") {
        return false;
    }
    std::string left;
    std::string right;
    for (int i = 0; i < 3; i++) {
        if (ip.find(".") == std::string::npos) {
            return false;
        }
        left = ip.substr(0, ip.find("."));

        right = ip.substr(ip.find(".") + 1, ip.size());
        if (left.size() == 0 || right.size() == 0) {
            return false;
        }
        int value = stoi(left);
        if (value < 0 || value > 255) {
            return false;
        }
        ip = right;
    }
    int value = stoi(ip);
    if (value < 0 || value > 255) {
        return false;
    }
    return true;
}

bool CheckPath(std::string path) {
    if (path == "") {
        return false;
    }
    UrlParser tmp(path);
    return tmp.is_ok_;
}

bool CheckPort(std::string port) {
    if (port == "") {
        return false;
    }
    int tmp = stoi(port);
    return tmp > 0 && tmp < 65535;
}

bool CheckThreadLimit(std::string thread_limit) {
    int limit = stoi(thread_limit);
    return limit > 0 && limit <= server_config::max_thread_num;
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
