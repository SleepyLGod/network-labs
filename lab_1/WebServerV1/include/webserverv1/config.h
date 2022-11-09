/**
 * @author dong
 * @date 26/10/2022
 */

#ifndef WEBSERVERV1_CONFIG_H
#define WEBSERVERV1_CONFIG_H
#include "iostream"

 namespace server_config {
//     constexpr int port = 8084;
//     constexpr int max_thread_num = 80;
//     const char *const ip_to_listen = "127.0.0.0";
     int port;
     int max_thread_num;
     char* ip_to_listen;
     const char *const path = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/";
     const char *const not_found = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/404_dong.html";
     const char *const bad_request = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/400_dong.html";
     const char *const index = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/index_dong.html";
 }

#endif //WEBSERVERV1_CONFIG_H
