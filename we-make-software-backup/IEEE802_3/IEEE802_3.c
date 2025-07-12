#include "../RFC8200/RFC8200.h"
InitNetworkAdapter
InitRFC1122
InitRFC791
InitRFC8200

struct RFC1122Pointer {
    u8 Address[6];
    struct net_device*dev;
};
struct IEEE802_3Pointer {
    u8 Destination[6];
    u8 Source[6];
    u16 Type;
} NoStructPadding;
struct Packet {
    struct IEEE802_3Pointer*IEEE802_3;
    struct RFC1122Pointer*RFC1122;
    u8*Payload;
    u8 Unused[sizeof(void*)*3];
    struct sk_buff*skb;
};
static u16 GetType(struct Packet*packet) {
    return(!packet)?0:ntohs(((struct IEEE802_3Pointer*)packet->IEEE802_3)->Type);
}
static void SetType(struct Packet*packet,u16 type){
    if(!packet) return;
    packet->skb->protocol=htons(type==2048?ETH_P_IP:ETH_P_IPV6);
    ((struct IEEE802_3Pointer*)packet->IEEE802_3)->Type=htons(type);
}
static bool Receiver(struct Packet*packet){
    packet->RFC1122=GetRFC1122()->Register(packet);
    if(!packet->RFC1122)return false;
    packet->Payload=(u8*)packet->IEEE802_3+14;
    if(GetType(packet)==2048)
        return GetRFC791()->Receiver(packet);
    else if(GetType(packet)==34525)
        return GetRFC8200()->Receiver(packet);
    return false;
}
static void Continue(struct Packet*packet) {
    if(GetType(packet)==2048)
        GetRFC791()->Continue(packet);
    else
        GetRFC8200()->Continue(packet);
}
static struct Packet*Create(u16 size,struct RFC1122Pointer*rFC1122Pointer) {
    if(!rFC1122Pointer||!rFC1122Pointer->dev)return NULL;
    struct Packet*packet=GetNetworkAdapter()->Create(size+14,rFC1122Pointer->dev);
    if(!packet)return NULL;
    packet->RFC1122=rFC1122Pointer;
    memcpy(packet->IEEE802_3->Destination,rFC1122Pointer->Address,6);
    packet->Payload=(u8*)packet->IEEE802_3+14;
    return packet;
}
End{};
Start(IEEE802_3,Bind(Receiver),Bind(Continue),Bind(Create),Bind(SetType)){}