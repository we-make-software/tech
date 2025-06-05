#include "InternetControlMessageProtocolVersion4.h"
InitEthernetFrame
static u8 Type(struct IEEE8023Header*header) {
    //ICMP type
   return header->PayLoader[20];
}

static void Receiver(struct NetworkAddress*networkAddressServer,struct NetworkAddress*networkAddressClient,struct Packet*packet) {
    struct IEEE8023Header*header =GetEthernetFrame()->DataLinkLayer(packet);
    u8 type = Type(header);
        printk(KERN_INFO "TYPE: %u\n", type);
    // Process the packet as needed
}

End{}
Start(InternetControlMessageProtocolVersion4, Bind(Receiver)) {

}