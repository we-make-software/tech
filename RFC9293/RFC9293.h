#ifndef RFC9293_h
#define RFC9293_h
#include "../MediaAccessControl/MediaAccessControl.h"
#include "../RFC791/RFC791.h"
#include "../RFC8200/RFC8200.h"

SystemLibrary(RFC9293){
    bool(*Permission)(u16*,struct ReceiverNetworkLayer**);
};

#define UseRFC9293Library\
        InitSystemLibrary(RFC9293)

#endif