#define UseReceiverPacket
#include "RFC8200.h"
UseMediaAccessControlLibrary
static void Continue(struct work_struct *work){
    struct ReceiverPacket*packet=container_of(work,struct ReceiverPacket,work);
    GetMediaAccessControl()->Register(packet->dev,packet->router);
    printk(KERN_INFO "RFC8200: Received packet from %pI6 to %pI6, source port %u, destination port %u\n",
           packet->sourceAddress, packet->destinationAddress,
           ntohs(*packet->sourcePort), ntohs(*packet->destinationPort));
    kfree_skb(packet->skb);
    kfree(packet);
}
static bool IsLocalAddress(u8*address){
    u16 convertAddress[8];
    for(u8 i=0;i<8;i++)
        convertAddress[i]=ntohs(*(u16*)(address+i*2));
    return(convertAddress[0]==0&&convertAddress[1]==0&&convertAddress[2]==0&&convertAddress[3]==0&&convertAddress[4]==0&&convertAddress[5]==0&&convertAddress[6]==0&&convertAddress[7]==1)||((convertAddress[0]&65472)==65152)||((convertAddress[0]&65024)==64512);
}
static bool Receiver(u8*networkLayer,u8**sourceAddress,u8**destinationAddress,u16**sourcePort,u16**destinationPort,u8**transportLayer){
    *sourceAddress=networkLayer+8;
    *destinationAddress=networkLayer+24;
    if(IsLocalAddress(*sourceAddress)||IsLocalAddress(*destinationAddress)) 
        return false;
    *transportLayer=networkLayer+40;
    *sourcePort=(u16*)(*transportLayer);
    *destinationPort=(u16*)(*transportLayer+2);
    return !(ntohs(*destinationPort)==22); 
}
SystemSetup(RFC791, NULL, NULL, Bind(Receiver),Bind(Continue));