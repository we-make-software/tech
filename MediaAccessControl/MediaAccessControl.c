#define UseReceiverPacket
#include "MediaAccessControl.h"
struct Router{
    u8 address[6];
    struct net_device*dev;
    u16 Used;
    struct list_head list;
}
static LIST_HEAD(routers);
static DEFINE_MUTEX(lock);
static struct Router*Find(u8*address){
    struct Router*router;
    list_for_each_entry(router,&routers,list) {
        if(memcmp(router->address,address,6) == 0) {
            return router;
        }
    }
    return NULL;
}
static void Hookup(struct Router*router){
    if(router)
        router->Used++;
}
static void Unhook(struct Router*router){
    if(!router||!router->Used)
        router->Used--;
    if(!router->Used){
        dev_put(router->dev);
        list_del(&router->list);
        kfree(router);
    }
}
static struct Router*Register(struct net_device*dev,u8*router){
    struct Router*existingRouter=Find(router);
    if(existingRouter)
      return existingRouter;
    mutex_lock(&lock);
    existingRouter=Find(router);
    if(existingRouter){
        mutex_unlock(&lock);
        return existingRouter;
    }
    existingRouter=kmalloc(sizeof(struct Router),GFP_KERNEL);
    if(!existingRouter)return NULL;
    dev_hold(dev);
    existingRouter->dev=dev;
    existingRouter->used=0;
    memcpy(existingRouter->address,router,6);
    list_add_tail(&existingRouter->list,&routers);
    mutex_unlock(&lock);
    return existingRouter;
}
static int Send(struct sk_buff*skb,struct Router*router){
    if(!router||!router->dev)return -ENODEV;
    skb->dev=router->dev;
    u8*dataLink=skb_mac_header(skb);
    memcpy(dataLink,router->address,6);
    memcpy(dataLink+6,router->dev->dev_addr,6);
    return dev_queue_xmit(skb);
}
UseRFC791Library
UseRFC8200Library
static bool IsLocal(u8*dataLink) {
    return (*dataLink&2);
}
static struct ReceiverPacket* ContinueReceiver(struct sk_buff*skb,struct net_device*dev,u8*router,u8*dataLink,u8*networklayer,u8*transportLayer,u8*sourceAddress,u8*destinationAddress,u16*sourcePort,u16*destinationPort){
    struct ReceiverPacket*packet=kmalloc(sizeof(struct ReceiverPacket),GFP_KERNEL);
    if(!packet)return NULL;
    packet->skb=skb;
    packet->dev=dev;
    packet->router=router;
    packet->dataLink=dataLink;
    packet->networkLayer=networklayer;
    packet->transportLayer=transportLayer;
    packet->sourceAddress=sourceAddress;
    packet->destinationAddress=destinationAddress;
    packet->sourcePort=sourcePort;
    packet->destinationPort=destinationPort;
    return packet;
}
static int ContinueReceiver2048(struct sk_buff*skb,struct net_device*dev,u8*router,u8*dataLink,u8*networklayer,u8*transportLayer,u8*sourceAddress,u8*destinationAddress,u16*sourcePort,u16*destinationPort){
    struct ReceiverPacket*packet=ContinueReceiver(skb,dev,router,dataLink,networklayer,transportLayer,sourceAddress,destinationAddress,sourcePort,destinationPort);
    if(packet){
        INIT_WORK(&packet->work, GetRFC791()->Continue);
        schedule_work(&packet->work);
    }
    return 0;
}
static int ContinueReceiver34527(struct sk_buff*skb,struct net_device*dev,u8*router,u8*dataLink,u8*networklayer,u8*transportLayer,u8*sourceAddress,u8*destinationAddress,u16*sourcePort,u16*destinationPort){
    struct ReceiverPacket*packet=ContinueReceiver(skb,dev,router,dataLink,networklayer,transportLayer,sourceAddress,destinationAddress,sourcePort,destinationPort);
    if(packet){
        INIT_WORK(&packet->work, GetRFC8200()->Continue);  
        schedule_work(&packet->work);
    }
    return 0;
}
static int Receiver(struct sk_buff*skb,struct net_device*dev){
    u8*dataLink=skb_mac_header(skb);
    u8*router=dataLink+6;
    if(IsLocal(dataLink)||IsLocal(router))return 0;
    u8*networkLayer=dataLink+14,*sourceAddress,*destinationAddress,*transportLayer;
    u16*sourcePort,*destinationPort;
    return ntohs(*(u16*)(dataLink+12))==2048?
        GetRFC791()->Receiver(networkLayer,&sourceAddress,&destinationAddress,&sourcePort,&destinationPort,&transportLayer)?
            ContinueReceiver2048(skb,dev,router,dataLink,networkLayer,transportLayer,sourceAddress,destinationAddress,sourcePort,destinationPort):1:
        GetRFC8200()->Receiver(networkLayer,&sourceAddress,&destinationAddress,&sourcePort,&destinationPort,&transportLayer)?
            ContinueReceiver34527(skb,dev,router,dataLink,networkLayer,transportLayer,sourceAddress,destinationAddress,sourcePort,destinationPort):1;
}
SystemSetup(MediaAccessControl, NULL, NULL,Bind(Receiver),Bind(Register),Bind(Find),Bind(Hookup),Bind(Unhook),Bind(Send));