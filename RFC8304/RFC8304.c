#include "RFC8304.h"
static bool Permission(u16*destinationPort, struct ReceiverNetworkLayer**receiverNetworkLayer) {

    return false;
}

SystemSetup(RFC8304, NULL, NULL, NULL, Bind(Permission));