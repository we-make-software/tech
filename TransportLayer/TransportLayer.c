#include "TransportLayer.h"
InitEthernetFrame

static struct TransportLayerHeader*Get(struct IEEE8023Header*header) {
    if(!header)return NULL;
    return (struct TransportLayerHeader*)(header->PayLoader+(GetEthernetFrame()->IsVersion4(header)?20:40));
}
End{}
Start(TransportLayer, Bind(Get)) {
  
}