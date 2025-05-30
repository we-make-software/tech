#include "RFC9293.h"
static bool Permission(u16*destinationPort, struct ReceiverNetworkLayer**receiverNetworkLayer) {

    return false;
}

SystemSetup(RFC9293, NULL, NULL, NULL, Bind(Permission));