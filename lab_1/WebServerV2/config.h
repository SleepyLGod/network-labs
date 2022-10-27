/**
 * @author dong
 * @date 26/10/2022
 */

#ifndef CONFIG_H
#define CONFIG_H

 namespace server_config {
     constexpr int port = 8080;
     constexpr int max_thread_num = 30;
     const char *const ip_to_listen = "127.0.0.0";
     const char *const path = "/home/dong/Git-repos/network-labs/lab_1/WebServerV2";
     const char *const not_found = "/home/dong/Git-repos/network-labs/lab_1/WebServerV2/executable/static/404.html";
     const char *const bad_request = "/home/dong/Git-repos/network-labs/lab_1/WebServerV2/executable/static/400.html";
     const char *const index = "/home/dong/Git-repos/network-labs/lab_1/WebServerV2/executable/static/index.html";
 }

#endif // CONFIG_H
