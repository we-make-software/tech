#define UseDeviceStorageManagerFile
#define UseDeviceStorageManagerSystem
#include "../System/.h"
InitDeviceStorageManagerFile
struct DSMS{
    struct list_head list; 
    u16 id;
    u64 Space,NextSection,FreeCount,System[62];
    struct mutex lock; 
};
CreateFunctionWithArgs(void*,Find,u16 ID){
    struct DSMS*data;
    list_for_each_entry(data, GetDeviceStorageManagerFile()->List(), list) {
        if (data->id==ID)return(void*)data; 
    }
    return NULL;
}
CreateFunctionWithArgs(bool,Set,void*file,u8 index,u64 value){
    if(index>=61)return false;
    struct DSMS*dsms=(struct DSMS*)file;
    if(!dsms)return false;
    dsms->System[index]=value;
    return GetDeviceStorageManagerFile()->Update(dsms->id);
}
CreateFunctionWithArgs(u64,Get,void*file,u8 index){
    if(index>=61)return 0;
    struct DSMS*dsms=(struct DSMS*)file;
    return dsms?dsms->System[index]:0;
}
CreateFunction(void*,New){
    struct DSMS*data;
    list_for_each_entry(data,GetDeviceStorageManagerFile()->List(), list) {
        if(!data->Space)
            return(void*)data; 
    }
    return NULL;
}
CreateFunctionWithArgs(void*,Static,void*file){
    struct DSMS*dsms=(struct DSMS*)file;
    if(!dsms)return NULL;
    return(void*)dsms; 
}

CreateActionWithArgs(Init,void*file,u64 Sectors){
    struct DSMS*dsms=(struct DSMS*)file;
    dsms->Space=Sectors;
    if(dsms->NextSection)
        dsms->Space-=(dsms->NextSection-1);
    else{
        dsms->NextSection=1;
        dsms->Space-=1;
        GetDeviceStorageManagerFile()->Update(dsms->id);
    }
    dsms->Space+=dsms->FreeCount?dsms->FreeCount:0;
}
WeMakeSoftwareRun(DeviceStorageManagerSystem, NULL,
    Bind(Init),
    Bind(Find),
    Bind(Set),
    Bind(Get),
    Bind(New),
    Bind(Static)
){}