#ifndef InternetControlMessageProtocolVersion4_h
#define InternetControlMessageProtocolVersion4_h
#include "../ServiceListener/ServiceListener.h"
SystemLibrary(InternetControlMessageProtocolVersion4) {
    void(*Receiver)(struct Packet*);
};
#define InitInternetControlMessageProtocolVersion4 \
        InitSystemLibrary(InternetControlMessageProtocolVersion4)

#endif