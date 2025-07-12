#include "../Network/Network.h"
InitIEEE802_3
InitNetworkAdapter
InitRFC792
InitRFC9293
InitRFC768
Struct TransportLayerPointer{
    u16 SourcePort,DestinationPort;
};
Struct RFC791Pointer {
#if IsLittleEndian
    u8 HeaderLength:4,Version:4;
#else
    u8 Version:4,HeaderLength:4;
#endif
    u8 ExplicitCongestionNotificationAndDifferentiatedServicesCodePoint;
    u16 TotalLength,Identification;
    u16 Reserved;
    u8 TimeToLive,Protocol;
    u16 Checksum;
    u32 SourceAddress,DestinationAddress,Options[];
};
struct RFC791Server {
    struct RFC791NetworkAddress NetworkAddress;
    struct RFC1122Pointer*RFC1122;
};
struct RFC791Client {
    struct RFC791NetworkAddress NetworkAddress;
    struct NetworkLayer networkLayer;
    struct delayed_work work;
};
static struct NetworkLayer*GetNetworkLayer(struct NetworkAddress*address) {
    return!address||address->Type==6?NULL:&((struct RFC791Client*)address)->networkLayer;
}
static DEFINE_MUTEX(ServerMutex);
static DEFINE_MUTEX(ClientMutex);
static LIST_HEAD(ServerNetworkAddress);
static LIST_HEAD(ClientNetworkAddress);
static void Destory(struct work_struct *work) {
    struct RFC791Client *client = container_of(work, struct RFC791Client, work.work);
    if (!client) return;
    mutex_lock(&ClientMutex);
    list_del(&client->NetworkAddress.list);
    mutex_unlock(&ClientMutex);
    struct LayerDataPointer *data = NULL, *temp = NULL;
    list_for_each_entry_safe(data, temp, &client->networkLayer.data, data) {
        if (data->Destroy)
            data->Destroy((void *)client);
        list_del(&data->data);
        kfree(data);
    }
    kfree(client);
}

static struct list_head*GetServerNetworkAddress(void) {
    return &ServerNetworkAddress;
}
static struct RFC791NetworkAddress*AddServer(u32 Address,struct RFC1122Pointer*RFC1122){
    struct RFC791Server*server=NULL,*temp=NULL;
    list_for_each_entry(temp, &ServerNetworkAddress, NetworkAddress.list) {
        if(temp->NetworkAddress.Address==Address) {
            return(struct RFC791NetworkAddress*)temp;
        }
    }
    mutex_lock(&ServerMutex);
    temp=server=NULL;
    list_for_each_entry(temp, &ServerNetworkAddress, NetworkAddress.list) {
        if(temp->NetworkAddress.Address==Address) {
            mutex_unlock(&ServerMutex);
            return(struct RFC791NetworkAddress*)temp;
        }
    }
    server=kmalloc(sizeof(struct RFC791Server), GFP_KERNEL);
    if(!server) {
        mutex_unlock(&ServerMutex);
        return NULL;
    }
    server->NetworkAddress.Type=4;
    server->NetworkAddress.Address = Address;
    INIT_LIST_HEAD(&server->NetworkAddress.list);
    server->RFC1122=RFC1122;
    list_add_tail(&server->NetworkAddress.list, &ServerNetworkAddress);
    mutex_unlock(&ServerMutex);
    return (struct RFC791NetworkAddress*)server;
}
static struct RFC791NetworkAddress*AddOrGetClient(u32 Address){
    struct RFC791Client*client=NULL,*temp=NULL;
    list_for_each_entry(temp, &ClientNetworkAddress, NetworkAddress.list) {
        if(temp->NetworkAddress.Address==Address) {
            schedule_delayed_work(&temp->work,msecs_to_jiffies(900000));
            return &temp->NetworkAddress;
        }
    }
    mutex_lock(&ClientMutex);
    temp=client=NULL;
    list_for_each_entry(temp, &ClientNetworkAddress, NetworkAddress.list) {
        if(temp->NetworkAddress.Address==Address) {
            mutex_unlock(&ClientMutex);
            schedule_delayed_work(&temp->work,msecs_to_jiffies(900000));
            return &temp->NetworkAddress;
        }
    }
    client=kmalloc(sizeof(struct RFC791Client), GFP_KERNEL);
    if(!client) {
        mutex_unlock(&ClientMutex);
        return NULL;
    }
    client->NetworkAddress.Type=4;
    client->NetworkAddress.Address=Address;
    INIT_LIST_HEAD(&client->networkLayer.data);
    mutex_init(&client->networkLayer.lock);
    INIT_LIST_HEAD(&client->NetworkAddress.list);
    list_add_tail(&client->NetworkAddress.list, &ClientNetworkAddress);
    INIT_DELAYED_WORK(&client->work, Destory);
    schedule_delayed_work(&client->work, msecs_to_jiffies(900000));
    mutex_unlock(&ClientMutex);
    return &client->NetworkAddress; 
}

struct Packet {
    struct IEEE802_3Pointer*IEEE802_3;
    struct RFC1122Pointer*RFC1122;
    struct RFC791Pointer*RFC791;
    u8*Payload;
    u8 Unused[sizeof(void*)*2];
    struct sk_buff*skb;
};
static void SetProtocol(struct Packet*packet, u8 protocol) {
    packet->RFC791->Protocol=protocol;
}
static u16 GetTotalLength(struct Packet*packet) {
    if(!packet)return 0;
    return ntohs(packet->RFC791->TotalLength)-20;
}

