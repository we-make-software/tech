#include "../RFC4443/RFC4443.h"
InitIEEE802_3
InitNetworkAdapter
InitRFC9293
InitRFC768
InitRFC4443


struct TransportLayerPointer{
    u16 SourcePort,DestinationPort;
}__attribute__((packed));
struct NoPadding RFC8200Pointer{
#if IsLittleEndian
    u32 FlowLabel:20,ExplicitCongestionNotificationAndDifferentiatedServicesCodePoint:8,Version:4;
#else
    u32 Version:4,DifferentiatedServicesCodePointAndExplicitCongestionNotification:8,FlowLabel:20;
#endif
    u16 PayloadLength;
    u8 NextHeader,HopLimit;
    u64 SourceAddressHigh,SourceAddressLow,DestinationAddressHigh,DestinationAddressLow;
};
struct RFC8200NetworkAddress {
    u8 Type;
    u64 AddressHigh,AddressLow;
    struct list_head list;
};
struct RFC8200Server {
    struct RFC8200NetworkAddress NetworkAddress;
    struct RFC1122Pointer*RFC1122;
};
struct RFC8200Client {
    struct RFC8200NetworkAddress NetworkAddress;
    struct NetworkLayer networkLayer;
    struct delayed_work work;
};
static struct NetworkLayer*GetNetworkLayer(struct NetworkAddress*address) {
    return!address||address->Type==4?NULL:&((struct RFC8200Client*)address)->networkLayer;
}
static DEFINE_MUTEX(ServerMutex);
static DEFINE_MUTEX(ClientMutex);
static LIST_HEAD(ServerNetworkAddress);
static LIST_HEAD(ClientNetworkAddress);
static struct list_head*GetServerNetworkAddress(void) {
    return &ServerNetworkAddress;
}
static struct RFC8200NetworkAddress*AddServer(u64 AddressHigh, u64 AddressLow,struct RFC1122Pointer*RFC1122){
    struct RFC8200Server*server=NULL,*temp=NULL;
    list_for_each_entry(temp, &ServerNetworkAddress, NetworkAddress.list) {
        if(temp->NetworkAddress.AddressHigh==AddressHigh&&temp->NetworkAddress.AddressLow==AddressLow) {
            return &temp->NetworkAddress;
        }
    }
    mutex_lock(&ServerMutex);
    temp=server=NULL;
    list_for_each_entry(temp, &ServerNetworkAddress, NetworkAddress.list) {
        if(temp->NetworkAddress.AddressHigh==AddressHigh&&temp->NetworkAddress.AddressLow==AddressLow) {
            mutex_unlock(&ServerMutex);
            return &temp->NetworkAddress;
        }
    }
    server=kmalloc(sizeof(struct RFC8200Server), GFP_KERNEL);
    if(!server) {
        mutex_unlock(&ServerMutex);
        return NULL;
    }
    server->NetworkAddress.Type=6;
    server->NetworkAddress.AddressHigh=AddressHigh;
    server->NetworkAddress.AddressLow=AddressLow;
    server->RFC1122=RFC1122;
    INIT_LIST_HEAD(&server->NetworkAddress.list);
    list_add_tail(&server->NetworkAddress.list, &ServerNetworkAddress);
    mutex_unlock(&ServerMutex);
    return &server->NetworkAddress;
}
static void Destroy(struct work_struct*work) {
    struct RFC8200Client*client=container_of(work,struct RFC8200Client,work.work);
    if(!client)return;
    mutex_lock(&ClientMutex);
    list_del(&client->NetworkAddress.list);
    mutex_unlock(&ClientMutex);
    struct ClientDataPointer*data=NULL,*temp=NULL;
    list_for_each_entry(temp, &client->data, list) {
        data=temp;
        if(data->Destroy)data->Destroy(&client->NetworkAddress);
        list_del(&data->list);
        kfree(data);
    }
    kfree(client);
}
static struct RFC8200NetworkAddress*AddOrGetClient(u64 AddressHigh, u64 AddressLow) {
    struct RFC8200Client*client=NULL,*temp=NULL;
    list_for_each_entry(temp, &ClientNetworkAddress, NetworkAddress.list) {
        if(temp->NetworkAddress.AddressHigh==AddressHigh&&temp->NetworkAddress.AddressLow==AddressLow) {
            schedule_delayed_work(&temp->work, msecs_to_jiffies(900000));   
            return &temp->NetworkAddress;
        }
    }
    mutex_lock(&ClientMutex);
    temp=client=NULL;
    list_for_each_entry(temp, &ClientNetworkAddress, NetworkAddress.list) {
        if(temp->NetworkAddress.AddressHigh==AddressHigh&&temp->NetworkAddress.AddressLow==AddressLow) {
            mutex_unlock(&ClientMutex);
            schedule_delayed_work(&temp->work, msecs_to_jiffies(900000));
            return &temp->NetworkAddress;
        }
    }
    client=kmalloc(sizeof(struct RFC8200Client), GFP_KERNEL);
    if(!client) {
        mutex_unlock(&ClientMutex);
        return NULL;
    }
    client->NetworkAddress.Type=6;
    client->NetworkAddress.AddressHigh = AddressHigh;
    client->NetworkAddress.AddressLow = AddressLow;
    INIT_LIST_HEAD(&client->data);
    INIT_LIST_HEAD(&client->NetworkAddress.list);
    list_add_tail(&client->NetworkAddress.list, &ClientNetworkAddress);
    INIT_DELAYED_WORK(&client->work, Destroy);
    schedule_delayed_work(&client->work, msecs_to_jiffies(900000));
    mutex_unlock(&ClientMutex);
    return &client->NetworkAddress;
}
struct Packet {
    struct IEEE802_3Pointer*IEEE802_3;
    struct RFC1122Pointer*RFC1122;
    struct RFC8200Pointer*RFC8200;
    u8*Payload;
    u8 Unused[sizeof(void*)*2];
    struct sk_buff*skb;
};
static u16 GetTotalLength(struct Packet*packet) {
    if(!packet)return 0;
    return ntohs(packet->RFC8200->PayloadLength);
}
static void SetFlowLabel(struct Packet*packet, u32 flowLabel) {
    packet->RFC8200->FlowLabel = flowLabel;
}
static void CloneFlowLabel(struct Packet*incoming,struct Packet*outgoing) {
    if(!incoming||!outgoing)return;
    outgoing->RFC8200->FlowLabel=incoming->RFC8200->FlowLabel;
}
static void SetNextHeader(struct Packet*packet, u8 nextHeader) {
    packet->RFC8200->NextHeader = nextHeader;
}
static bool Receiver(struct Packet*packet) {
    u64 nDestinationAddressHigh=be64_to_cpu(packet->RFC8200->DestinationAddressHigh);
    u64 nDestinationAddressLow=packet->RFC8200->DestinationAddressLow;
    u8 nDestinationAddressFirst=(u8)(nDestinationAddressHigh>>56);
    if((nDestinationAddressHigh==0&&(nDestinationAddressLow==0||nDestinationAddressLow==1))||(nDestinationAddressFirst==255)||(nDestinationAddressFirst==254&&(u8)((nDestinationAddressHigh>>54)&3)==2))return false;
    packet->Payload=(u8*)packet->RFC8200+40;
    return!(packet->RFC8200->NextHeader==6&&ntohs(((struct TransportLayerPointer*)packet->Payload)->DestinationPort)==22);
}
static struct Packet*Create(u16 size, struct RFC8200NetworkAddress*client,struct RFC8200NetworkAddress*server) {
    if(!server||!server->AddressHigh||!server->AddressLow)return NULL;
    struct RFC8200Server *rFC8200Server=container_of(server, struct RFC8200Server, NetworkAddress);
    struct Packet*packet=GetIEEE802_3()->Create(size+40, rFC8200Server->RFC1122);
    if(!packet)return NULL;
    packet->RFC8200->SourceAddressHigh=server->AddressHigh;
    packet->RFC8200->SourceAddressLow=server->AddressLow;
    packet->RFC8200->DestinationAddressHigh=client->AddressHigh;
    packet->RFC8200->DestinationAddressLow=client->AddressLow;
    packet->RFC8200->HopLimit=64;
    packet->RFC8200->Version=6;
    GetIEEE802_3()->SetType(packet, 34525);
    packet->RFC8200->PayloadLength=htons(size);
    packet->Payload=(u8*)packet->RFC8200+40;
    SetFlowLabel(packet, 0);
    packet->RFC8200->ExplicitCongestionNotificationAndDifferentiatedServicesCodePoint=0;
    return packet;
}
static void Continue(struct Packet*packet) {
    struct RFC8200NetworkAddress*server=AddServer(packet->RFC8200->DestinationAddressHigh,packet->RFC8200->DestinationAddressLow,packet->RFC1122);
    if(!server)return;
    struct RFC8200NetworkAddress*client=AddOrGetClient(packet->RFC8200->SourceAddressHigh, packet->RFC8200->SourceAddressLow);
    if(!client||!GetNetworkAdapter()->Trust(&client->networkLayer))return;
    switch (packet->RFC8200->NextHeader) {
        case 6:
            // GetRFC9293()->RFC8200Receiver(packet, client, server);
            break;
        case 17: 
            // GetRFC768()->RFC8200Receiver(packet, client, server);
            break;
        case 58:
            GetRFC4443()->Receiver(packet, client, server);
            break;
        default:
            printk(KERN_WARNING "RFC8200: Unsupported protocol %d\n", packet->RFC8200->NextHeader);
            break;
    }
}
End{
    struct RFC8200Client*rFC8200Client=NULL,*rFC8200Clienttemp=NULL;
    list_for_each_entry_safe(rFC8200Client, rFC8200Clienttemp, &ClientNetworkAddress, NetworkAddress.list) {
        list_del(&rFC8200Client->NetworkAddress.list);
        cancel_delayed_work_sync(&rFC8200Client->work);
        struct LayerDataPointer*data=NULL,*temp=NULL;
        list_for_each_entry_safe(data, temp, &rFC8200Client->data, list) {
            if(data->Destroy)data->Destroy((struct NetworkAddress*)rFC8200Client);
            list_del(&data->data);
            kfree(data);
        }
        kfree(rFC8200Client);
    }
    struct RFC8200Server*rFC8200Server=NULL,*rFC8200Servertemp=NULL;
    list_for_each_entry_safe(rFC8200Server, rFC8200Servertemp, &ServerNetworkAddress, NetworkAddress.list) {
        list_del(&rFC8200Server->NetworkAddress.list);
        kfree(rFC8200Server);
    }
};
Start(RFC8200, 
    Bind(Receiver), 
    Bind(Continue),
    Bind(Create),
    Bind(SetNextHeader),
    Bind(GetTotalLength),
    Bind(CloneFlowLabel),
    Bind(SetFlowLabel),
    Bind(GetNetworkLayer)){}