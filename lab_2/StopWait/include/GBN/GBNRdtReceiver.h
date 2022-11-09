/**
 * @author dong
 * @details GBNRdtReceiver
 */
#ifndef STOPWAIT_GBNRDTRECEIVER_H
#define STOPWAIT_GBNRDTRECEIVER_H

#include "../RdtReceiver.h"

class GBNRdtReceiver :public RdtReceiver {
private:
    int expectSequenceNumberRcvd;
    Packet lastAckPkt;
public:
    GBNRdtReceiver();
    ~GBNRdtReceiver() override;

public:
    void receive(const Packet &packet) override;
};
#endif //STOPWAIT_GBNRDTRECEIVER_H
