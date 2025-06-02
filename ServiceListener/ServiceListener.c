#include "ServiceListener.h"
InitEthernetFrame
InitNetworkLayer
InitTransportLayer

static LIST_HEAD(TransmissionControlProtocol_List);
static LIST_HEAD(UserDatagramProtocol_List);

static struct ServiceListenerHeader*Get(struct Packet*packet) {
    struct IEEE8023Header*dataLinkLayer=GetEthernetFrame()->DataLinkLayer(packet);
    GetNetworkLayer()->NextHeader(dataLinkLayer);
    struct TransportLayerHeader*transportLayerHeader=GetTransportLayer()->Get(dataLinkLayer);

    return NULL;
}
End{}
Start(ServiceListener, Bind(Get)){
   
}
