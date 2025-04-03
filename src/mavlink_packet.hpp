#include <cstdint>
#include <string>

#define MAVLINK1_MAGIC 0xFE
#define MAVLINK2_MAGIC 0xFD

#define MAVLINK_IFLAG_SIGNED 0x01

enum PacketStatus{
    MAVLINK_OK,
    MAVLINK_MAGIC_NOK,
    MAVLINK_LEN_NOK,
    MAVLINK_CHECKSUM_NOK,
    MAVLINK_OTHER_NOK
};

class MavlinkPacket{
    protected:
        enum PacketStatus status;
    public:
        MavlinkPacket();
#ifdef PLATFORM_LINUX
        virtual void debug();
        std::string statusToString();
#endif
};

class Mavlink2Packet : public MavlinkPacket{
    private:
        uint8_t len;
        uint8_t incompat_flags;
        uint8_t compat_flags;
        uint8_t seq;
        uint8_t sysid;
        uint8_t compid;
        uint32_t msgid;
        uint8_t payload[255];
        uint16_t checksum;
        bool has_signature;
        uint8_t signature[13];
    public:
#ifdef PLATFORM_LINUX
        Mavlink2Packet(const uint8_t* data, uint16_t len);
        void debug() override;
#endif
};

class Mavlink1Packet : public MavlinkPacket{
    private:
        uint8_t len;
        uint8_t seq;
        uint8_t sysid;
        uint8_t compid;
        uint8_t msgid;
        uint8_t payload[255];
        uint16_t checksum;
    public:
#ifdef PLATFORM_LINUX
        Mavlink1Packet(uint8_t* data, uint16_t len);
        //void debug();
#endif
};