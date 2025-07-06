#define UseDeviceStorageManagerFile
#include "../System/.h"
struct DSMF{
    u16 id;
    struct file*connection;
    u64 sectors;
    struct list_head list; 
    struct mutex lock; 
}; 
GlobelList(dSMF);
CreateFunctionWithArgs(struct DSMF*,Get,u16 ID){
    struct DSMF*file=NULL;
    list_for_each_entry(file,&dSMF,list){
       if(file->id!=ID)continue;
       return file; 
    }
    return NULL;
}
CreateFunctionWithArgs(bool,Lock,u16 ID){
    struct DSMF*file=Get(ID);
    if(file){
        mutex_lock(&file->lock);
        return true;
    }
    return false;
}
CreateFunctionWithArgs(bool,Unlock,u16 ID){
    struct DSMF*file=Get(ID);
    if(file){
        mutex_unlock(&file->lock);
        return true;
    }
    return false;
}
CreateFunctionWithArgs(u64,Sectors,u16 ID){
    struct DSMF*file=Get(ID);
    return file?file->sectors:0;
}

CreateFunctionWithArgs(u8*,Read,u16 ID,u64 Section){
   struct DSMF*file=Get(ID);
}
CreateFunctionWithArgs(bool,Write,u8*,u16 ID,u64 Section){
   struct DSMF*file=Get(ID);
}


CreateAction(Test){
      printk(KERN_INFO "hello world\n");
}
CreateAction(End){
    struct DSMF*file,*tmp;
    list_for_each_entry_safe(file,tmp,&dSMF,list){
        filp_close(file->connection,NULL);
        list_del(&file->list);
        kfree(file);
    }
}
WeMakeSoftwareRun(DeviceStorage,&End,Bind(Sectors),Bind(Read),Bind(Write)){
    for(u32 i=0;i<U16MaxOverflow;i++){
        char path[128];
        snprintf(path, sizeof(path),"/root/We-Make-Software/%u.wms",i);
        struct file*connection=filp_open(path,O_RDWR|O_LARGEFILE,0);
        if(IS_ERR(connection))continue;
        struct DSMF*file=kmalloc(sizeof(struct DSMF),GFP_KERNEL);
        if(!file){
            filp_close(connection,NULL);
            continue;
        }
        file->id=i;
        file->connection=connection;
        INIT_LIST_HEAD(&file->list);
        file->sectors=i_size_read(file_inode(connection)) >> 9;
        list_add_tail(&file->list,&dSMF);
    }
    Test();
}