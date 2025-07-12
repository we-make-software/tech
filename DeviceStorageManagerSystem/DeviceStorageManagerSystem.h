#ifndef DeviceStorageManagerSystem_h
#define DeviceStorageManagerSystem_h
#include "../DeviceStorageManagerFile/DeviceStorageManagerFile.h"
    #ifdef UseDeviceStorageManagerSystem   

        WeMakeSoftwareLibrary(DeviceStorageManagerSystem){
            ActionWithArgs(Init,void*,u64);
            FunctionWithArgs(void*,Find,u16);
            FunctionWithArgs(bool,Set,void*,u8,u64);
            FunctionWithArgs(u64,Get,void*,u8);
            Function(void*,New);
            FunctionWithArgs(void*,Static,void*);
        };

        #define InitDeviceStorageManagerSystem\
            InitSystemLibrary(DeviceStorageManagerSystem)

    #endif
#endif