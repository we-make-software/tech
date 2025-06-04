#include "InternetControlMessageProtocolVersion6.h"

static void Receiver(struct NetworkAddress*networkAddressServer,struct NetworkAddress*networkAddressClient,struct Packet*packet) {

}

End{}
Start(InternetControlMessageProtocolVersion6, Bind(Receiver)) {

}