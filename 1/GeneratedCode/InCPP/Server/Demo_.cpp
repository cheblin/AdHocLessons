#include "Server.hpp"
#include <cassert>

void host_event(uint32_t place, Receiver* receiver, Transmitter* transmitter, Pack* pack, HOST_EVENT event) { if(pack) free_pack(pack) ;}

static size_t     some_size_t    = 0;

using namespace  org::company::some_namespace;
void on_FirstPack() {}

struct ClientServerLink_demo
{
    ClientServerLink<ClientServerLink_demo> channel;
    void on_FirstPack()
    {
        ::on_FirstPack();
        printf("FirstPack pass\n");
    }
    static  ClientServerLink_demo * from(Receiver * receiver)
    {
        return reinterpret_cast<ClientServerLink_demo*>(reinterpret_cast<uint8_t*>(receiver) - offsetof(ClientServerLink_demo, channel) - offsetof(ClientServerLink<ClientServerLink_demo>, receiver));
    }

};


int main()
{
    CURSORS(cur);
    uint8_t buffer[512];
    int bytes_out ;
    ClientServerLink_demo _ClientServerLink{};
    _ClientServerLink.channel.bytes_into_packs(buffer, 512); // receiving bytes
}
