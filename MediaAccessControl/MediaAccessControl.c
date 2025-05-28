#include "MediaAccessControl.h"
static bool IsLocal(u8* data) {
    return (*data & 2);
}
static int Receiver(struct sk_buff*skb,struct net_device*dev){
    u8*data=skb_mac_header(skb);
    if(IsLocal(data)||IsLocal(data+6))
       return 0;
    printk(KERN_INFO "Received packet from %pM to %pM\n", data, data + 6);   
    return 0;
}
End{

}
SystemSetup(MediaAccessControl, NULL, BindEnd,Bind(Receiver));