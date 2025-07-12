#include "RFC768.h"
static void RFC791Receiver(struct Packet*packet,struct RFC791NetworkAddress*client,struct RFC791NetworkAddress*server) {

}
static void RFC8200Receiver(struct Packet*packet,struct RFC8200NetworkAddress*client,struct RFC8200NetworkAddress*server) {
 
}
End{}
Start(RFC768, Bind(RFC791Receiver),Bind(RFC8200Receiver)){}