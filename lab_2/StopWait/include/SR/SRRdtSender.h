/**
 * @author dong
 * @details SRRdtSender
 */

#ifndef STOPWAIT_SRRDTSENDER_H
#define STOPWAIT_SRRDTSENDER_H

#include "RdtSender.h"
#include <vector>
class SRRdtSender :public RdtSender {
private:
    enum {UNKWON, RECEIVED};
    bool waitingState;	// 是否处于等待Ack的状态
    int base;
    int nextseqnum;
    std::vector<Packet *> packges;
    std::vector<int> packetState;
    void printWindow();

public:
    SRRdtSender();
    ~SRRdtSender() override;

public:
    bool getWaitingState() override;
    bool send(const Message &message) override;		// 发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
    void receive(const Packet &ackPkt) override;	// 接受确认Ack，将被NetworkServiceSimulator调用
    void timeoutHandler(int seqNum) override;		// Timeout handler，将被NetworkServiceSimulator调用

};
#endif //STOPWAIT_SRRDTSENDER_H
