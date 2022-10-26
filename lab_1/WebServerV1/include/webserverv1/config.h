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
     const char *const ip_to_listen = "0.0.0.0";
     const char *const path = "/home/dong/Git-repos/network-labs/lab_1/";
     const char *const not_found = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/404.html";
     const char *const bad_request = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/400.html";
     const char *const index = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/index.html";
 }

#endif //WEBSERVERV1_CONFIG_H
