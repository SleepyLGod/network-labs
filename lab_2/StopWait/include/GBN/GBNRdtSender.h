/**
 * @author dong
 * @details GBNRdtSender
 */
#ifndef STOPWAIT_GBNRDTSENDER_H
#define STOPWAIT_GBNRDTSENDER_H

#include "RdtSender.h"
#include <vector>

class GBNRdtSender: public RdtSender {
private:
    bool waitingState;				// 是否处于等待Ack的状态
    int base;
    int nextseqnum;
    std::vector<Packet *> packges;
    void printWindow() const;

public:
    bool getWaitingState();
    bool send(const Message &message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
    void receive(const Packet &ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用
    void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用
public:
    GBNRdtSender();
    virtual ~GBNRdtSender();

};

#endif //STOPWAIT_GBNRDTSENDER_H
