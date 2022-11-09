/**
 * @author dong
 * @details SRRdtReceiver
 */

#ifndef STOPWAIT_SRRDTRECEIVER_H
#define STOPWAIT_SRRDTRECEIVER_H
#include "RdtReceiver.h"
#include <vector>
class SRRdtReceiver :public RdtReceiver {
private:
    Packet lastAckPkt;
    enum {RECEIVED, UNKNOW};
    std::vector<Packet *> buffers;
    std::vector<int> packetState;
    int rcv_base;

    // 填充空的packet
    void push_empty_packet();
    static void copy_packet(const Packet * source, Packet * dest);
    void printWindow();
public:
    SRRdtReceiver();
    ~SRRdtReceiver() override;

public:
    void receive(const Packet &packet) override;
};
#endif //STOPWAIT_SRRDTRECEIVER_H
