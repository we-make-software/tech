#include "MediaAccessControl.h"
static int Receiver(struct sk_buff*skb,struct net_device*dev) {
    return 0;
}
End{

}
SystemSetup(MediaAccessControl, NULL, BindEnd) {
    return (void*)&(struct MediaAccessControlLibrary) {
        .Receiver = Receiver
    };
}