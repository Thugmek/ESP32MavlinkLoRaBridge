#include "mavlink_packet.hpp"
#include <iostream>
#include <string>

MavlinkPacket::MavlinkPacket(): status(MAVLINK_OK)
{    
}

Mavlink2Packet::Mavlink2Packet(const uint8_t* data, uint16_t d_len)
{
    status = MAVLINK_OK;
    if(data[0] != MAVLINK2_MAGIC){
        status = MAVLINK_MAGIC_NOK;
        return;
    }
    if(d_len < 11){
        status = MAVLINK_LEN_NOK;
        return;
    }
    len = data[1];
    incompat_flags = data[2];
    has_signature = (incompat_flags & MAVLINK_IFLAG_SIGNED);
    uint16_t required_len = len + 12 + has_signature * 13;
    if(required_len > d_len){
        status = MAVLINK_LEN_NOK;
        return;
    }
    compat_flags = data[3];
    seq = data[4];
    sysid = data[5];
    compid = data[6];
    msgid = (data[9] << 16) + (data[8] << 8) + data[7];
    for(int i=0; i<len; i++){
        payload[i] = data[10+i];
    }
    checksum = (data[11+len] << 8) + data[10+len];
    if(has_signature){
        for(int i = 0;i<13;i++){
            signature[i] = data[len+12+i];
        }
    }
}

#ifdef PLATFORM_LINUX
std::string MavlinkPacket::statusToString()
{
    switch(status){
        case MAVLINK_OK:
            return "OK";
        case MAVLINK_MAGIC_NOK:
            return "MAGIC_NOK";
        case MAVLINK_LEN_NOK:
            return "LEN_NOK";
        case MAVLINK_CHECKSUM_NOK:
            return "CHECKSUM_NOK";
        case MAVLINK_OTHER_NOK:
            return "OTHER_NOK";
        default:
            return "undefined";
    }
}

void MavlinkPacket::debug()
{
    std::cout << "Packet status: " << statusToString() << "\n";
}

void Mavlink2Packet::debug()
{
    std::cout << "Packet status: " << statusToString() << "\n"
              << "\tLen:            " << (int)len << "\n"
              << "\tincompat_flags: " << (int)incompat_flags << "\n"
              << "\tcompat_flags:   " << (int)compat_flags << "\n"
              << "\tseq:            " << (int)seq << "\n"
              << "\tsysid:          " << (int)sysid << "\n"
              << "\tcompid:         " << (int)compid << "\n"
              << "\tmsgid:          " << (int)msgid << "\n"
              << "\tpayload:        ["
    ;
    for(int i=0; i<len;i++){
        std::cout << (int)payload[i] << ((i==len-1) ? "":", ");
    }
    std::cout << "]\n"
              << "\tChecksum:       " << (int)checksum << "\n";
    if(has_signature){
        std::cout << "\tSignature:      [";
        for(int i=0; i<13;i++){
            std::cout << (int)signature[i] << ", ";
        }
        std::cout << "\n";
    }
}
#endif