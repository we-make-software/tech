#include "../Network/Network.h"
InitIEEE802_3

static bool AllowNetwork=true;
struct Adapter{
  struct packet_type type;  
  struct list_head list;
};

struct Packet{
    u8*IEEE802_3;
    u8 Unused[sizeof(void*)*5];
    struct sk_buff*skb;
    struct work_struct work;
};

static void Free(struct Packet* packet) {
    if(!packet)return;
    if(packet->skb)
        kfree_skb(packet->skb);
    kfree(packet);
    packet=NULL;
}
static LIST_HEAD(Adapters);
static bool Send(struct Packet*packet){
    int ret=dev_queue_xmit(packet->skb);
    if(ret==0)
        kfree(packet);
    return ret==0;
}
static struct Packet*Create(u16 size,struct net_device*dev) {
    struct Packet*packet=kmalloc(sizeof(*packet),GFP_KERNEL);
    if(!packet) 
        return NULL;
    packet->skb=alloc_skb(size, GFP_KERNEL);
    if(!packet->skb){
        kfree(packet);
        return NULL;
    }
    skb_set_mac_header(packet->skb,0);
    packet->IEEE802_3=packet->skb->data;
    packet->skb->dev=dev;
    memcpy(packet->IEEE802_3+6,dev->dev_addr,6);
    packet->skb->len=size; 
    return packet;
}
static void Continue(struct work_struct*work){
    struct Packet*packet=container_of(work,struct Packet,work);
    if(!AllowNetwork){
        Free(packet);
        return;
    }
    GetIEEE802_3()->Continue(packet);
    Free(packet);
}
static int Receiver(struct sk_buff*skb,struct net_device*dev,struct packet_type*pt,struct net_device*orig_dev){
    if(skb->pkt_type==PACKET_OUTGOING||!AllowNetwork)return 0;
    struct Packet*packet=kmalloc(sizeof(*packet),GFP_KERNEL);
    if(!packet) {
        kfree_skb(skb);
        return NET_RX_DROP;
    }
    packet->skb=skb;
    packet->IEEE802_3=skb_mac_header(skb);
    if(GetIEEE802_3()->Receiver(packet)){
        INIT_WORK(&packet->work, Continue);
        queue_work(system_wq, &packet->work);
        return NET_RX_DROP;
    }
    kfree(packet);
    return NET_RX_SUCCESS;
}
End{
    AllowNetwork=false;
    struct Adapter*adapter,*tmp;
    list_for_each_entry_safe(adapter,tmp,&Adapters,list){
        dev_remove_pack(&adapter->type);
        list_del(&adapter->list);
        kfree(adapter);
    }
    synchronize_net();
}
Start(NetworkAdapter,Bind(Send),Bind(Create),Bind(Free)) {
    struct net_device*dev;
    struct ethtool_link_ksettings link_settings;
    rcu_read_lock();
    for_each_netdev(&init_net,dev){
        if(dev->ethtool_ops&&dev->ethtool_ops->get_link_ksettings){
            memset(&link_settings,0,sizeof(link_settings));
            link_settings.base.cmd=ETHTOOL_GLINKSETTINGS;
            if(dev->ethtool_ops->get_link_ksettings(dev, &link_settings)==0 && link_settings.base.duplex==DUPLEX_FULL){
                struct Adapter*adapter=kmalloc(sizeof(struct Adapter), GFP_KERNEL);
                adapter->type.type=htons(ETH_P_ALL);
                adapter->type.dev=dev;
                adapter->type.func=Receiver;
                INIT_LIST_HEAD(&adapter->list);
                list_add(&adapter->list,&Adapters);
                dev_add_pack(&adapter->type);
            }
        }
    }
    rcu_read_unlock();
    synchronize_net();
    AllowNetwork=true;
}