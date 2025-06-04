#include "../ServiceListener/ServiceListener.h"
InitEthernetFrame
InitRouter


static LIST_HEAD(Version4);
static LIST_HEAD(Version6);
static struct list_head*GetServerVersion4(void){
    return &Version4;
}
static struct list_head*GetServerVersion6(void){
    return &Version6;
}
struct Pointer8{
    u8 value;
    u8 index;
    struct list_head data;
    struct delayed_work work;
    struct mutex lock;
    struct Pointer8*prev;
    struct list_head list,odd_list,even_list;
    struct mutex odd_mutex,even_mutex;
};
struct Pointer16{
    u16 Value;
    u8 index;
    struct list_head data;
    struct delayed_work work;
    struct mutex lock;
    struct Pointer16*prev;
    struct list_head list,odd_list,even_list;
    struct mutex odd_mutex,even_mutex;
};
static LIST_HEAD(Pointer8_odd_list);
static LIST_HEAD(Pointer8_even_list);
static LIST_HEAD(Pointer16_odd_list);
static LIST_HEAD(Pointer16_even_list);
static DEFINE_MUTEX(Pointer8_odd_mutex);
static DEFINE_MUTEX(Pointer8_even_mutex);
static DEFINE_MUTEX(Pointer16_odd_mutex);
static DEFINE_MUTEX(Pointer16_even_mutex);
static void DeletePointer8(struct Pointer8*pointer8){
    if(!pointer8||!list_empty(&pointer8->odd_list)||!list_empty(&pointer8->even_list)||!list_empty(&pointer8->data))return;
    list_del(&pointer8->list);
    DeletePointer8(pointer8->prev);
    kfree(pointer8);
}
static void DeletePointer16(struct Pointer16*pointer16){
    if(!pointer16||!list_empty(&pointer16->odd_list)||!list_empty(&pointer16->even_list)||!list_empty(&pointer16->data))return;
    list_del(&pointer16->list);
    DeletePointer16(pointer16->prev);
    kfree(pointer16);
}

