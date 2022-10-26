/**
 * @author dong
 * @date 26/10/2022
 */

#ifndef WEBSERVERV1_CONFIG_H
#define WEBSERVERV1_CONFIG_H
#include "iostream"

 namespace server_config {
     constexpr int port = 8080;
     constexpr int max_thread_num = 30;
     const std::string ip_to_listen = "0.0.0.0";
     const std::string path = "/home/dong/Git-repos/network-labs/lab_1";
     const std::string not_found = "/home/dong/Git-repos/network-labs/lab_1/404.html";
     const std::string bad_request = "/home/dong/Git-repos/network-labs/lab_1/400.html";
     const std::string index = "/home/dong/Git-repos/network-labs/lab_1/index.html";
 }

#define PORT 8080
#define MAX_THREAD_NUM 30
#define IP_TO_LISTEN "0.0.0.0"
#define PATH "/home/dong/Git-repos/network-labs/lab_1"
#define NOT_FOUND "/home/dong/Git-repos/network-labs/lab_1/404.html"
#define BAD_REQUEST "/home/dong/Git-repos/network-labs/lab_1/400.html"
#define INDEX "/home/dong/Git-repos/network-labs/lab_1/index.html"

#endif //WEBSERVERV1_CONFIG_H
