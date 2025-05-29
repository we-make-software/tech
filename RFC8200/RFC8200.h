#ifndef RFC8200_h
#define RFC8200_h
#include "../MediaAccessControl/MediaAccessControl.h"
 
SystemLibrary(RFC8200){
    bool(*Receiver)(u8*,u8**,u8**,u16**,u16**,u8**);
        void(*Continue)(struct work_struct*);
};

#define UseRFC8200Library\
        InitSystemLibrary(RFC8200)

#endif