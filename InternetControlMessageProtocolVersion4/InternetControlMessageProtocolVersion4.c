#include "InternetControlMessageProtocolVersion4.h"
InitEthernetFrame
InitNetworkLayer
static u8 Type(struct IEEE8023Header*header) {
    //ICMP type
   return header->PayLoader[20];
}
static u8 Code(struct IEEE8023Header*header) {
    //ICMP code
    return header->PayLoader[21];
}

static void SetCheckSum(struct IEEE8023Header*header,u16 size) {
    *(u16*)(header->PayLoader+22)=0;
    u32 sum=0;
    const u16*buf=(const u16*)(header->PayLoader+20);
    for(int i=0;i<size/2;i++)sum+=buf[i];
    if(size&1)sum+=*((const u8*)buf+size-1);
    while(sum>>16)sum=(sum&0xFFFF)+(sum>>16);
    *(u16*)(header->PayLoader+22)=(u16)(~sum);
    GetNetworkLayer()->SetPayloadLength(header, size);
}

static void Receiver(struct NetworkAddress*networkAddressServer,struct NetworkAddress*networkAddressClient,struct Packet*packet) {
    struct IEEE8023Header*header =GetEthernetFrame()->DataLinkLayer(packet);
    u8 type = Type(header);

    switch ( Type(header))
    {
    case 0: // Destination Unreachable
        /* code */
    case 8:
    {
        u16 payloadLength=GetNetworkLayer()->PayloadLength(header);
        struct Packet *replyPacket;
        struct IEEE8023Header*replyIEEE8023Header=GetNetworkLayer()->Create(networkAddressServer,payloadLength,&replyPacket);
        if(!replyIEEE8023Header)return;
        *(u16*)(replyIEEE8023Header->PayLoader+20)=0;
        *(u32*)(replyIEEE8023Header->PayLoader+22)=*(u32*)(header->PayLoader+22);
        *(u16*)(replyIEEE8023Header->PayLoader+4)=*(u16*)(header->PayLoader + 4);
        if(payloadLength>8)
            memcpy(replyIEEE8023Header->PayLoader+8, header->PayLoader+8,payloadLength-8);
        SetCheckSum(replyIEEE8023Header, payloadLength);
        replyIEEE8023Header->PayLoader[1]=0;// Type of Service
        
        return;
    }
    default:
        ///stop it i just want to print the fucking type
        printk(KERN_INFO "ICMPv4 Type: %u\n", type);
        printk(KERN_INFO "ICMPv4 Code: %u\n", Code(header));
        break;
    }
}

End{}
Start(InternetControlMessageProtocolVersion4, Bind(Receiver)) {

}