#ifndef DeviceStorageManagerFile_h
#define DeviceStorageManagerFile_h
#include "../System/System.h"
#include <linux/fs.h>
    #ifdef UseDeviceStorageManagerFile    

        WeMakeSoftwareLibrary(DeviceStorageManagerFile){
            FunctionWithArgs(u64,Sectors,u16);
            FunctionWithArgs(u8*,Read,u16,u64);
            FunctionWithArgs(bool,Write,u8*,u16,u64);
        };
        #define InitDeviceStorageManagerFile\
            InitSystemLibrary(DeviceStorageManagerFile)

    #endif
#endif