#include "Router.h"
InitEthernetFrame
 
struct RouterHeader{
    u8 Address[6];
    struct net_device*Device;
    struct list_head List,Version4,Version6;
};
struct RouterBindVersion{
    struct RouterHeader*routerInfomation;
    struct list_head List;
};
static LIST_HEAD(RouterList);
static DEFINE_MUTEX(RouterMutex);
static struct RouterHeader*Get(struct Packet*packet) {
    struct IEEE8023Header*dataLinkLayer=GetEthernetFrame()->DataLinkLayer(packet);
    struct RouterHeader*routerHeader = NULL;
    list_for_each_entry(routerHeader, &RouterList, List) {
        if(memcmp(routerHeader->Address, dataLinkLayer->DestinationAddress, 6) == 0) {
            return routerHeader;
        }
    }
    mutex_lock(&RouterMutex);
    list_for_each_entry(routerHeader, &RouterList, List){
        if(memcmp(routerHeader->Address, dataLinkLayer->DestinationAddress,6)==0) {
            mutex_unlock(&RouterMutex);
            return routerHeader;
        }
    }
    routerHeader=kmalloc(sizeof(*routerHeader),GFP_KERNEL);
    if(!routerHeader) {
        mutex_unlock(&RouterMutex);
        return NULL;
    }
    memcpy(routerHeader->Address, dataLinkLayer->DestinationAddress, 6);
    routerHeader->Device=GetEthernetFrame()->PhysicalLayer(packet);
    dev_hold(routerHeader->Device);
    INIT_LIST_HEAD(&routerHeader->List);
    INIT_LIST_HEAD(&routerHeader->Version4);
    INIT_LIST_HEAD(&routerHeader->Version6);
    list_add(&routerHeader->List,&RouterList);
    mutex_unlock(&RouterMutex);
    return routerHeader;
}
static struct IEEE8023Header*CreateVersion4(u16 size,struct RouterHeader*routerHeader,struct Packet**packet) {
    struct IEEE8023Header*header=GetEthernetFrame()->CreateVersion4(size+34,routerHeader->Device,packet);
    if(!header)return NULL;
    memcpy(header->DestinationAddress, routerHeader->Address,6);
    return header;
}
static struct IEEE8023Header*CreateVersion6(u16 size,struct RouterHeader*routerHeader,struct Packet**packet) {
    struct IEEE8023Header*header=GetEthernetFrame()->CreateVersion6(size+54,routerHeader->Device,packet);
    if(!header)return NULL;
    memcpy(header->DestinationAddress, routerHeader->Address,6);
    return header;
}


End{}
Start(Router, Bind(Get)){}