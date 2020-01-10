
#include "Server.hpp"
#include <string.h>
#include <stdio.h>
#include <assert.h>

using namespace  org::company::some_namespace;


void host_event(uint32_t place, Receiver* receiver, Transmitter* transmitter, Pack* pack, HOST_EVENT event) { if(pack) free_pack(pack) ;}

namespace org
{
    namespace unirail
    {
        namespace test
        {





            void on_FirstPack() {printf("FirstPack \n");}



            struct TEST_Channel
            {

                Pack* test_pack = nullptr;
                Transmitter transmitter{};
                static const Pack* pull_sending_pack(Transmitter* transmitter)
                {
                    Pack * pack = nullptr;
                    std::swap(pack, reinterpret_cast<TEST_Channel*>(reinterpret_cast<uint8_t*>(transmitter) - offsetof(TEST_Channel, transmitter))->test_pack);
                    return pack;
                }
                size_t  packs_into_bytes(uint8_t* dst, size_t dst_bytes) { return ::transmit(& transmitter, dst, dst_bytes);}
                size_t  packs_into_bytes_adv(uint8_t* dst, size_t dst_bytes) { return ::transmit_adv(& transmitter, dst, dst_bytes);}
                bool  send_FirstPack()  { return  test_pack ? false : (test_pack = const_cast<Pack *>(&org::unirail::MetaInfo::meta0pack), true); }





                Receiver receiver{};

                static Meta const * dispatch(Receiver * receiver, size_t id, Pack * pack)
                {
                    using namespace org::unirail;
                    switch(id)
                    {
                        default:
                            return nullptr;
                        case 0:
                            return pack ? on_FirstPack(), nullptr : &MetaInfo::meta0;
                    }
                }
                void  bytes_into_packs(uint8_t* src, size_t src_bytes) {  ::receive(src, src_bytes, &receiver);}
                void  bytes_into_packs_adv(uint8_t* src, size_t src_bytes) {  ::receive_adv(src, src_bytes, &receiver);}

                TEST_Channel()
                {
                    transmitter.pull = pull_sending_pack;
                    receiver.dispatch = dispatch;
                }

            };





            struct ClientServerLink_test
            {
                ClientServerLink<ClientServerLink_test> channel;
                void on_FirstPack()
                {
                    ::org::unirail::test::on_FirstPack();
                    printf("FirstPack pass\n");
                }
                static  ClientServerLink_test * from(Receiver * receiver)
                {
                    return reinterpret_cast<ClientServerLink_test*>(reinterpret_cast<uint8_t*>(receiver) - offsetof(ClientServerLink_test, channel) - offsetof(ClientServerLink<ClientServerLink_test>, receiver));
                }

            };

        }

    }
}

int main()
{
    using namespace org::unirail::test;
    static uint8_t buff[512];
    CURSORS(cur);
    CURSORS(cur_dst);
    CURSORS(cur_src);
    ClientServerLink_test ch_ClientServerLink{};
    TEST_Channel ch_TEST_Channel{};
    {
        if(ch_TEST_Channel.send_FirstPack())
            for(size_t len; (len = ch_TEST_Channel.packs_into_bytes_adv(buff, sizeof buff));)
                ch_ClientServerLink.channel.bytes_into_packs(buff,  len);
        else  assert("error AD_HOC_FAILURE_SENDING_QUEUE_OVERFLOW");
    }
}

