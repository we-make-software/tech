#ifndef DeviceStorageManagerFile_h
#define DeviceStorageManagerFile_h
#include "../System/System.h"
#include <linux/fs.h>
    #ifdef UseDeviceStorageManagerFile    
        WeMakeSoftwareLibrary(DeviceStorageManagerFile){
            FunctionWithArgs(void*,Read,u16,u64);
            FunctionWithArgs(bool,Write,void*);
            Function(struct list_head*,List);
            FunctionWithArgs(bool,Update,u16);
        };
        
        #define InitDeviceStorageManagerFile\
            InitSystemLibrary(DeviceStorageManagerFile)

    #endif
#endif