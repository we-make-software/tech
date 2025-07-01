#ifndef DeviceStorage_h
#define DeviceStorage_h
#include "../System/System.h"
#include <linux/fs.h>
    #ifdef UseDeviceStorage     
        Struct DeviceStorageSection{
            u8 Data[512];
        };
        Struct DeviceStorageAddress{
            u16 ID;
            u64 Section;
        };
        struct DeviceStorageReference{
            struct mutex Read,Write;
            struct list_head List;
            u32 Index;
            u64 Count;
            bool Overwrite;
        };
        struct DeviceStorageData{
            struct DeviceStorageSection Section;
            struct DeviceStorageAddress Address;
            struct DeviceStorageReference Reference;
        };
        Struct DeviceStorageSystem{
            u64 Unused[60];
            u64 UseEnd;
            u64 UseTotal;
            u64 DeletedEnd;
            u64 DeletedCount;
        };
        Struct DeviceStorageDeleted{
            u64 Prev;
            u64 Count;
            u64 Sections[62];
        };
        WeMakeSoftwareLibrary(DeviceStorage){
            FunctionWithArgs(struct DeviceStorageData*,Get,u16,u64);
            FunctionWithArgs(bool,Free,struct DeviceStorageData*);
            ActionWithArgs(Look,struct DeviceStorageData*);
            ActionWithArgs(Unlock,struct DeviceStorageData*);
            ActionWithArgs(Overwrite,struct DeviceStorageData*);
        };
        #define InitDeviceStorage\
            InitSystemLibrary(DeviceStorage)

    #endif
#endif