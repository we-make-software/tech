#include "RFC791.h"
static bool Receiver(u8*networkLayer, u8**sourceAddress,u8**destinationAddress,u16**sourcePort,u16**destinationPort,u8**transportLayer){

    return false; 
}
SystemSetup(RFC791, NULL, NULL, Bind(Receiver));