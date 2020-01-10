
#include "Server.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

void host_event(uint32_t place, Receiver* receiver, Transmitter* transmitter, Pack* pack, HOST_EVENT event) { if(pack) free_pack(pack) ;}


typedef struct
{

    c_ClientServerLink channel;
} c_ClientServerLink_TEST;







/**
 * send FirstPack
 * param SEND function name with signature bool (c_TEST_Channel * dst, Pack* pack)
 * param c_TEST_Channel * pointer to channel that contains transmitter
 * return true if add pack to the sending queue succeed
 */
#define c_TEST_Channel_send_FirstPack(SEND, c_TEST_Channel) ( SEND ( c_TEST_Channel , (Pack *)&meta0pack) )


typedef struct
{
    Pack * test_pack;
    Transmitter transmitter;

} c_TEST_Channel;
bool TEST_Channel_send(c_TEST_Channel * dst, Pack  * const pack) { return dst->test_pack ? false : (dst->test_pack = pack), true;}

const Pack * TEST_Channel_pull(Transmitter * transmitter)
{
    c_TEST_Channel * ch = (c_TEST_Channel *)((uint8_t*)transmitter - offsetof(c_TEST_Channel, transmitter));
    Pack * pack = ch->test_pack;
    ch->test_pack = NULL;
    return pack;
}

















static inline void  ClientServerLink_TEST_on_FirstPack(c_ClientServerLink_TEST * channel)
{
    printf("on_FirstPack \n");
}
static inline Meta const * ClientServerLink_TEST_dispatcher(Receiver* receiver, size_t id, Pack* pack)
{
    c_ClientServerLink_TEST * channel = (c_ClientServerLink_TEST *)((uint8_t*)receiver - offsetof(c_ClientServerLink_TEST, channel) - offsetof(c_ClientServerLink, receiver));
    c_ClientServerLink_DISPATCHER(ClientServerLink_TEST)
}



int main()
{
    static uint8_t buff[512];
    c_TEST_Channel TEST_Channel_instance = { .transmitter.pull = TEST_Channel_pull  };
    c_ClientServerLink_TEST ClientServerLink_instance = { .channel.receiver.dispatch = ClientServerLink_TEST_dispatcher  };
    {
        c_TEST_Channel_send_FirstPack(TEST_Channel_send, &TEST_Channel_instance);
        for(size_t len; (len = transmit_adv(&TEST_Channel_instance.transmitter, buff, sizeof buff));)
            c_ClientServerLink_bytes_into_packs(buff,  len, &ClientServerLink_instance.channel);
    }
}