static void AutomatikDeleteNetworkAddress(struct work_struct *work){
    struct NetworkAddress*networkAddress=container_of(work,struct NetworkAddress,work.work);
    struct NetworkDataHeader*networkDataHeader=NULL,*tmp_networkDataHeader=NULL;
    list_for_each_entry_safe(networkDataHeader, tmp_networkDataHeader, &networkAddress->data, data) {
        if(networkDataHeader->Destroy){
            networkDataHeader->Destroy(networkAddress,networkDataHeader->ID);
        }
        list_del(&networkDataHeader->data);
        kfree(networkDataHeader);
    }
    if(networkAddress->index==3){
        struct Pointer8*pointer8=(struct Pointer8*)networkAddress;
        DeletePointer8(pointer8);
    }else{
        struct Pointer16*pointer16=(struct Pointer16*)networkAddress;
        DeletePointer16(pointer16);
    }
}
static void SetExpiryNetworkAddress(struct NetworkAddress*networkAddress){
    schedule_delayed_work(&networkAddress->work, msecs_to_jiffies(600000));
}
static struct Pointer8*FindPointer8(u8 value,struct list_head*odd_list,struct list_head*even_list){
    struct Pointer8*pointer8=NULL,*tmp_pointer8=NULL;
    if(value>127){
        list_for_each_entry_safe_reverse(pointer8, tmp_pointer8, value&1?odd_list:even_list, list) {
            if(pointer8->value==value){
                return pointer8;
            }
        }
    }else{
        list_for_each_entry_safe(pointer8, tmp_pointer8, value&1?odd_list:even_list,list) {
            if(pointer8->value==value){
                return pointer8;
            }
        }
    }
    return NULL;
};
static struct Pointer16*FindPointer16(u16 value,struct list_head*odd_list,struct list_head*even_list){
    struct Pointer16*pointer16=NULL,*tmp_pointer16=NULL;
    if(value>32767){
        list_for_each_entry_safe_reverse(pointer16, tmp_pointer16, value&1?odd_list:even_list, list) {
            if(pointer16->Value==value)
                return pointer16;
            if(pointer16->Value<value)
                return NULL;
        }
        return NULL;
    }else{
        list_for_each_entry_safe(pointer16, tmp_pointer16, value&1?odd_list:even_list,list) {
            if(pointer16->Value==value)
                return pointer16;
            if(pointer16->Value>value)
                return NULL;
        }
        return NULL;
    }
};
static struct Pointer8*CreatePointer8(struct Pointer8* prev,u8 value,struct list_head*odd_list,struct list_head*even_list){
    struct Pointer8*pointer8=kmalloc(sizeof(struct Pointer8),GFP_KERNEL);
    if(!pointer8){
        DeletePointer8(prev);
        return NULL;
    }
    pointer8->value=value;
    if(prev)
        pointer8->index=prev->index+1;
    else
        pointer8->index=0;
    pointer8->prev=prev;
    INIT_LIST_HEAD(&pointer8->list);
    INIT_LIST_HEAD(&pointer8->odd_list);
    INIT_LIST_HEAD(&pointer8->even_list);
    INIT_LIST_HEAD(&pointer8->data);
    mutex_init(&pointer8->lock);
    mutex_init(&pointer8->work.lock);
    mutex_init(&pointer8->odd_mutex);
    mutex_init(&pointer8->even_mutex);
    INIT_DELAYED_WORK(&pointer8->work, AutomaticDeleteNetworkAddress);
    if(list_empty(value&1?odd_list:even_list))
        list_add(&pointer8->list, value&1?odd_list:even_list);
    else{
        struct Pointer8*nearby,*tmp_pointer8=NULL;
        if(value>127){
           list_for_each_entry_safe_reverse(nearby, tmp_pointer8, value&1?odd_list:even_list, list) {
                if(nearby->value<value){
                    list_add_tail(&pointer8->list, &nearby->list);
                    return pointer8;
                }
            }
            list_add_tail(&pointer8->list, value&1?odd_list:even_list); 
        }else{
            list_for_each_entry_safe(nearby, tmp_pointer8, value&1?odd_list:even_list,list) {
                if(nearby->value>value){
                    list_add(&pointer8->list, &nearby->list);
                    return pointer8;
                }
            }
            list_add(&pointer8->list, value&1?odd_list:even_list);
        }
    }
    return pointer8;
}
static struct Pointer16*CreatePointer16(struct Pointer16* prev,u16 value,struct list_head*odd_list,struct list_head*even_list){
    struct Pointer16*pointer16=kmalloc(sizeof(struct Pointer16),GFP_KERNEL);
    if(!pointer16){
        DeletePointer16(prev);
        return NULL;
    }
    pointer16->Value=value;
    if(prev)
        pointer16->index=prev->index+1;
    else
        pointer16->index=0;
    pointer16->prev=prev;
    INIT_LIST_HEAD(&pointer16->list);
    INIT_LIST_HEAD(&pointer16->odd_list);
    INIT_LIST_HEAD(&pointer16->even_list);
    INIT_LIST_HEAD(&pointer16->data);
    mutex_init(&pointer16->odd_mutex);
    mutex_init(&pointer16->even_mutex);
    INIT_DELAYED_WORK(&pointer16->work,AutomaticDeleteNetworkAddress);
    if(list_empty(value&1?odd_list:even_list))
        list_add(&pointer16->list, value&1?odd_list:even_list);
    else{
        struct Pointer16*nearby,*tmp_pointer8=NULL;
        if(value>32767){
           list_for_each_entry_safe_reverse(nearby, tmp_pointer8, value&1?odd_list:even_list, list) {
                if(nearby->Value<value){
                    list_add_tail(&pointer16->list, &nearby->list);
                    return pointer16;
                }
            }
            list_add_tail(&pointer16->list, value&1?odd_list:even_list); 
        }else{
            list_for_each_entry_safe(nearby, tmp_pointer8, value&1?odd_list:even_list,list) {
                if(nearby->Value>value){
                    list_add(&pointer16->list, &nearby->list);
                    return pointer16;
                }
            }
            list_add(&pointer16->list, value&1?odd_list:even_list);
        }
    }
    return pointer16;
}
static struct Pointer8*GetPointer8(u8*value){
    struct list_head*odd_list=&Pointer8_odd_list,*even_list=&Pointer8_even_list;
    struct mutex*odd_mutex=&Pointer8_odd_mutex,*even_mutex=&Pointer8_even_mutex;
    struct Pointer8*pointer8=NULL;
    for(u8 i=0;i<4;i++){
        pointer8=FindPointer8(value[i], odd_list, even_list);
        if(pointer8){
            if(i==3)
                return pointer8;
            goto SetPointer;   
        }
        mutex_lock(value[i]&1?odd_mutex:even_mutex);
        pointer8=FindPointer8(value[i], odd_list, even_list);
        if(pointer8){
            mutex_unlock(value[i]&1?odd_mutex:even_mutex);
            if(i==3)
                return pointer8;
            goto SetPointer;   
        }
        pointer8=CreatePointer8(pointer8, value[i], odd_list, even_list);
        if(!pointer8){
            mutex_unlock(value[i]&1?odd_mutex:even_mutex);
            return NULL;
        }
        mutex_unlock(value[i]&1?odd_mutex:even_mutex);
        if(i==3)
            return pointer8;
        SetPointer:
        odd_list=&pointer8->odd_list;
        even_list=&pointer8->even_list;
        odd_mutex=&pointer8->odd_mutex;
        even_mutex=&pointer8->even_mutex;
    }
    return NULL;
}
static struct Pointer16*GetPointer16(u16*value) {
    struct list_head*odd_list=&Pointer16_odd_list,*even_list=&Pointer16_even_list;
    struct mutex*odd_mutex=&Pointer16_odd_mutex,*even_mutex=&Pointer16_even_mutex;
    struct Pointer16*pointer16=NULL;
    for(u8 i=0;i<8;i++){
        pointer16=FindPointer16(value[i], odd_list, even_list);
        if(pointer16){
            if(i==7)
                return pointer16;
            goto SetPointer; 
        }
        mutex_lock(value[i]&1?odd_mutex:even_mutex);
        pointer16=FindPointer16(value[i], odd_list, even_list);
        if(pointer16){
            mutex_unlock(value[i]&1?odd_mutex:even_mutex);
            if(i==7)
                return pointer16;
            goto SetPointer; 
        }
        pointer16=CreatePointer16(pointer16, value[i], odd_list, even_list);
        if(!pointer16){
            mutex_unlock(value[i]&1?odd_mutex:even_mutex);
            return NULL;
        }
        mutex_unlock(value[i]&1?odd_mutex:even_mutex);
        if(i==7)
            return pointer16;
        SetPointer:
        odd_list=&pointer16->odd_list;
        even_list=&pointer16->even_list;
        odd_mutex=&pointer16->odd_mutex;
        even_mutex=&pointer16->even_mutex;
    }
    return NULL;
}
static struct NetworkAddress*GetVersion4Address(u8*value){
    struct Pointer8*pointer8=GetPointer8(value);
    if(!pointer8)return NULL;
    return (struct NetworkAddress*)pointer8;
}
static struct NetworkAddress*GetVersion6Address(u16*value){
    struct Pointer16*pointer16=GetPointer16(value);
    if(!pointer16)return NULL;
    return (struct NetworkAddress*)pointer16;
}
static enum NetworkLayerNextHeader NextHeader(struct IEEE8023Header*header){
    return !header?0:header->PayLoader[GetEthernetFrame()->IsVersion4(header)?9:6];
}
static bool IsPublic(struct IEEE8023Header*header){
    if(!header)return false;
    if(GetEthernetFrame()->IsVersion4(header)){
        u8*skb_DestinationAddress=header->PayLoader+12,*skb_SourceAddress=header->PayLoader+16;
       return!(
            (skb_SourceAddress[0]==10||skb_DestinationAddress[0]==10)||
            ((skb_SourceAddress[0]==172&&skb_SourceAddress[1]>=16&&skb_SourceAddress[1]<=31)||
            (skb_DestinationAddress[0]==172&&skb_DestinationAddress[1]>=16&&skb_DestinationAddress[1]<=31))||
            ((skb_SourceAddress[0]==192&&skb_SourceAddress[1]==168)||
            (skb_DestinationAddress[0]==192&&skb_DestinationAddress[1]==168))||
            (skb_SourceAddress[0]==127||skb_DestinationAddress[0]==127)||
            ((skb_SourceAddress[0]==169&&skb_SourceAddress[1]==254)||
            (skb_DestinationAddress[0]==169&&skb_DestinationAddress[1]==254))||
            ((skb_SourceAddress[0]==100&&skb_SourceAddress[1]>=64&&skb_SourceAddress[1]<=127)||
            (skb_DestinationAddress[0]==100&&skb_DestinationAddress[1]>=64&&skb_DestinationAddress[1]<=127))||
            (skb_SourceAddress[0]==0||skb_DestinationAddress[0]==0)||
            ((skb_SourceAddress[0]==255&&skb_SourceAddress[1]==255&&
            skb_SourceAddress[2]==255&&skb_SourceAddress[3]==255)||
            (skb_DestinationAddress[0]==255&&skb_DestinationAddress[1]==255&&
            skb_DestinationAddress[2]==255&&skb_DestinationAddress[3]==255))||
            ((skb_SourceAddress[0]==192&&skb_SourceAddress[1]==0&&skb_SourceAddress[2]==2)||
            (skb_DestinationAddress[0]==192&&skb_DestinationAddress[1]==0&&skb_DestinationAddress[2]==2))||
            ((skb_SourceAddress[0]==198&&skb_SourceAddress[1]==51&&skb_SourceAddress[2]==100)||
            (skb_DestinationAddress[0]==198&&skb_DestinationAddress[1]==51&&skb_DestinationAddress[2]==100))||
            ((skb_SourceAddress[0]==203&&skb_SourceAddress[1]==0&&skb_SourceAddress[2]==113)||
            (skb_DestinationAddress[0]==203&&skb_DestinationAddress[1]==0&&skb_DestinationAddress[2]==113))
            );
    } 
    u16*skb_DestinationAddress=(u16*)(header->PayLoader+8),*skb_SourceAddress=(u16*)(header->PayLoader+24),DestinationAddress[8], SourceAddress[8];
    for(int i=0;i<8;i++){
        DestinationAddress[i]=ntohs(skb_DestinationAddress[i]);
        SourceAddress[i]=ntohs(skb_SourceAddress[i]);
    }
    return!((
        ((DestinationAddress[0]>>8)&254) == 252 ||
        ((SourceAddress[0]>>8)&254) == 252) ||
        ((DestinationAddress[0] & 65472) == 65152 ||
         (SourceAddress[0] & 65472) == 65152) ||
        (DestinationAddress[0]==0 && DestinationAddress[1]==0 && DestinationAddress[2]==0 &&
         DestinationAddress[3]==0 && DestinationAddress[4]==0 && DestinationAddress[5]==0 &&
         DestinationAddress[6]==0 && DestinationAddress[7]==1) ||
        (SourceAddress[0]==0 && SourceAddress[1]==0 && SourceAddress[2]==0 &&
         SourceAddress[3]==0 && SourceAddress[4]==0 && SourceAddress[5]==0 &&
         SourceAddress[6]==0 && SourceAddress[7]==1) ||
        (DestinationAddress[0]==0 && DestinationAddress[1]==0 && DestinationAddress[2]==0 &&
         DestinationAddress[3]==0 && DestinationAddress[4]==0 && DestinationAddress[5]==0 &&
         DestinationAddress[6]==0 && DestinationAddress[7]==0) ||
        (SourceAddress[0]==0 && SourceAddress[1]==0 && SourceAddress[2]==0 &&
         SourceAddress[3]==0 && SourceAddress[4]==0 && SourceAddress[5]==0 &&
         SourceAddress[6]==0 && SourceAddress[7]==0)
    );
}
static struct NetworkDataHeader*GetNetworkDataHeader(struct NetworkAddress*networkAddress,u16 ID){
    if(!networkAddress||list_empty(&networkAddress->data))return NULL;
    struct NetworkDataHeader*networkDataHeader=NULL;
    if(id>32767){
        list_for_each_entry_reverse(networkDataHeader,&networkAddress->data,data) {
            if(networkDataHeader->ID<ID){
                return networkDataHeader;
            }
        }
        return NULL;
    }
    list_for_each_entry(networkDataHeader,&networkAddress->data,data) {
        if(networkDataHeader->ID>ID){
            return networkDataHeader;
        }
    }
    return NULL;
}



