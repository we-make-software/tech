#include "../InternetControlMessageProtocolVersion6/InternetControlMessageProtocolVersion6.h"
InitEthernetFrame
InitNetworkLayer
InitTransportLayer
InitInternetControlMessageProtocolVersion4
InitInternetControlMessageProtocolVersion6
static LIST_HEAD(TransmissionControlProtocol_List);
static LIST_HEAD(UserDatagramProtocol_List);
struct ServiceListenerHeader{
    void(*Function)(struct NetworkAddress*,struct NetworkAddress*,struct Packet*);
    u16 Port;
    struct list_head list;
};
static struct ServiceListenerHeader InternetControlMessageProtocolVersion4;
static struct ServiceListenerHeader InternetControlMessageProtocolVersion6; 
static struct ServiceListenerHeader*Get(struct Packet*packet) {
    struct IEEE8023Header*dataLinkLayer=GetEthernetFrame()->DataLinkLayer(packet);
    struct TransportLayerHeader*transportLayerHeader=GetTransportLayer()->Get(dataLinkLayer);
    struct ServiceListenerHeader*serviceListenerHeader=NULL;
    if(GetNetworkLayer()->NextHeader(dataLinkLayer)==NetworkLayerNextHeader_TransmissionControlProtocol){
        list_for_each_entry(serviceListenerHeader, &TransmissionControlProtocol_List, list) {
            if(ntohs(transportLayerHeader->DestinationPort) == serviceListenerHeader->Port) {
                return serviceListenerHeader;
            }
        }
    }else if(GetNetworkLayer()->NextHeader(dataLinkLayer)==NetworkLayerNextHeader_UserDatagramProtocol){
        list_for_each_entry(serviceListenerHeader, &UserDatagramProtocol_List, list) {
            if(ntohs(transportLayerHeader->DestinationPort) == serviceListenerHeader->Port) {
                return serviceListenerHeader;
            }
        }
    }else if(GetNetworkLayer()->NextHeader(dataLinkLayer)==NetworkLayerNextHeader_InternetControlMessageProtocolVersion4){
        return &InternetControlMessageProtocolVersion4;
    }else if(GetNetworkLayer()->NextHeader(dataLinkLayer)==NetworkLayerNextHeader_InternetControlMessageProtocolVersion6){
        return &InternetControlMessageProtocolVersion6;
    }
    return NULL;
}
End{}
Start(ServiceListener, Bind(Get)){
   InternetControlMessageProtocolVersion4.Function=GetInternetControlMessageProtocolVersion4()->Receiver;
   InternetControlMessageProtocolVersion6.Function=GetInternetControlMessageProtocolVersion6()->Receiver; 
}
