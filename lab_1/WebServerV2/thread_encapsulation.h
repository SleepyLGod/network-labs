/**
 * @author dong
 * @date 26/10/2022
 */

#ifndef THREAD_ENCAPSULATION_H
#define THREAD_ENCAPSULATION_H

#include <thread>
#include <mutex>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "response.h"
#include "url_parser.h"

/**
 * @brief the encapsulation of the standard lib <thread>
 */
class ThreadEncapsulation {
public:
    bool is_finished_;
    bool is_added_{};
    int flag_{};

    ThreadEncapsulation();
    void CreateThread(int, std::string);
};

#endif // THREAD_ENCAPSULATION_H