static bool RegisterRouter(struct NetworkAddress*networkAddressServer,struct RouterHeader*routerHeader){
    if(!networkAddressServer||!routerHeader)return false;
    if(GetNetworkDataHeader(networkAddressServer,0))return true;
    mutex_lock(&networkAddressServer->lock);
    if(GetNetworkDataHeader(networkAddressServer,0)){
        mutex_unlock(&networkAddressServer->lock);
        return true;
    }
    struct RouterBindServer*routerBindServer=kmalloc(sizeof(struct RouterBindServer),GFP_KERNEL);
    if(!routerBindServer)return;
    routerBindServer->ID=0;
    routerBindServer->routerInfomation=routerHeader;
    routerBindServer->networkAddress=networkAddressServer;
    INIT_LIST_HEAD(&routerBindServer->data);
    INIT_LIST_HEAD(&routerBindServer->version);
    list_add(&routerBindServer->data,&networkAddressServer->data);
    list_add(&routerBindServer->version,networkAddressServer->index==3?&Version4:&Version6);
    mutex_unlock(&networkAddressServer->lock);
    return true;
}
struct ServiceListenerHeader{
    void(*Function)(struct NetworkAddress*,struct NetworkAddress*,struct Packet*);
};
static void Receiver(struct ServiceListenerHeader*serviceListener,struct RouterHeader*routerHeader,struct Packet*packet){
    struct IEEE8023Header*dataLinkLayer=GetEthernetFrame()->DataLinkLayer(packet);
    struct NetworkAddress*NetworkAddressServer=NULL,*NetworkAddressClient=NULL;
    if(GetEthernetFrame()->IsVersion4(dataLinkLayer)){
        u8*Client=dataLinkLayer->PayLoader+12,*Server=dataLinkLayer->PayLoader+16;
        NetworkAddressServer=GetVersion4Address(Server);
        NetworkAddressClient=GetVersion4Address(Client);
          printk(KERN_INFO "NetworkLayer: IPv4 Packet - Source: %d.%d.%d.%d, Destination: %d.%d.%d.%d\n",
           Client[0], Client[1], Client[2], Client[3],
           Server[0], Server[1], Server[2], Server[3]);
    }else{
        u16*skb_SourceAddress=(u16*)(dataLinkLayer->PayLoader+8),*skb_DestinationAddress=(u16*)(dataLinkLayer->PayLoader+24), Server[8],Client[8];
        for(int i=0;i<8;i++){
            Server[i]=ntohs(skb_DestinationAddress[i]);
            Client[i]=ntohs(skb_SourceAddress[i]);
        }
        NetworkAddressServer=GetVersion6Address(Server);
        NetworkAddressClient=GetVersion6Address(Client);
           printk(KERN_INFO "NetworkLayer: IPv6 Packet - Source: %x:%x:%x:%x:%x:%x:%x:%x, Destination: %x:%x:%x:%x:%x:%x:%x:%x\n",
               Client[0], Client[1], Client[2], Client[3], Client[4], Client[5], Client[6], Client[7],
               Server[0], Server[1], Server[2], Server[3], Server[4], Server[5], Server[6], Server[7]);

    }
    if(!NetworkAddressServer||!RegisterRouter(NetworkAddressServer,routerHeader)||!NetworkAddressClient)return;
    SetExpiryNetworkAddress(NetworkAddressClient);
    serviceListener->Function(NetworkAddressServer, NetworkAddressClient, packet);
    SetExpiryNetworkAddress(NetworkAddressClient);
}
static bool WriteVersion4(u8*pos,struct NetworkAddress*networkAddress){
    if(!networkAddress||!pos)return false;
    struct Pointer8*pointer8=(struct Pointer8*)networkAddress;
    for(int i=0;i<4;i++){
        pos[pointer8->index]=pointer8->value;
        pointer8=pointer8->prev;
    }
    return true;
}
static bool WriteVersion6(u16*pos,struct NetworkAddress*networkAddress){
    if(!networkAddress||!pos)return false;
    struct Pointer16*pointer16=(struct Pointer16*)networkAddress;
    for(int i=0;i<8;i++){
        pos[pointer16->index]=htons(pointer16->Value);
        pointer16=pointer16->prev;
    }
    return true;
}



