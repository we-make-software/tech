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
CreateFunctionWithArgs(u64, Used, u16 ID){
    struct DeviceStorageSystem*sys=System(ID);
    return sys?sys->UseTotal:0;
}

CreateFunctionWithArgs(struct DeviceStorageData*,Get,u16 ID,u64 Section){
    struct DeviceStorageData*data=NULL;
    list_for_each_entry(data,&deviceStorageData,Reference.List){
        if(data->Address.ID==ID&&data->Address.Section==Section){
            mutex_lock(&data->Reference.Read);
            if(data->Reference.Count==(u64)u64Max){
                data->Reference.Index++;
                data->Reference.Count=0;
                mutex_unlock(&data->Reference.Read);
                return data;
            }
            data->Reference.Count++;
            mutex_unlock(&data->Reference.Read);
            return data;
        }
    }
    mutex_lock(&deviceStorageDataLock);
    data=NULL;
    list_for_each_entry(data,&deviceStorageData,Reference.List){
        if(data->Address.ID==ID&&data->Address.Section==Section){
            mutex_lock(&data->Reference.Read);
            if(data->Reference.Count==(u64)u64Max){
                data->Reference.Index++;
                data->Reference.Count=0;
                mutex_unlock(&data->Reference.Read);
                mutex_unlock(&deviceStorageDataLock);
                return data;
            }
            data->Reference.Count++;
            mutex_unlock(&data->Reference.Read);
            mutex_unlock(&deviceStorageDataLock);
            return data;
        }
    }
    struct DeviceStorageFile*file=NULL;
    list_for_each_entry(file,&deviceStorageFile,list){
        if(file->id!=ID)continue;
        if(file->countSector<Section){
            mutex_unlock(&deviceStorageDataLock);
            return NULL;
        }
        break;
    }
    if(!file){
        mutex_unlock(&deviceStorageDataLock);
        return NULL;
    }
    data=kmalloc(sizeof(struct DeviceStorageData),GFP_KERNEL);
    if(!data){
        mutex_unlock(&deviceStorageDataLock);
        return NULL;
    }
    data->Address.ID=ID;
    data->Address.Section=Section;
    data->Reference.Index=0;
    data->Reference.Count=1;
    data->Reference.Overwrite=false;
    INIT_LIST_HEAD(&data->Reference.List);
    mutex_init(&data->Reference.Read);
    mutex_init(&data->Reference.Write);
    loff_t offset=(loff_t)data->Address.Section<<9;
    if (kernel_read(file->connection,data->Section.Data,512,&offset)!=512) {
        kfree(data);
        mutex_unlock(&deviceStorageDataLock);
        return NULL;
    }
    list_add_tail(&data->Reference.List,&deviceStorageData);
    mutex_unlock(&deviceStorageDataLock);
    return data;
}
CreateFunctionWithArgs(bool,Free,struct DeviceStorageData*data){
    if(!data)return false;
    mutex_lock(&data->Reference.Read);
    mutex_lock(&data->Reference.Write);
    struct DeviceStorageFile*file=NULL;
    list_for_each_entry(file,&deviceStorageFile,list){
        if(file->id!=data->Address.ID)continue;
        if(file->countSector<data->Address.Section){
            mutex_unlock(&data->Reference.Read);
            mutex_unlock(&data->Reference.Write);
            return false;
        }
        break;
    }
    if(!file){
        mutex_unlock(&data->Reference.Read);
        mutex_unlock(&data->Reference.Write);
        kfree(data);
        return false;
    }
    if(!data->Reference.Index){
        if(data->Reference.Count){
            data->Reference.Count--;
            mutex_unlock(&data->Reference.Read);
            mutex_unlock(&data->Reference.Write);
            return true;
        }
        data->Reference.Index--;
        data->Reference.Count=(u64)u64Max;
        mutex_unlock(&data->Reference.Read);
        mutex_unlock(&data->Reference.Write);
        return true;
    }
    data->Reference.Count--;
    if(data->Reference.Count){
        mutex_unlock(&data->Reference.Read);
        mutex_unlock(&data->Reference.Write);
        return true;
    }
    mutex_lock(&deviceStorageDataLock);
    list_del(&data->Reference.List);
    if(data->Reference.Overwrite){
        loff_t base_offset = (loff_t)data->Address.Section << 9;
        ssize_t written;
        for(u8 retry=0; retry<10; retry++){
            loff_t offset = base_offset;
            written=kernel_write(file->connection, data->Section.Data, 512, &offset);
            if(written==512)break;
        }
        if(written != 512||vfs_fsync(file->connection,0)<0){
            mutex_unlock(&deviceStorageDataLock);
            mutex_unlock(&data->Reference.Read);
            mutex_unlock(&data->Reference.Write);
            kfree(data);
            return false;
        }
    }
    mutex_unlock(&deviceStorageDataLock);
    mutex_unlock(&data->Reference.Read);
    mutex_unlock(&data->Reference.Write);
    kfree(data);
    return true;
}
CreateAction(Look,struct DeviceStorageData*data){
    if(!data)return;
    mutex_lock(&data->Reference.Write);
}
CreateAction(Unlock,struct DeviceStorageData*data){
    if(!data)return;
    mutex_unlock(&data->Reference.Write);
}
CreateAction(Overwrite,struct DeviceStorageData*data){
    if(!data||data->Reference.Overwrite)return;
    mutex_lock(&data->Reference.Read);
    data->Reference.Overwrite=true;
    mutex_unlock(&data->Reference.Read);
}

CreateFunctionWithArgs(struct DeviceStorageData*,New,u16 ID){
    struct DeviceStorageSystem*sys=System(ID);
    if(!sys||!Space(ID))return NULL;
    mutex_lock(&file->data->Reference->Write);
    mutex_unlock(&file->data->Reference->Write);
    return NULL;
}
CreateFunctionWithArgs(bool,Delete,struct DeviceStorageData*data){
    if(!data)return true;
    return false;
}

CreateAction(End){
    struct DeviceStorageData*data,*tmp;
    list_for_each_entry_safe(data,tmp,&deviceStorageData,Reference.List){
        data->Reference.Index=0;
        data->Reference.Count=1;
        Free(data);
    }
    struct DeviceStorageFile*file,*tmp;
    list_for_each_entry_safe(file,tmp,&deviceStorageFile,list){
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
            file->system->FreeStart=0;
            file->system->FreeEnd=0;
            file->system->FreeCount=0;
        }
        list_add_tail(&file->list,&deviceStorageFile);
    }
}