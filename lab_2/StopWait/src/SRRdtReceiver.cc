#include <Global.h>
#include <assert.h>
#include "SRRdtReceiver.h"

SRRdtReceiver::SRRdtReceiver() : rcv_base(1) { // 填充空的数据
    for (int i = 0; i < GBN_WINDOW_SIZE; i++)
        push_empty_packet();
    lastAckPkt.acknum = -1; // 初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
    lastAckPkt.checksum = 0;
    lastAckPkt.seqnum = -1; //忽略该字段
    for (char & i : lastAckPkt.payload)
        i = '.';
    lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

SRRdtReceiver::~SRRdtReceiver() = default;

void SRRdtReceiver::receive(const Packet &packet) {
    int checkSum = pUtils->calculateCheckSum(packet);
    if (checkSum == packet.checksum) { // 现在分析第一种情况，即序号在[rcv_base, rcv_base + N - 1]的情况
        bool in_case1 = false;
        bool in_case2 = false;
        int index = 0;
        if (rcv_base + GBN_WINDOW_SIZE <= MAX_SEQ) { //此时没有跨越边界
//            std::cout << "没有跨越边界" << std::endl;
            if (packet.seqnum >= rcv_base && packet.seqnum <= rcv_base + GBN_WINDOW_SIZE - 1) {
                in_case1 = true;
                index = packet.seqnum - rcv_base;
            }
        } else { // 跨越了边界，那么通过两个序号一起加上N来跳出边界
            if ((packet.seqnum + GBN_WINDOW_SIZE) % MAX_SEQ >= (rcv_base + GBN_WINDOW_SIZE) % MAX_SEQ &&
                (packet.seqnum + GBN_WINDOW_SIZE) % MAX_SEQ <= (rcv_base + 2 * GBN_WINDOW_SIZE - 1) % MAX_SEQ) {
                in_case1 = true;
                index = (packet.seqnum + GBN_WINDOW_SIZE) % MAX_SEQ - (rcv_base + GBN_WINDOW_SIZE) % MAX_SEQ;
            }
        }

        // 现在分析第二种情况，即序号在[rcv_base - N, rcv_base - 1]的情况
        if (rcv_base >= GBN_WINDOW_SIZE) { // 此时base距离序号0至少还有N个空间
            if (packet.seqnum >= rcv_base - GBN_WINDOW_SIZE && packet.seqnum <= rcv_base - 1)
                in_case2 = true;
        } else { // 如果base距离0不足N个空间，那么两者一起加上N来跨越边界
            if ((packet.seqnum + GBN_WINDOW_SIZE) % MAX_SEQ >= rcv_base &&
                (packet.seqnum + GBN_WINDOW_SIZE) % MAX_SEQ <= rcv_base + GBN_WINDOW_SIZE - 1) {
                in_case2 = true;
            }
        }
        // 理论上不可能同时发生case1 以及case2
        assert((!in_case1) || (!in_case2));
        // 正式开始处理
        if (in_case1) { // 如果是在第一个窗口的话
//            assert(buffers.at(index)->seqnum == index);
            if (packet.seqnum == rcv_base) {
                std::cout << "SR 接收方收到数据包 seq = " << packet.seqnum << "窗口发生变化: 由 " << std::endl;
                printWindow();
                std::cout << "变为: " << std::endl;
            }
            lastAckPkt.acknum = packet.seqnum;
            lastAckPkt.checksum = 0;
            lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
            if(!TESTING)
                pUtils->printPacket("接收方发送确认报文", lastAckPkt);
            pns->sendToNetworkLayer(SENDER, lastAckPkt);    // 调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
            if (packetState.at(index) == UNKNOW) {
                // 如果之前没有收到，更改状态并存储
//                std::cout << "收到paket的时候first packetState.size = " << packetState.size() << std::endl;
                packetState[index] = RECEIVED;
//                std::cout << "计算出来的index = " << index << "实际上的seq = " << packet.seqnum;
                Packet *temp = buffers.at(index);
                // 复制到对应的位置
                copy_packet(&packet, temp);
//                std::cout << "之前没有收到" << std::endl;
//                std::cout << "收到paket的时候 packetState.size = " << packetState.size() << std::endl;
                temp = nullptr;
            } else {
//                std::cout << "之前收到过" << std::endl;
            }
        }
        if (in_case2) { // 如果是第二种情况也要正常发送ack
            lastAckPkt.acknum = packet.seqnum;
            lastAckPkt.checksum = 0;
            lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
            if(!TESTING)
                pUtils->printPacket("接收方发送确认报文", lastAckPkt);
            pns->sendToNetworkLayer(SENDER, lastAckPkt);    //调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
//            std::cout << "根据规则发送的ack" << std::endl;
        }
//        std::cout << "此时收到的packet.seq = " << packet.seqnum << " rcv_base = " << rcv_base << std::endl;

        if (packet.seqnum == rcv_base) { // 如果等于基序号
            assert(in_case1);
//            std::cout << "等于rcv_base = " << rcv_base << " 此时packetState.size = " << packetState.size() << std::endl;
            while (packetState.at(0) == RECEIVED) {
                // 上交报文，并填充新的空数据
//                std::cout << "上交了一个数据" << std::endl;
                Message msg;
                memcpy(msg.data, buffers.at(0)->payload, sizeof(buffers.at(0)->payload));
                pns->delivertoAppLayer(RECEIVER, msg);
                packetState.erase(packetState.begin());
                buffers.erase(buffers.begin());
                push_empty_packet();
                rcv_base++;
                rcv_base %= MAX_SEQ;
//                std::cout << "rcv_base改变为" << rcv_base << std::endl;
            }
            printWindow();
        }
    }
}

void SRRdtReceiver::push_empty_packet() { // 填充新的数据到缓冲区，每个字段的值并不重要
    auto *packet = new Packet();
    buffers.push_back(packet);
    packetState.push_back(UNKNOW);
    packet = nullptr;
}

void SRRdtReceiver::copy_packet(const Packet *source, Packet *dest) {
    dest->checksum = source->checksum;
    dest->acknum = source->acknum;
    dest->seqnum = source->acknum;
    for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
        dest->payload[i] = source->payload[i];
    assert(pUtils->calculateCheckSum(*source) == source->checksum);
}

void SRRdtReceiver::printWindow() {
    if(TESTING) {
        std::cout << "> '-' 表示该包已经被缓存 <" << std::endl;
        if (packetState.size() == 0) {
            std::cout << "[ ]" << std::endl;
            return;
        }
        std::cout << "[ ";
        for (int i = 0; i < packetState.size(); i++) {
            if (packetState.at(i) == RECEIVED) {
                std::cout << "-" << (i + rcv_base) % MAX_SEQ << "-, ";
            } else {
                std::cout << (i + rcv_base) % MAX_SEQ << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
}