static struct IEEE8023Header*Create(struct NetworkAddress*networkAddresServer,u16 size,struct Packet**packet){
    if(!networkAddresServer||!packet)return NULL;
    struct NetworkDataHeader*networkDataHeader=GetNetworkDataHeader(networkAddresServer, 0);
    if(!networkDataHeader)return NULL;
    struct RouterBindServer*routerBindServer=(struct RouterBindServer*)networkDataHeader;
    if(networkAddresServer->index==3){
        struct IEEE8023Header*iEEE8023Header=GetRouter()->CreateVersion4(size,routerBindServer->routerInfomation, packet);
        if(!iEEE8023Header)return NULL;
        u8*networkLayer=iEEE8023Header->PayLoader;
        u8*Source=networkLayer+12;
        if(!WriteVersion4(Source, networkAddresServer)){
            kfree(*packet);
            return NULL;
        }
        return iEEE8023Header;
    }
    struct IEEE8023Header*iEEE8023Header=GetRouter()->CreateVersion6(size,routerBindServer->routerInfomation, packet);
    if(!iEEE8023Header)return NULL;
    u8*networkLayer=iEEE8023Header->PayLoader;
    u16*Source=(u16*)(networkLayer+8);
    if(!WriteVersion6(Source, networkAddresServer)){
        kfree(*packet);
        return NULL;
    }
    return iEEE8023Header;
}
static int Send(struct NetworkAddress*networkAddresClient,struct Packet*packet){
    if(!networkAddresClient||!packet)return -1;
    struct IEEE8023Header*dataLinkLayer=GetEthernetFrame()->DataLinkLayer(packet);
    u8*networkLayer=dataLinkLayer->PayLoader;
    if(GetEthernetFrame()->IsVersion4(dataLinkLayer)){
        u8*Destination=networkLayer+16;
        if(!WriteVersion4(Destination, networkAddresClient))
            return -1;
    }else{
        u16*Destination=(u16*)(networkLayer+24);
        if(!WriteVersion6(Destination, networkAddresClient))
            return -1;
    }
    SetExpiryNetworkAddress(networkAddresClient);
    int ret=GetEthernetFrame()->Send(packet);
    SetExpiryNetworkAddress(networkAddresClient);
    return ret;
}


End{}
Start(NetworkLayer,Bind(NextHeader),Bind(IsPublic),Bind(Receiver),Bind(Create),Bind(WriteVersion4),Bind(WriteVersion6),Bind(GetVersion4Address),Bind(GetVersion6Address)){}

