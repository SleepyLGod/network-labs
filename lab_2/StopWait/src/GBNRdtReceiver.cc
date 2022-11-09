#include "Global.h"
#include "GBNRdtReceiver.h"

GBNRdtReceiver::GBNRdtReceiver() : expectSequenceNumberRcvd(1) {
    lastAckPkt.acknum = -1; // 初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
    lastAckPkt.checksum = 0;
    lastAckPkt.seqnum = -1;    //忽略该字段
    for (char & i : lastAckPkt.payload)
        i = '.';
    lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

GBNRdtReceiver::~GBNRdtReceiver() = default;

void GBNRdtReceiver::receive(const Packet &packet) {
    int checkSum = pUtils->calculateCheckSum(packet);
    if (checkSum == packet.checksum && this->expectSequenceNumberRcvd == packet.seqnum) {
        if (!TESTING)
            pUtils->printPacket("接收方正确收到发送方的报文", packet);
        Message msg;
        memcpy(msg.data, packet.payload, sizeof(packet.payload));
        pns->delivertoAppLayer(RECEIVER, msg);

        lastAckPkt.acknum = packet.seqnum; // 确认序号等于收到的报文序号
        lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
        if (!TESTING)
            pUtils->printPacket("接收方发送确认报文", lastAckPkt);
        pns->sendToNetworkLayer(SENDER, lastAckPkt);    // 调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方

        this->expectSequenceNumberRcvd += 1; // 接收序号在0-1之间切换
        this->expectSequenceNumberRcvd %= MAX_SEQ;
    } else {
        if (checkSum != packet.checksum) {
            if (!TESTING)
                pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
        } else {
            if (!TESTING)
                pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
        }
        if(!TESTING)
            pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
        pns->sendToNetworkLayer(SENDER, lastAckPkt);    // 调用模拟网络环境的sendToNetworkLayer，通过网络层发送上次的确认报文
    }
}