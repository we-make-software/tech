#ifndef InternetControlMessageProtocolVersion6_h
#define InternetControlMessageProtocolVersion6_h
#include "../InternetControlMessageProtocolVersion4/InternetControlMessageProtocolVersion4.h"
SystemLibrary(InternetControlMessageProtocolVersion6) {
    void(*Receiver)(struct Packet*);
};

#define InitInternetControlMessageProtocolVersion6 \
        InitSystemLibrary(InternetControlMessageProtocolVersion6)

#endif