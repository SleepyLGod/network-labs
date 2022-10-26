/**
 * @author dong
 * @date 26/10/2022
 */

#ifndef CONFIG_H
#define CONFIG_H
#include "iostream"

 namespace server_config {
     constexpr int port = 8080;
     constexpr int max_thread_num = 80;
     const char *const ip_to_listen = "127.0.0.0";
//     const char *const path = "/home/dong/Git-repos/network-labs/lab_1/";
     const char *const not_found = "executable/static/404.html";
     const char *const bad_request = "executable/static/400.html";
     const char *const index = "executable/static/index.html";
 }

#endif // CONFIG_H
