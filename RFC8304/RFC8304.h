#ifndef RFC8304_h
#define RFC8304_h
#include "../MediaAccessControl/MediaAccessControl.h"
#include "../RFC791/RFC791.h"
#include "../RFC8200/RFC8200.h"

SystemLibrary(RFC8304){
    bool(*Permission)(u16*,struct ReceiverNetworkLayer**);
};

#define UseRFC8304Library\
        InitSystemLibrary(RFC8304)

#endif