static void CloneIdentification(struct Packet*incoming,struct Packet*outgoing){
    outgoing->RFC791->Identification=incoming->RFC791->Identification;
}
static void SetIdentification(struct Packet*outgoing,u16 value){
    outgoing->RFC791->Identification=value;
}
static bool Receiver(struct Packet*packet){
    u32 nDestinationAddress=ntohl(packet->RFC791->DestinationAddress);
    if((nDestinationAddress>=0&&nDestinationAddress<=16777215)||(nDestinationAddress>=167772160&&nDestinationAddress<=184549375)||(nDestinationAddress>=2130706432&&nDestinationAddress<=2147483647)||(nDestinationAddress>=2886729728&&nDestinationAddress<=2887778303)||(nDestinationAddress>=3232235520&&nDestinationAddress<=3232301055)||(nDestinationAddress>=3758096384&&nDestinationAddress<=4026531839)||(nDestinationAddress>=4278190080&&nDestinationAddress<=4294967295))return false;
    packet->Payload=(u8*)packet->RFC791+20;
    return!(packet->RFC791->Protocol==6&&ntohs(((struct TransportLayerPointer*)packet->Payload)->DestinationPort)==22);
}
static void Continue(struct Packet*packet){
    struct RFC791NetworkAddress*server=AddServer(packet->RFC791->DestinationAddress,packet->RFC1122);
    if(!server)return;
    struct RFC791NetworkAddress*client=AddOrGetClient(packet->RFC791->SourceAddress);
    if(!client
        
        //||!GetNetworkAdapter()->Trust(&client->networkLayer)
    
    )return;
    switch (packet->RFC791->Protocol)
    {
        case 1:
            GetRFC792()->Receiver(packet,client,server);
            break;
        case 6:
            //GetRFC9293()->RFC791Receiver(packet,client,server);
            break;
        case 17: 
            //GetRFC768()->RFC791Receiver(packet,client,server);
            break;
        default:
            printk(KERN_WARNING "RFC791: Unsupported protocol %d\n", packet->RFC791->Protocol);
            break;
    }
    //print the ID
    if(packet->RFC791->Identification)
        printk(KERN_INFO "RFC791: Identification = %u", ntohs(packet->RFC791->Identification));
    else
        printk(KERN_INFO "RFC791: Identification = 0 (not set)");
}

static bool Send(struct Packet*packet,struct RFC791NetworkAddress*client){
    if(!packet||!client)return false;
    packet->RFC791->DestinationAddress=client->Address;
    struct Checksum checksums[2] = {
        { .Data = (u16*)&packet->RFC791, .Length = 5},
        { .Data = (u16*)&packet->RFC791->SourceAddress, .Length = 4 }
    };
    //packet->RFC791->Checksum = GetNetworkAdapter()->ChecksumCalculator(checksums, 2);
    return GetNetworkAdapter()->Send(packet);
}
static struct Packet*Create(u16 size,struct RFC791NetworkAddress*server){
    if(!server)return NULL;
    struct RFC791Server*rFC791Server=container_of(server,struct RFC791Server,NetworkAddress);
    struct Packet*packet=GetIEEE802_3()->Create(size+20,rFC791Server->RFC1122);
    if(!packet)return NULL;
    packet->Payload=(u8*)packet->RFC791+20;
    packet->RFC791->HeaderLength=5;
    packet->RFC791->Version=4;
    packet->RFC791->TotalLength=htons(size+20);
    packet->RFC791->SourceAddress=server->Address;
    packet->RFC791->TimeToLive=64;
    GetIEEE802_3()->SetType(packet,2048);
    packet->RFC791->Reserved=0;
    packet->RFC791->ExplicitCongestionNotificationAndDifferentiatedServicesCodePoint=0;
    return packet;
}
End{
    struct RFC791Client*rFC791Client=NULL,*rFC791Clienttemp=NULL;  
    list_for_each_entry_safe(rFC791Client,rFC791Clienttemp,&ClientNetworkAddress,NetworkAddress.list) {
        list_del(&rFC791Client->NetworkAddress.list);
        cancel_delayed_work_sync(&rFC791Client->work);
        struct LayerDataPointer*data=NULL,*temp=NULL;
        list_for_each_entry_safe(data,temp,&rFC791Client->networkLayer.data,data) {
            if(data->Destroy)data->Destroy((struct NetworkAddress*)rFC791Client);
            list_del(&data->data);
            kfree(data);
        }
        kfree(rFC791Client);
        rFC791Client=NULL;
    }
    struct RFC791Server*rFC791Server=NULL,*rFC791Servertemp=NULL;
    list_for_each_entry_safe(rFC791Server,rFC791Servertemp,&ServerNetworkAddress,NetworkAddress.list) {
        list_del(&rFC791Server->NetworkAddress.list);
        kfree(rFC791Server);
        rFC791Server=NULL;
    }
};
Start(RFC791,
    Bind(Receiver),
    Bind(Continue),
    Bind(Create),
    Bind(Send),
    Bind(GetTotalLength),
    Bind(SetProtocol),
    Bind(CloneIdentification),
    Bind(SetIdentification),
    Bind(GetNetworkLayer)){}