#include "RFC1122.h"
struct RFC1122Pointer{
    u8 Address[6];
    struct net_device*dev;
    struct list_head list;
};
struct IEEE802_3Pointer {
    u8 Destination[6];
    u8 Source[6];
} NoStructPadding;
struct Packet {
    struct IEEE802_3Pointer*IEEE802_3;
    u8 Unused[sizeof(void*)*5];
    struct sk_buff*skb;
};
static LIST_HEAD(RFC1122Pointers);
static DEFINE_MUTEX(RFC1122PointersMutex);
static struct RFC1122Pointer*Get(u8*address) {
    if(!address||(address[0] & 2))return NULL;
    struct RFC1122Pointer*pointer=NULL;
    list_for_each_entry(pointer,&RFC1122Pointers,list) {
        if(!memcmp(pointer->Address,address,6))
            return pointer;
    }
    return NULL;
}
static struct RFC1122Pointer*Register(struct Packet*packet) {
    if(!packet||(packet->IEEE802_3->Source[0] & 2))return NULL;
    struct RFC1122Pointer*pointer=Get(packet->IEEE802_3->Source);
    if(pointer)return pointer;
    mutex_lock(&RFC1122PointersMutex);
    pointer=Get(packet->IEEE802_3->Source);
    if(pointer) {
        mutex_unlock(&RFC1122PointersMutex);
        return pointer;
    }
    pointer=kmalloc(sizeof(*pointer),GFP_KERNEL);
    if(!pointer) {
        mutex_unlock(&RFC1122PointersMutex);
        return NULL;
    }
    memcpy(pointer->Address,packet->IEEE802_3->Source,6);
    pointer->dev=packet->skb->dev;
    dev_hold(pointer->dev);
    INIT_LIST_HEAD(&pointer->list);
    list_add_tail(&pointer->list,&RFC1122Pointers);
    mutex_unlock(&RFC1122PointersMutex);
    return pointer;
}
End{
    struct RFC1122Pointer*rFC1122Pointer=NULL,*temp=NULL;
    list_for_each_entry_safe(rFC1122Pointer,temp,&RFC1122Pointers,list) {
        list_del(&rFC1122Pointer->list);
        dev_put(rFC1122Pointer->dev);
        kfree(rFC1122Pointer);
        rFC1122Pointer=NULL;
    }
};
Start(RFC1122,Bind(Get),Bind(Register)){}