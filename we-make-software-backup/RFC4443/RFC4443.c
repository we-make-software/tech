#include "RFC4443.h"
InitNetworkAdapter
InitRFC8200

struct NoPadding RFC8200Pointer{
#if IsLittleEndian
    u32 FlowLabel:20,ExplicitCongestionNotification:2,DifferentiatedServicesCodePoint:6,Version:4;
#else
    u32 Version:4,DifferentiatedServicesCodePoint:6,ExplicitCongestionNotification:2,FlowLabel:20;
#endif
    u16 PayloadLength;
    u8 NextHeader,HopLimit;
    u64 SourceAddressHigh,SourceAddressLow,DestinationAddressHigh,DestinationAddressLow;
};
struct NoPadding RFC4443Pointer {
    u8 Type;
    u8 Code;
    u16 Checksum;
    union {
        struct {
            u16 Identifier;
            u16 SequenceNumber;
            u8 Data[];
        } Echo;
    } Content;
};
struct Packet{
    struct IEEE802_3Pointer*IEEE802_3;
    struct RFC1122Pointer*RFC1122;
    struct RFC8200Pointer*RFC8200;
    struct RFC4443Pointer*RFC4443;
    struct RFC8200NetworkAddress*Client;
    u8 Unused[sizeof(void*)];
    struct sk_buff*skb;
    struct work_struct work;
};
static struct Packet* CreateByIncoming(u16 size, struct Packet* incoming,struct RFC8200NetworkAddress*client,struct RFC8200NetworkAddress* server) {
    struct Packet* outgoing = GetRFC8200()->Create(size, client, server);
    if(!outgoing)return NULL;
    GetRFC8200()->SetNextHeader(outgoing, 58);
    return outgoing;
}
static void Send(struct work_struct* work) {
    struct Packet* packet = container_of(work, struct Packet, work);
    if(!packet)return;
    packet->RFC4443->Checksum = 0;
    struct in6_addr saddr;
    u64 temp_s_high=cpu_to_be64(packet->RFC8200->SourceAddressHigh);
    memcpy(&saddr.s6_addr[0],&temp_s_high,sizeof(u64));
    u64 temp_s_low=cpu_to_be64(packet->RFC8200->SourceAddressLow);
    memcpy(&saddr.s6_addr[8],&temp_s_low,sizeof(u64));
    struct in6_addr daddr;
    u64 temp_d_high=cpu_to_be64(packet->RFC8200->DestinationAddressHigh);
    memcpy(&daddr.s6_addr[0],&temp_d_high,sizeof(u64));
    u64 temp_d_low=cpu_to_be64(packet->RFC8200->DestinationAddressLow);
    memcpy(&daddr.s6_addr[8],&temp_d_low,sizeof(u64));
    u16 len=GetRFC8200()->GetTotalLength(packet);
    packet->RFC4443->Checksum=csum_ipv6_magic(&saddr,&daddr,len,IPPROTO_ICMPV6,csum_partial((u8*)packet->RFC4443,len,0));
    if(!GetNetworkAdapter()->Send(packet)){
        GetNetworkAdapter()->Free(packet);
    }
}
static void Receiver128(struct Packet* incoming, struct RFC8200NetworkAddress* client,struct RFC8200NetworkAddress*server){
    struct Packet*outgoing = CreateByIncoming(GetRFC8200()->GetTotalLength(incoming), incoming, client, server);
    if(!outgoing)return;
    outgoing->RFC4443->Type=129;
    outgoing->RFC4443->Code=0;
    outgoing->RFC4443->Content.Echo.Identifier = incoming->RFC4443->Content.Echo.Identifier;
    outgoing->RFC4443->Content.Echo.SequenceNumber = incoming->RFC4443->Content.Echo.SequenceNumber;
    u16 size = GetRFC8200()->GetTotalLength(incoming) - 8;
    if(size)
        memcpy(outgoing->RFC4443->Content.Echo.Data, incoming->RFC4443->Content.Echo.Data, size);
    outgoing->Client = client;
    INIT_WORK(&outgoing->work, Send);
    queue_work(system_wq, &outgoing->work);
}
static void Receiver(struct Packet*packet, struct RFC8200NetworkAddress*client, struct RFC8200NetworkAddress*server){
    switch (packet->RFC4443->Type)
    {
        case 128:
            Receiver128(packet,client,server);
            break;
        default:
            printk(KERN_WARNING "RFC4443: Unsupported type %d\n", packet->RFC4443->Type);
            break;
    }
}
End{}
Start(RFC4443, Bind(Receiver)){}