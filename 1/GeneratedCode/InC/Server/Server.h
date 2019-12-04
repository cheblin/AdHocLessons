
#ifdef __cplusplus
extern "C"
{
#endif


#pragma once

#include "Utils_.h"




//#######################                 c_ClientServerLink                       ##################################
typedef struct
{
    Receiver receiver;

} c_ClientServerLink;


/*
static inline Meta* dispatcher (Receiver* receiver, size_t id, Pack* pack)
{
	Channel * channel = ...// from Receiver *  to Channel_type * converter code
	c_ClientServerLink_DISPATCHER( Channel )
}
________________________________________________________
static inline void <CHANNEL>_on_FirstPack( <Channel> * chennal ){}
*/

#define c_ClientServerLink_DISPATCHER(CHANNEL)\
		switch (id)\
		{\
			default:    return NULL;\
			case 0:	return pack ? CHANNEL##_on_FirstPack( channel ), NULL : &meta0;\
		}

static inline void    c_ClientServerLink_bytes_into_packs(uint8_t* src, size_t src_bytes, c_ClientServerLink * dst) {  receive_adv(src, src_bytes, &dst->receiver);}





#ifdef __cplusplus
}
#endif
