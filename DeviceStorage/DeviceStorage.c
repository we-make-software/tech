#define UseDeviceStorage
#include "../System/.h"
struct DeviceStorageFile{
    u16 id;
    struct file*connection;
    u64 countSector;
    struct list_head list; 
    struct mutex lock; 
    struct DeviceStorageData*data;
    struct DeviceStorageSystem*system;
};
GlobelList(deviceStorageFile);
GlobelList(deviceStorageData);
GlobelMutex(deviceStorageDataLock);
CreateFunctionWithArgs(struct DeviceStorageFile,FGet,u16){
    
}
CreateFunctionWithArgs(struct DeviceStorageSystem*,System,u16 ID){
    struct DeviceStorageFile*file=NULL;
    list_for_each_entry(file,&deviceStorageFile,list){
       if(file->id!=ID)continue;
       if(!file->data)return NULL;
       return file->system; 
    }
    return NULL;
}
CreateFunctionWithArgs(u64,Space,u16 ID){
    struct DeviceStorageFile*file=NULL;
    list_for_each_entry(file,&deviceStorageFile,list){
       if(file->id!=ID)continue;
       if(!file->data)return 0;
       return file->system->DeletedCount+(file->countSector-file->system->UseTotal);
    }
    return 0;
}
CreateFunctionWithArgs(u64,Used,u16 ID){
    struct DeviceStorageSystem*sys=System(ID);
    return sys?sys->UseTotal:0;
}

CreateFunctionWithArgs(struct DeviceStorageData*,Get,u16 ID,u64 Section){
    return NULL;
}
CreateFunctionWithArgs(bool,Free,struct DeviceStorageData*data){
      return false;
}

CreateAction(End){

    struct DeviceStorageData*data,*datatmp;
    list_for_each_entry_safe(data,datatmp,&deviceStorageData,Reference.List){
        data->Reference.Index=0;
        data->Reference.Count=1;
        Free(data);
    }
    
    struct DeviceStorageFile*file,*filetmp;
    list_for_each_entry_safe(file,filetmp,&deviceStorageFile,list){
        filp_close(file->connection,NULL);
        list_del(&file->list);
        kfree(file);
    }
}
WeMakeSoftwareRun(DeviceStorage,&End,Bind(Get),Bind(Free)){
    for(u32 i=0;i<U16MaxOverflow;i++){
        char path[128];
        snprintf(path, sizeof(path),"/root/We-Make-Software/%u.wms",i);
        struct file*connection=filp_open(path,O_RDWR|O_LARGEFILE,0);
        if(IS_ERR(connection))continue;;
        struct DeviceStorageFile*file=kmalloc(sizeof(struct DeviceStorageFile),GFP_KERNEL);
        if(!file){
            filp_close(connection,NULL);
            continue;
        }
        file->id=i;
        file->connection=connection;
        INIT_LIST_HEAD(&file->list);
        file->countSector=i_size_read(file_inode(connection)) >> 9;
        file->data=Get(i,0);
        if(!file->data){
            filp_close(connection,NULL);
            kfree(file);
            continue;
        }
        file->system =(struct DeviceStorageSystem*)file->data->Section.Data;
        if(!file->system->UseEnd){
            file->system->UseEnd=1;
            file->system->UseTotal=1;
            file->system->DeletedEnd=0;
            file->system->DeletedCount=0;
        }
        list_add_tail(&file->list,&deviceStorageFile);
    }
}