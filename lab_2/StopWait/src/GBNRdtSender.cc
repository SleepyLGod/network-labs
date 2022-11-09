#include <cstring>
#include <Global.h>
#include <assert.h>
#include "GBNRdtSender.h"

bool GBNRdtSender::getWaitingState() {
    return waitingState;
}

GBNRdtSender::GBNRdtSender():nextseqnum(1), waitingState(false),base(1) {}
GBNRdtSender::~GBNRdtSender(){}
bool GBNRdtSender::send(const Message &message) {
    if (packges.size() >=  GBN_WINDOW_SIZE) return false;
    Packet * packet = new Packet();
    packet->acknum = -1;
    packet->checksum = 0;
    packet->seqnum = nextseqnum;
    memcpy(packet->payload, message.data, sizeof(message.data));
    packet->checksum = pUtils->calculateCheckSum(*packet);
    packges.push_back(packet);
    if (!TESTING)
        pUtils->printPacket("发送方发送报文", *packet);
    if (base == nextseqnum)
        pns->startTimer(SENDER, Configuration::TIME_OUT,packet->seqnum);			//启动发送方定时器
    nextseqnum++;
    nextseqnum %= MAX_SEQ;
    assert(nextseqnum < MAX_SEQ);
    waitingState = packges.size() >= GBN_WINDOW_SIZE;

    pns->sendToNetworkLayer(RECEIVER, *packet);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
    packet = nullptr;
    return true;
}

void GBNRdtSender::receive(const struct Packet & ackPkt) {
    int checkSum = pUtils->calculateCheckSum(ackPkt);
    if (checkSum ==  ackPkt.checksum) { // 如果没有损坏
        if (((nextseqnum > base) && (ackPkt.acknum >= base) &&
            (ackPkt.acknum < nextseqnum)) || ((nextseqnum < base) &&
            ((ackPkt.acknum < nextseqnum) || (ackPkt.acknum >= base)))) { // 只有当收到的ack是在当前窗口的时候才进行处理, 否则直接丢弃, 并将waitingState置为false
            waitingState = false;
            // 先暂存base的值,用于停止计时器
            int temp = base;
            // 更新base的值
            std::cout << "GBN 发送方收到ack = " << ackPkt.acknum << "窗口发生变化: 由 " << std::endl;
            printWindow();
            std::cout << "变为: " << std::endl;
            base = ackPkt.acknum + 1;
            base %= MAX_SEQ;
            printWindow();
            int index = 0;
            if (ackPkt.acknum >= temp) {
                index = ackPkt.acknum - temp;
            } else {
                index = MAX_SEQ - temp + ackPkt.acknum;
            }
//            std::cout << "收到ack, 此时ack = " << ackPkt.acknum << " base = " << base << " temp = " << temp << " next = " << nextseqnum << std::endl;
            // 假设此时是base = 2 ^ k - 1，然后收到的ack = 0, 那么, 结果应该要删除2个
            for (int i = 0; i <= index; i++) // 遍历每一个packet, 销毁对应的对象
                delete packges.at(i);

            // 移除所有已经接收到的对象指针, 其中base - temp表示收到的个数
            packges.erase(packges.begin(), packges.begin() + index + 1);
            if (base == nextseqnum) {
                pns->stopTimer(SENDER, temp);
            } else {
                pns->stopTimer(SENDER, temp);
                pns->startTimer(SENDER, Configuration::TIME_OUT, base);
            }
        }
    }
}

void GBNRdtSender::timeoutHandler(int seqNum) {
    // 按照理论来说应该始终是base超时
    assert(seqNum == base);
    pns->stopTimer(SENDER, seqNum);
    pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
    int limit = 0;
    if (nextseqnum > base) { // 如果没有越过分界点
        limit = nextseqnum - base;
    } else if (nextseqnum < base) { // 如果越过了分界点
        limit = MAX_SEQ - base + nextseqnum;
        // 假设此时base = 2 ^ k - 1, nextsequm = 1, 那么应该重发2个包
    }

    for (int i = 0; i < limit; i++) {
        // 遍历从base到nextseqnum-1的所有报文,进行重传
        Packet * packet = packges.at(i);
        if (!TESTING)
            pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", *packet);
        pns->sendToNetworkLayer(RECEIVER, *packet);
    }
}

void GBNRdtSender::printWindow() const {
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