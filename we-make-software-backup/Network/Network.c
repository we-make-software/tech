#include "Network.h"
static u16 ChecksumCalculator(struct Checksum*checksums,u8 size) {
    u32 total=0;
    for(u8 i=0;i<size;i++){
        struct Checksum*checksum=&checksums[i];
        for (u16 j=0;j<checksum->Length; j++)
           total+=ToHost16(checksum->Data[j]);
    }
    while(total>>16)
        total=(total&65535)+(total>>16);
    return (u16)(~total);
}
    /*
    SystemLibrary(NetworkLayer) {
    struct NetworkLayer*(*GetNetworkLayer)(struct NetworkAddress*);
    bool(*Add)(struct NetworkLayer*,void*);
    bool(*Remove)(struct NetworkLayer*,u16);
    void(*Lock)(struct NetworkLayer*);
    void(*Unlock)(struct NetworkLayer*);
    struct NetworkAddress*(*GetVersion4)(u32);
    struct NetworkAddress*(*GetVersion6)(u64,u64);
    bool(*AllowedToSend)(struct NetworkLayer*);
    
};
    */
   static struct LayerDataPointer*GetLayerDataPointer(struct NetworkLayer*networkLayer,u16 ID) {
    if(!networkLayer)return NULL;
    struct LayerDataPointer*dataPointer=NULL,*temp=NULL;
    list_for_each_entry(temp,&networkLayer->data,data) {
        if(temp->ID==ID) {
            dataPointer=temp;
            break;
        }
    }
    return dataPointer;
}
static bool AddLayerDataPointer(struct NetworkLayer*networkLayer,void*VoidLayerDataPointer) {
    if(!networkLayer||!VoidLayerDataPointer)return false;
    struct LayerDataPointer*layerDataPointer=(struct LayerDataPointer*)VoidLayerDataPointer;
    struct LayerDataPointer*dataPointer=GetLayerDataPointer(networkLayer,layerDataPointer->ID);
    if(dataPointer)return false;
    mutex_lock(&networkLayer->lock);
    dataPointer=GetLayerDataPointer(networkLayer,layerDataPointer->ID);
    if(dataPointer){
        mutex_unlock(&networkLayer->lock);
        return false;   
    }
    list_add_tail(&layerDataPointer->data,&networkLayer->data);
    return true;
}

static void LockNetworkLayer(struct NetworkLayer*networkLayer) {
    if(!networkLayer)return;
    mutex_lock(&networkLayer->lock);
}
static void UnlockNetworkLayer(struct NetworkLayer*networkLayer) {
    if(!networkLayer)return;
    mutex_unlock(&networkLayer->lock);
}

static bool Trust(struct NetworkLayer*networkLayer){
    if(!networkLayer)return false;
    struct LayerDataPointer*dataPointer=GetLayerDataPointer(networkLayer,0);
    if(dataPointer)return ((struct NetworkConnection*)dataPointer)->trust;
    struct NetworkConnection*connection=kmalloc(sizeof(struct NetworkConnection),GFP_KERNEL);
    if(!connection)return false;
    connection->layerDataPointer.ID=0;
    connection->layerDataPointer.Destroy=NULL;
    connection->trust=true;
    INIT_LIST_HEAD(&connection->packet);
    INIT_LIST_HEAD(&connection->layerDataPointer.data);
    if(!AddLayerDataPointer(networkLayer,&connection->layerDataPointer)) {
        kfree(connection);
        return false;   
    }
    return true;
}
static bool Add(struct NetworkLayer*networkLayer,void*VoidLayerDataPointer) {
    return NULL;
}

End{}
Start(Network,
    Bind(Add)
){
    
}