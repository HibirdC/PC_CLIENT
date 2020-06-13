//
//  CTNPacket_hpp
//  TNMP
//
//  Created by 兰怀玉 on 16/4/13.
//  Copyright © 2016年 兰怀玉. All rights reserved.
//

#ifndef CTNPacket_hpp
#define CTNPacket_hpp

#include <stdio.h>

#ifdef WIN32

#include <Winsock2.h>
typedef __int32 int32;
typedef __int16 int16;

#else

#include <sys/types.h>

typedef __int32_t int32;
typedef __int16_t int16;

#endif

#define NEW_PACKET(len) ((TNPacketBuffer *)new char[len])

#define DELETE_PACKET(p) if (p != NULL) {delete [] (char*)p; p = NULL;}


const size_t TNMP_HLEN = 6;//header length

struct TNPacketBuffer{
    int32 length;//payload length
    int16 type;// CTNIMTypedef.h
    char payload[0];
    
    TNPacketBuffer(){
        length = 0;
        type  = 0;
    }
    
    void decode(){
        length = ntohl(length);
        type = ntohs(type);
    }
    
    void encode(){
        length = htonl(length);
        type = htons(type);
    }
    
    TNPacketBuffer* clone(){
        TNPacketBuffer* packetBuffer = NEW_PACKET(TNMP_HLEN + this->length);
        packetBuffer->type = this->type;
        packetBuffer->length = this->length;
        if (packetBuffer->length > 0) {
            memcpy(packetBuffer->payload, this->payload, this->length);
        }
        
        return packetBuffer;
    }
};



//TNPacketBuffer* clonePacketBuffer(TNPacketBuffer* packet){
//    if (packet == nullptr){
//        return nullptr;
//    }
//
//    TNPacketBuffer* packetBuffer = NEW_PACKET(TNMP_HLEN + packet->length);
//    packetBuffer->type = packet->type;
//    packetBuffer->length = packet->length;
//    if (packetBuffer->length > 0) {
//        memcpy(packetBuffer->payload, packet->payload, packet->length);
//    }
//
//    return packetBuffer;
//}




#endif /* CTNPacketBase_hpp */
