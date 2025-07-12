#include "RFC9293.h"
//RFC9293 is TCP, which is built on bottom of RFC791 (IP) and RFC8200 (IPv6).
/*
    * RFC 9293: Transmission Control Protocol (TCP)
    * https://datatracker.ietf.org/doc/html/rfc9293
    * 
    * This code defines the TCP header structure and provides functions to handle TCP packets.
    * It includes functions for receiving TCP packets, printing their contents, and handling
    * different TCP flags.
    * * The TCP header structure includes fields such as source and destination ports,
    *   sequence and acknowledgment numbers, flags, window size, checksum, and urgent pointer.
    *   The flags include:
    *  - FinishFlag: Indicates the end of a connection.
    * - SynchronizeSequenceNumbersFlag: Used to synchronize sequence numbers during connection establishment.
    *   ResetConnectionFlag: Indicates a request to reset the connection.
    *  PushFunctionFlag: Indicates that the sender is requesting immediate delivery of data.
    *  AcknowledgmentFlag: Indicates that the acknowledgment number is valid.
    * UrgentPointerFlag: Indicates that the urgent pointer field is valid.
    * ExplicitCongestionNotificationEchoFlag: Used for explicit congestion notification.
    * 
  0                   1                   2                   3   
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |          Source Port          |       Destination Port        |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                        Sequence Number                        |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |                    Acknowledgment Number                      |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |  Data |Rese-|N|C|E|U|A|P|R|S|F|                               |
 | Offset|rved|S|W|C|R|C|S|S|Y|I|            Window             |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |           Checksum            |         Urgent Pointer        |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


*/
struct NoPadding RFC9293Pointer {
    u16 SourcePort, DestinationPort;
    u32 SequenceNumber, AcknowledgmentNumber;
#if IsLittleEndian
   u16 Finish:1,
       SynchronizeSequenceNumbers:1,
       ResetConnection:1,
       PushFunction:1,
       Acknowledgment:1,
       UrgentPointer:1,
       ExplicitCongestionNotification:1,
       CongestionWindowReduced:1,
       NonceSum:1,
       Reserved:3,
       DataOffset:4;
#else
   u16 DataOffset:4,
       Reserved:3,
       NonceSum:1,
       CongestionWindowReduced:1,
       ExplicitCongestionNotification:1,
       UrgentPointer:1,
       Acknowledgment:1,
       PushFunction:1,
       ResetConnection:1,
       SynchronizeSequenceNumbers:1,
       Finish:1;
#endif
    u16 Window;
    u16 Checksum;
};

struct Packet{
    struct IEEE802_3Pointer*IEEE802_3;
    struct RFC1122Pointer*RFC1122;
    union
    {
       struct RFC791Pointer*RFC791;
       struct RFC8200Pointer*RFC8200;
    }NetworkLayer;
    struct RFC9293Pointer*RFC9293;
    u8 Unused[sizeof(void*)*2];
    struct sk_buff*skb;
    struct work_struct work;
};


static void RFC791Receiver(struct Packet*packet,struct RFC791NetworkAddress*client,struct RFC791NetworkAddress*server) {
    switch (ntohs(packet->RFC9293->DestinationPort)) {

        default:{
            //print start
            printk(KERN_INFO "RFC9293: Start");
            printk(KERN_INFO "RFC9293: End");

        }
    }
    printk(KERN_INFO "RFC9293: RFC791Receiver called");
}
static void RFC8200Receiver(struct Packet*packet,struct RFC8200NetworkAddress*client,struct RFC8200NetworkAddress*server) {
    switch (ntohs(packet->RFC9293->DestinationPort)) {

        default:{
            printk(KERN_INFO "RFC9293: Start");
         printk(KERN_INFO "RFC9293: End");    
        }
    }
    printk(KERN_INFO "RFC9293: RFC8200Receiver called");
}
End{}
Start(RFC9293, Bind(RFC791Receiver),Bind(RFC8200Receiver)){}