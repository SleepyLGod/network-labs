#ifndef GLOBAL_H
#define GLOBAL_H
#define TESTING true // TESTING表示是否在测试，如果为 true 则会输出窗口大小等信息
#define TESTQR true // TESTQR表示是否在测试快速重传，如果为 true 则会输出快速重传信息

#include "Tool.h"
#include "NetworkService.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

#define GBN_WINDOW_SIZE 4
#define SEQ_BIT 3
#define MAX_SEQ (1 << SEQ_BIT)

#define INPUT_FILE_URL "/home/dong/Git-repos/network-labs/lab_2/StopWait/res/input.txt"
#define OUTPUT_FILE_URL "/home/dong/Git-repos/network-labs/lab_2/StopWait/res/output.txt"

extern  Tool *pUtils;						// 指向唯一的工具类实例，只在main函数结束前delete
extern  NetworkService *pns;				// 指向唯一的模拟网络环境类实例，只在main函数结束前delete

#endif