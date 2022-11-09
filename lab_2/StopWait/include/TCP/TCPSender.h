/**
 * @author dong
 * @details TCPSender
 */

#ifndef STOPWAIT_TCPSENDER_H
#define STOPWAIT_TCPSENDER_H

#include "RdtSender.h"
#include <vector>
#include <map>


class TCPSender: public RdtSender {
private:
    bool waitingState;				// 是否处于等待Ack的状态
    int base;
    int nextseqnum;
    std::vector<Packet *> packges;
    std::map<int, int> ackCount;

    void printWindow();
public:
    bool getWaitingState() override;
    bool send(const Message &message) override;						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
    void receive(const Packet &ackPkt) override;						//接受确认Ack，将被NetworkServiceSimulator调用
    void timeoutHandler(int seqNum) override;					//Timeout handler，将被NetworkServiceSimulator调用

public:
    TCPSender();
    ~TCPSender() override;

};


#endif //STOPWAIT_TCPSENDER_H
