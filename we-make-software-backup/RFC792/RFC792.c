#include "RFC792.h"
InitRFC791
InitNetworkAdapter
struct RFC792Pointer {
    u8 Type;
    u8 Code;
    u16 Checksum;
    union {
        struct {
            u16 Identifier,SequenceNumber;
            u8 Data[];
        } Echo;
    } Content;
}NoStructPadding;
struct Packet{
    struct IEEE802_3Pointer*IEEE802_3;
    struct RFC1122Pointer*RFC1122;
    struct RFC791Pointer*RFC791;
    struct RFC792Pointer*RFC792;
    struct RFC791NetworkAddress*Client;
    u8 Unused[sizeof(void*)];
    struct sk_buff*skb;
    struct work_struct work;
};
static struct Packet*CreateByIncoming(u16 size,struct Packet*incoming, struct RFC791NetworkAddress*server){
    struct Packet*outgoing=GetRFC791()->Create(size,server);
    if(!outgoing)return NULL;
    GetRFC791()->CloneIdentification(incoming, outgoing);
    return outgoing;
}
static void Send(struct work_struct*work) {
    struct Packet*packet=container_of(work,struct Packet,work);
    if(!packet)return;
    GetRFC791()->SetProtocol(packet,1);
    packet->RFC792->Checksum=0;
    packet->RFC792->Checksum=csum_fold(csum_partial((u8 *)packet->RFC792,GetRFC791()->GetTotalLength(packet),0));
    if(!GetRFC791()->Send(packet, packet->Client))
       GetNetworkAdapter()->Free(packet);
}
static void Receiver8(struct Packet*incoming, struct RFC791NetworkAddress*client, struct RFC791NetworkAddress*server) {
    u16 size=GetRFC791()->GetTotalLength(incoming);
    struct Packet*outgoing=CreateByIncoming(size, incoming, server);
    if(!outgoing)return;
    outgoing->RFC792->Type=0;
    outgoing->RFC792->Code=0;
    outgoing->RFC792->Content.Echo.Identifier=incoming->RFC792->Content.Echo.Identifier;
    outgoing->RFC792->Content.Echo.SequenceNumber=incoming->RFC792->Content.Echo.SequenceNumber;
    size-=8;
    if(size)
        memcpy(outgoing->RFC792->Content.Echo.Data, incoming->RFC792->Content.Echo.Data,size);
    outgoing->Client=client;
    INIT_WORK(&outgoing->work, Send);
    queue_work(system_wq,&outgoing->work);
}
static void Receiver(struct Packet*packet,struct RFC791NetworkAddress*client,struct RFC791NetworkAddress*server) {

    switch (packet->RFC792->Type)
    {
        case 8:
            Receiver8(packet, client, server);
            break;
        default:
            printk(KERN_WARNING "RFC792: Unsupported type %d\n", packet->RFC792->Type);
            break;
    }
}
End{}
Start(RFC792, Bind(Receiver)){}