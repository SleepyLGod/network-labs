/**
 * @author dong
 * @details TCPReceiver
 */

#ifndef STOPWAIT_TCPRECEIVER_H
#define STOPWAIT_TCPRECEIVER_H
#include "RdtReceiver.h"
class TCPReceiver :public RdtReceiver {
private:
    int expectSequenceNumberRcvd;
    Packet lastAckPkt;
public:
    TCPReceiver();
    ~TCPReceiver() override;

public:
    void receive(const Packet &packet) override;
};
#endif //STOPWAIT_TCPRECEIVER_H
