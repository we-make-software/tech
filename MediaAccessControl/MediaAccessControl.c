#include "MediaAccessControl.h"
UseRFC791Library
UseRFC8200Library

static bool IsLocal(u8*dataLink) {
    return (*dataLink&2);
}
static int ContinueReceiver2048(struct sk_buff*skb,struct net_device*dev,u8*router,u8*dataLink,u8*networklayer,u8*sourceAddress,u8*destinationAddress,u16*sourcePort,u16*destinationPort){

    return 1;
}
static int ContinueReceiver34527(struct sk_buff*skb,struct net_device*dev,u8*router,u8*dataLink,u8*networklayer,u8*sourceAddress,u8*destinationAddress,u16*sourcePort,u16*destinationPort){

    return 1;
}
static int Receiver(struct sk_buff*skb,struct net_device*dev){
    u8*dataLink=skb_mac_header(skb);
    u8*router=data+6;
    if(IsLocal(dataLink)||IsLocal(router))return 0;
    u8*networkLayer=dataLink+14;
    u8*sourceAddress,*destinationAddress;
    u16*sourcePort,*destinationPort;
    return ntohs(*(u16*)(dataLink+12))==2048?
        GetRFC791()->Receiver(networkLayer,&sourceAddress,&destinationAddress,&sourcePort,&destinationPort)?
            ContinueReceiver2048(skb,dev,router,dataLink,networkLayer,sourceAddress,destinationAddress,sourcePort,destinationPort):0:
        GetRFC8200()->Receiver(networkLayer,&sourceAddress,&destinationAddress,&sourcePort,&destinationPort)?
            ContinueReceiver34527(skb,dev,router,dataLink,networkLayer,sourceAddress,destinationAddress,sourcePort,destinationPort):0;
}
End{

}
SystemSetup(MediaAccessControl, NULL, BindEnd,Bind(Receiver));