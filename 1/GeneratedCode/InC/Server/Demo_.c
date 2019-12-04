
#include "Server.h"
#include <assert.h>
#include <stddef.h>

void host_event(uint32_t place, Receiver* receiver, Transmitter* transmitter, Pack* pack, HOST_EVENT event) { if(pack) free_pack(pack) ;}

static size_t     some_size_t    = 0;



typedef struct
{
    c_ClientServerLink channel;

} c_ClientServerLink_DEMO;


static inline void  ClientServerLink_DEMO_on_FirstPack(c_ClientServerLink_DEMO * channel)
{
}
static inline Meta const * ClientServerLink_DEMO_dispatcher(Receiver* receiver, size_t id, Pack* pack)
{
    c_ClientServerLink_DEMO * channel = (c_ClientServerLink_DEMO *)((uint8_t*)receiver - offsetof(c_ClientServerLink_DEMO, channel) - offsetof(c_ClientServerLink, receiver));
    c_ClientServerLink_DISPATCHER(ClientServerLink_DEMO)
}




int main()
{
    static CURSORS(cur);
    c_ClientServerLink_DEMO ClientServerLink_instance = { .channel.receiver.dispatch = ClientServerLink_DEMO_dispatcher  };
    return 0;
}
