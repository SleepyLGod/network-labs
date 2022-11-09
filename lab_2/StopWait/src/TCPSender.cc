#include <cstring>
#include <Global.h>
#include <assert.h>
#include "TCPSender.h"

bool TCPSender::getWaitingState() {
    return waitingState;
}

TCPSender::TCPSender():nextseqnum(1), waitingState(false),base(1) {}
TCPSender::~TCPSender(){}
bool TCPSender::send(const Message &message) {
    if (packges.size() >=  GBN_WINDOW_SIZE) {
        return false;
    }
    auto * packet = new Packet();
    packet->acknum = -1;
    packet->checksum = 0;
    packet->seqnum = nextseqnum;
    memcpy(packet->payload, message.data, sizeof(message.data));
    packet->checksum = pUtils->calculateCheckSum(*packet);
    packges.push_back(packet);
    if(!TESTING) {pUtils->printPacket("发送方发送报文", *packet);}
    if (base == nextseqnum) {
        // 直接将序号设置为0
        pns->startTimer(SENDER, Configuration::TIME_OUT,0);			//启动发送方定时器
    }
    nextseqnum++;
    nextseqnum %= MAX_SEQ;
    assert(nextseqnum < MAX_SEQ);
    waitingState = packges.size() >=  GBN_WINDOW_SIZE;

    pns->sendToNetworkLayer(RECEIVER, *packet);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
    packet = nullptr;
    return true;
}

void TCPSender::receive(const struct Packet & ackPkt) {
    int checkSum = pUtils->calculateCheckSum(ackPkt);
    if (checkSum ==  ackPkt.checksum) {
        // 如果没有损坏
        if (((nextseqnum > base) && (ackPkt.acknum >= base) && (ackPkt.acknum < nextseqnum)) || ((nextseqnum < base) && ((ackPkt.acknum < nextseqnum) || (ackPkt.acknum >= base)))) {
            // 只有当收到的ack是在当前窗口的时候才进行处理, 否则直接丢弃
            // 并将waitingState置为false
            waitingState = false;
            // 先暂存base的值,用于停止计时器
            int temp = base;
            // 更新base的值

            std::cout << "TCP 发送方收到ack = " << ackPkt.acknum << "窗口发生变化: 由 " << std::endl;
            printWindow();
            std::cout << "变为: " << std::endl;

            base = ackPkt.acknum + 1;
            base %= MAX_SEQ;
            int index = 0;
            if (ackPkt.acknum >= temp) {
                index = ackPkt.acknum - temp;
            } else {
                index = MAX_SEQ - temp + ackPkt.acknum;
            }
//            std::cout << "收到ack, 此时ack = " << ackPkt.acknum << " base = " << base << " temp = " << temp << " next = " << nextseqnum << std::endl;

            // 假设此时是base = 2 ^ k - 1，然后收到的ack = 0, 那么, 结果应该要删除2个
            for (int i = 0; i <= index; i++) {
                // 遍历每一个packet, 销毁对应的对象
                delete packges.at(i);
            }

            // 移除所有已经接收到的对象指针, 其中base - temp表示收到的个数
            packges.erase(packges.begin(), packges.begin() + index + 1);
            if (base == nextseqnum) {
                pns->stopTimer(SENDER, 0);
            } else {
                pns->stopTimer(SENDER, 0);
                pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
            }
            if (ackCount.find(ackPkt.acknum) != ackCount.end()) {
                // 如果之前就有的话，说明是上一轮留下来的，那么就重置为1
                ackCount[ackPkt.acknum] = 1;
            } else {
                // 如果没有的话置为1
                ackCount.insert({ackPkt.acknum, 1});
            }
            printWindow();
        }
        else {
            // 如果不在当前的窗口当中
//            std::cout << "收到的ack = " << ackPkt.acknum << std::endl;
//            assert(ackCount.find(ackPkt.acknum) != ackCount.end());
            ackCount[ackPkt.acknum]++;
            if (ackCount[ackPkt.acknum] == 4 || ackPkt.acknum == -1) {
                // 如果达到了4个重复的ack，执行快速重传，或者是第一个数据包出错所发送的ack = -1
                assert(packges.size() > 0);
                Packet * packet = packges.at(0);
                if(!TESTING) {pUtils->printPacket("收到3个重复ack，执行快速重传", *packet);}
                if (TESTQR) {
                    std::cout << "收到重复ack = " << ackPkt.acknum << "执行快速重传" << std::endl;
                }
                pns->sendToNetworkLayer(RECEIVER, *packet);
                ackCount[ackPkt.acknum] = 0;
            }
        }
    }
}

void TCPSender::timeoutHandler(int seqNum) {
    // 按照理论来说应该始终是base超时
//    assert(seqNum == base);
    assert(packges.size() > 0);
    pns->stopTimer(SENDER, 0);
    pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
    // 只对最开始的一个包进行重传
    Packet * packet = packges.at(0);
    if(!TESTING) {pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", *packet);}
    pns->sendToNetworkLayer(RECEIVER, *packet);
    if (ackCount.find(seqNum) != ackCount.end()) {
        ackCount[seqNum] = 0;
    }
}

void TCPSender::printWindow() {
    std::cout << "> '-' 表示该包已被确认<" << std::endl;
    if (TESTING) {
        if (base < nextseqnum) {
            std::cout << "[ ";
            for (int i = base; i < nextseqnum;i++) {
                std::cout << i << ", ";
            }
            std::cout << "]" << std::endl;
        } else if (base > nextseqnum) {
            std::cout << "[ ";
            for (int i = base; i < MAX_SEQ; i++) {
                std::cout << i << ", ";
            }
            for (int i = 0; i < nextseqnum; i++) {
                std::cout << i << ", ";
            }
            std::cout << "]" << std::endl;
        } else {
            std::cout << "[ ]" << std::endl;
        }
    }
}