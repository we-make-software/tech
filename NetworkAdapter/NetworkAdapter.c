#include "../MediaAccessControl/MediaAccessControl.h"
UseMediaAccessControlLibrary
struct Adapter{
  struct packet_type type;  
  struct list_head list;
};
static LIST_HEAD(Adapters);
static int Receiver(struct sk_buff*skb,struct net_device*dev,struct packet_type*pt,struct net_device*orig_dev){
    return GetMediaAccessControl()->Receiver(skb,dev);
}
Start{
    struct net_device*dev;
    struct ethtool_link_ksettings link_settings;
    rcu_read_lock();
    for_each_netdev(&init_net,dev){
        if(dev->ethtool_ops&&dev->ethtool_ops->get_link_ksettings){
            memset(&link_settings,0,sizeof(link_settings));
            link_settings.base.cmd=ETHTOOL_GLINKSETTINGS;
            if(dev->ethtool_ops->get_link_ksettings(dev, &link_settings)==0 && link_settings.base.duplex==DUPLEX_FULL){
                struct Adapter*adapter=kmalloc(sizeof(*adapter), GFP_KERNEL);
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
}
End{
    struct Adapter*adapter,*tmp;
    list_for_each_entry_safe(adapter,tmp,&Adapters,list){
        dev_remove_pack(&adapter->type);
        list_del(&adapter->list);
        kfree(adapter);
    }
    synchronize_net();
}
SystemSetup(NetworkAdapter,BindStart,BindEnd)