#define UseReceiverPacket
#include "RFC791.h"
UseMediaAccessControlLibrary
static void Continue(struct work_struct *work){
    struct ReceiverPacket*packet=container_of(work,struct ReceiverPacket,work);
    GetMediaAccessControl()->Register(packet->dev,packet->router);
    printk(KERN_INFO "RFC791: Received packet from %pI4 to %pI4, source port %u, destination port %u\n",
           packet->sourceAddress, packet->destinationAddress,
           ntohs(*packet->sourcePort), ntohs(*packet->destinationPort));
    kfree_skb(packet->skb);
    kfree(packet);
}
static bool IsLocalAddress(u8*address) {
    return(address[0]== 10||(address[0]==172&&(address[1]>=16&&address[1]<=31))||(address[0]==192&&address[1]==168)||address[0]==127||(address[0]==169&&address[1]==254));
}
static bool Receiver(u8*networkLayer, u8**sourceAddress,u8**destinationAddress,u16**sourcePort,u16**destinationPort,u8**transportLayer){
    *sourceAddress=networkLayer+12;
    *destinationAddress=networkLayer+16;
    if(IsLocalAddress(*sourceAddress)||IsLocalAddress(*destinationAddress))return false; 
    *transportLayer=networkLayer+20;
    *sourcePort=(u16*)(*transportLayer);
    *destinationPort=(u16*)(*transportLayer+2);
    return !(ntohs(*destinationPort)==22); 
}
SystemSetup(RFC791, NULL, NULL,Bind(Receiver),Bind(Continue));