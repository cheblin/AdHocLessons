
#include "Utils_.hpp"
namespace org
{
    namespace company
    {
        namespace some_namespace
        {





            //#######################                 ClientServerLink                       ##################################
            /*
            	static <CHANNEL> * from(Receiver * receiver){}

            */
            template< typename CHANNEL >
            struct ClientServerLink
            {
                ClientServerLink()
                {
                    receiver.dispatch = dispatch;
                }

                Receiver receiver{};


                /*
                void on_FirstPack(  ){}
                */
                static Meta const * dispatch(Receiver * receiver, size_t id, Pack * pack)
                {
                    CHANNEL * channel = CHANNEL::from(receiver);
                    using namespace org::unirail;
                    switch(id)
                    {
                        default:
                            return nullptr;
                        case 0:
                            return pack ? channel->on_FirstPack(), nullptr : &MetaInfo::meta0;
                    }
                }
                /*Push received packs bytes to the channel*/
                void  bytes_into_packs(uint8_t* src, size_t src_bytes) {  ::receive_adv(src, src_bytes, & receiver);}

            };

        }
    }
}
