#define UseDeviceStorageManagerFile
#define UseDeviceStorageManagerSystem
#include "../System/.h"
InitDeviceStorageManagerSystem
struct DSMF{
    struct list_head list; 
    u16 id;
    u64 Reserved;
    u8 Data[512];
    struct mutex lock; 
    struct file*connection;
}; 
GlobelList(dSMF);

struct DSP{
    u8 Buffer[512];
    u16 ID;
    u64 Sector;
    struct mutex Lock;
    bool Overwrite;
    struct delayed_work work; 
    struct list_head list; 
};

CreateFunctionWithArgs(struct DSMF*,Get,u16 ID){
    struct DSMF*file=NULL;
    list_for_each_entry(file,&dSMF,list){
       if(file->id!=ID)continue;
       return file; 
    }
    return NULL;
}
CreateFunction(struct list_head*,List){
    return &dSMF;
}
CreateFunctionWithArgs(void*,Read,u16 ID,u64 Sector){
    struct DSMF*file=Get(ID);
    if(!file)return NULL;
    struct DSP*dsp=kmalloc(sizeof(*dsp),GFP_KERNEL);
    if(!dsp)return NULL;
    dsp->ID=ID;
    dsp->Sector=Sector;
    mutex_init(&dsp->Lock);
    INIT_DELAYED_WORK(&dsp->work,NULL);
    INIT_LIST_HEAD(&dsp->list);
    loff_t offset=Sector<<9;
    mutex_lock(&file->lock);
    ssize_t len=kernel_read(file->connection,dsp->Buffer,512,&offset);
    mutex_unlock(&file->lock);
    return len==512?(void*)dsp:(kfree(dsp),NULL);
}
CreateFunctionWithArgs(bool,Write,void*ptr){
    struct DSP*dsp=ptr;
    if(!dsp->Overwrite)return false;
    struct DSMF*file=Get(dsp->ID);
    if(!file)return false;
    loff_t offset=dsp->Sector<<9;
    mutex_lock(&file->lock);
    ssize_t len=kernel_write(file->connection,dsp->Buffer,512,&offset);
    int res=vfs_fsync(file->connection,0);
    mutex_unlock(&file->lock);
    return len==512&&res==0;
}
CreateFunctionWithArgs(bool,Update,u16 ID){
    struct DSMF* file = Get(ID);
    if (!file) return false;
    loff_t offset=0; 
    mutex_lock(&file->lock);
    ssize_t len = kernel_write(file->connection, file->Data, 512, &offset);
    int res = vfs_fsync(file->connection, 0);
    mutex_unlock(&file->lock);
    return len==512&&res==0;
}

CreateAction(End){
    struct DSMF*file,*tmp;
    list_for_each_entry_safe(file,tmp,&dSMF,list){
        filp_close(file->connection,NULL);
        list_del(&file->list);
        kfree(file);
    }
}
WeMakeSoftwareRun(DeviceStorageManagerFile,&End,Bind(Read),Bind(Write),Bind(Update),Bind(List)){
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
        u64 sectors=i_size_read(file_inode(connection)) >> 9;
        loff_t offset=0;
        kernel_read(file->connection,file->Data,512,&offset);
        list_add_tail(&file->list,&dSMF);
        GetDeviceStorageManagerSystem()->Init((void*)file,sectors);
    }
}