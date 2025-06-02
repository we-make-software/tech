#include "../ServiceListener/ServiceListener.h"
InitNetworkAdapter
InitRouter
InitServiceListener
InitNetworkLayer

struct Packet{
    struct sk_buff*skb;
};
static struct net_device*PhysicalLayer(struct Packet*packet) {
    return!packet?NULL:packet->skb->dev;
}
static struct IEEE8023Header*DataLinkLayer(struct Packet*packet) {
    return!packet?NULL:(struct IEEE8023Header*)skb_mac_header(packet->skb);;
}
static bool IsVersion4(struct IEEE8023Header*header){
    return!header?false:ntohs(header->Type)==2048;
}
static bool IsGlobel(struct IEEE8023Header*header) {
    return!header?false:!(header->DestinationAddress[0]&4);
}
static void Receiver(struct Packet*packet){
    struct ServiceListenerHeader*serviceListenerHeader=GetServiceListener()->Get(packet);
    if(!serviceListenerHeader)return;
    struct RouterHeader*routerHeader=GetRouter()->Get(packet);
    if(!routerHeader)return;
    GetNetworkLayer()->Receiver(serviceListenerHeader, routerHeader, packet);
}
static struct IEEE8023Header*CreateVersion4(u16 size,struct net_device*dev,struct Packet**packet){
    u8*data=NULL;
    *packet=GetNetworkAdapter()->Create(size,dev,&data); 
    if(!*packet)return NULL;
    struct IEEE8023Header*header=(struct IEEE8023Header*)data;
    header->Type=htons(2048);
    (*packet)->skb->protocol=htons(ETH_P_IP);
    header->PayLoader[0]=69;
    return header;
}
static struct IEEE8023Header*CreateVersion6(u16 size,struct net_device*dev,struct Packet**packet) {
    u8*data=NULL;
    *packet=GetNetworkAdapter()->Create(size,dev,&data); 
    if(!*packet)return NULL;
    struct IEEE8023Header*header=(struct IEEE8023Header*)data;
    header->Type=htons(34525);
    (*packet)->skb->protocol=htons(ETH_P_IPV6);
    header->PayLoader[0]=96;
    return header;
}
static int Send(struct Packet*packet) {
    struct IEEE8023Header*dataLinkLayer=DataLinkLayer(packet);
    if(IsVersion4(dataLinkLayer)){
        //depend of UDP or TCP then we can set the other field like length, checksum.
    }else{
        //depend of UDP or TCP then we can set the other field like length.
    }
    return GetNetworkAdapter()->Send(packet);
}

End{}
Start(EthernetFrame,Bind(PhysicalLayer),Bind(DataLinkLayer),Bind(IsGlobel),Bind(IsVersion4),Bind(Receiver),Bind(CreateVersion4),Bind(CreateVersion6),Bind(Send)){}