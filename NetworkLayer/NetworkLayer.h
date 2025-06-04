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
    u8 value;
    u8 index;
    struct list_head data;
    struct delayed_work work;
    struct mutex lock;
};
struct RouterBindServer{
    void(*Destroy)(struct NetworkAddress*);//this not used when its server
    u16 ID;
    struct RouterHeader*routerInfomation;
    struct NetworkAddress*networkAddress;
    struct list_head data,version;
};
struct NetworkDataHeader{
    void(*Destroy)(struct NetworkAddress*,u16);//this not used when its server
    u16 ID;
};
struct ServiceListenerHeader;
struct RouterHeader;
SystemLibrary(NetworkLayer){
    enum NetworkLayerNextHeader(*NextHeader)(struct IEEE8023Header*);
    bool(*IsPublic)(struct IEEE8023Header*);
    void(*Receiver)(struct ServiceListenerHeader*, struct RouterHeader*, struct Packet*);
    struct NetworkDataHeader*(*GetNetworkDataHeader)(struct NetworkAddress*,u16);
    struct IEEE8023Header*(*Create)(struct NetworkAddress*,struct NetworkAddress*,u16,struct Packet**);
    bool(*WriteVersion4)(u8*,struct NetworkAddress*);
    bool(*WriteVersion6)(u16*,struct NetworkAddress*);
    struct list_head*(*GetServerVersion4)(void);
    struct list_head*(*GetServerVersion6)(void);
    struct NetworkAddress*(*GetVersion4Address)(u8*);
    struct NetworkAddress*(*GetVersion6Address)(u16*);
};

#define InitNetworkLayer\
        InitSystemLibrary(NetworkLayer)

#endif