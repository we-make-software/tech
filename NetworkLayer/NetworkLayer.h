#ifndef NetworkLayer_h
#define NetworkLayer_h
#include "../EthernetFrame/EthernetFrame.h"
#include <linux/workqueue.h>
#include <linux/jiffies.h>
#include <linux/time.h>
enum NetworkLayerNextHeader{
    NetworkLayerNextHeader_TransmissionControlProtocol = 6, 
    NetworkLayerNextHeader_UserDatagramProtocol = 17,
    NetworkLayerNextHeader_InternetControlMessageProtocolVersion4 = 1,
    NetworkLayerNextHeader_InternetControlMessageProtocolVersion6 = 58,
    NetworkLayerNextHeader_Unknown
};
struct NetworkAddress{
    u8 index;
    struct list_head data;
    struct delayed_work work;
    struct mutex lock;
};

struct NetworkDataHeader{
    void(*Destroy)(struct NetworkAddress*,u16);
    u16 ID;
    struct list_head data;
};
struct ServiceListenerHeader;
struct RouterHeader;
SystemLibrary(NetworkLayer){
    enum NetworkLayerNextHeader(*NextHeader)(struct IEEE8023Header*);
    bool(*IsPublic)(struct IEEE8023Header*);
    void(*Receiver)(struct ServiceListenerHeader*, struct RouterHeader*, struct Packet*);
    struct NetworkDataHeader*(*GetNetworkDataHeader)(struct NetworkAddress*,u16);
    struct IEEE8023Header*(*Create)(struct NetworkAddress*,u16,struct Packet**);
    bool(*WriteVersion4)(u8*,struct NetworkAddress*);
    bool(*WriteVersion6)(u16*,struct NetworkAddress*);
    struct list_head*(*GetServerVersion4)(void);
    struct list_head*(*GetServerVersion6)(void);
    int(*Send)(struct NetworkAddress*, struct Packet*);
    struct NetworkAddress*(*GetConnectionVersion4)(u8*);
    struct NetworkAddress*(*GetConnectionVersion6)(u16*);
};

#define InitNetworkLayer\
        InitSystemLibrary(NetworkLayer)

#endif