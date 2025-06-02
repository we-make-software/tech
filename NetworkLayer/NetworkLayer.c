#include "../ServiceListener/ServiceListener.h"
InitEthernetFrame


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
    u16*skb_DestinationAddress=(u16*)(header->PayLoader+8),*skb_SourceAddress=(u16*)(header->PayLoader+16),DestinationAddress[8], SourceAddress[8];
    for(int i=0;i<8;i++){
        DestinationAddress[i]=ntohs(skb_DestinationAddress[i]);
        SourceAddress[i]=ntohs(skb_SourceAddress[i]);
    }
    return!((((DestinationAddress[0]>>8)&254)==252||
    ((SourceAddress[0]>>8)&254)==252)||
    ((DestinationAddress[0]==0&&DestinationAddress[1]==0&&DestinationAddress[2]==0&&
    DestinationAddress[3]==0&&DestinationAddress[4]==0&&DestinationAddress[5]==0&&
    DestinationAddress[6]==0&&DestinationAddress[7]==1)||
    (SourceAddress[0]==0&&SourceAddress[1]==0&&SourceAddress[2]==0&&
    SourceAddress[3]==0&&SourceAddress[4]==0&&SourceAddress[5]==0&&
    SourceAddress[6]==0&&SourceAddress[7]==1))||
    ((DestinationAddress[0]==0&&DestinationAddress[1]==0&&DestinationAddress[2]==0&&
    DestinationAddress[3]==0&&DestinationAddress[4]==0&&DestinationAddress[5]==0&&
    DestinationAddress[6]==0&&DestinationAddress[7]==0)||
    (SourceAddress[0]==0&&SourceAddress[1]==0&&SourceAddress[2]==0&&
    SourceAddress[3]==0&&SourceAddress[4]==0&&SourceAddress[5]==0&&
    SourceAddress[6]==0&&SourceAddress[7]==0)));
}
static void Receiver(struct ServiceListenerHeader*serviceListener,struct RouterHeader*routerHeader,struct Packet*packet){
}
End{}
Start(NetworkLayer,Bind(NextHeader),Bind(IsPublic),Bind(Receiver)){}

