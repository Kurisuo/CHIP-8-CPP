#include <stdint.h>
#include <fstream>
#include <filesystem>
#include <array>
#include <cstdio>


static constexpr unsigned int MEM_SIZE = 4096;
static constexpr unsigned int ST_ADDRESS = 0x200; //known at compile time
static constexpr unsigned int REMAINDER = MEM_SIZE - ST_ADDRESS;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

class CHIP_8 {
    public:
       
        bool LoadROM(const std::filesystem::path& filename); 
        
    private: 
        std::array<u8, 16> registers {}; //16 8-bit registers
        std::array<u8, 4096> memory  {}; //4096 Bytes of Memory
        u16 PC                       {}; //program counter
        u16 index_register           {}; //store mem addresses
        std::array<u16, 16> stack    {}; //16 Stack
        u8 SP                        {}; //stack-pointer
        u8 delay_timer               {}; //delay-timer
        u8 sound_timer               {}; //sound-timer
        std::array<u8, 16> inp_keys  {}; //input-keys
        std::array<u32, 64 * 32> vid {}; //display-video
        u16 opcode;


};