/**
 * @author dong
 * @details 定义控制台应用程序的入口点
 */

#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "StopWait/StopWaitRdtSender.h"
#include "StopWait/StopWaitRdtReceiver.h"
#include "GBN/GBNRdtReceiver.h"
#include "GBN/GBNRdtSender.h"
#include "SR/SRRdtReceiver.h"
#include "SR/SRRdtSender.h"
#include "TCP/TCPReceiver.h"
#include "TCP/TCPSender.h"

RdtReceiver * pr;
RdtSender * ps;

void RDTPIniter (std::string option) {
    if (std::equal(option.begin(), option.end(),"TCP")) {
        pr = new TCPReceiver();
        ps = new TCPSender();
    } else if(std::equal(option.begin(), option.end(),"SR")) {
        pr = new SRRdtReceiver();
        ps = new SRRdtSender();
    } else if (std::equal(option.begin(), option.end(),"SW")) {
        ps = new StopWaitRdtSender();
        pr = new StopWaitRdtReceiver();
    } else if (std::equal(option.begin(), option.end(),"GBN")) {
        ps = new GBNRdtSender();
        pr = new GBNRdtReceiver();
    }
}

void RDTPIniter (int option) {
    if (option == 3) {
        pr = new TCPReceiver();
        ps = new TCPSender();
    } else if(option == 2) {
        pr = new SRRdtReceiver();
        ps = new SRRdtSender();
    } else if (option == 0) {
        ps = new StopWaitRdtSender();
        pr = new StopWaitRdtReceiver();
    } else if (option == 1) {
        ps = new GBNRdtSender();
        pr = new GBNRdtReceiver();
    }
}

int main(int argc, char* argv[]) {
    std::cout << "🌃 Which RDTP would you like to choose: " << std::endl
        //<< "0: StopWait" << std::endl
        << "1: GBN" << std::endl
        << "2: SR" << std::endl
        << "3: TCP" << std::endl
        << "💁 Please input the numnber!" << std::endl;
    int option;
    std::cin >> option;
    while (!(option >= 0 && option <= 3)) {
        std::cout << "🙈 ERROR! Input the number again, please: " << std::endl;
        std::cin >> option;
    }
    RDTPIniter(option);
	pns->setRunMode(0);  // VERBOS模式
    if (TESTING || TESTQR) {
        pns->setRunMode(1);  // 安静模式
    }
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile(INPUT_FILE_URL);
	pns->setOutputFile(OUTPUT_FILE_URL);
	pns->start();
	delete ps;
	delete pr;
	delete pUtils;		// 指向唯一的工具类实例，只在main函数结束前delete
	delete pns;			// 指向唯一的模拟网络环境类实例，只在main函数结束前delete
	return 0;
}