#ifndef RFC791_h
#define RFC791_h
#include "../MediaAccessControl/MediaAccessControl.h"

SystemLibrary(RFC791){
    bool(*Receiver)(u8*,u8**,u8**,u16**,u16**,u8**);
    void(*Continue)(struct work_struct*);
};

#define UseRFC791Library\
        InitSystemLibrary(RFC791)

#endif