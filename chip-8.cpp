#include <stdint.h>
#include <fstream>
#include <filesystem>
#include <array>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

/*
Machine state
→ ROM loading
→ Font loading
→ Instruction decoding
→ Fetch/decode/execute loop
→ Display and input
→ Timers
→ Testing
*/

class CHIP_8 {
    public:
        //ROM Loader - Read Bytes to Binary
        static constexpr unsigned int MEM_SIZE = 4096;
        static constexpr unsigned int ST_ADDRESS = 0x200; //known at compile time
        static constexpr unsigned int REMAINDER = MEM_SIZE - ST_ADDRESS;

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

        bool LoadROM(const std::filesystem::path& filename);

};

//Load information into Memory from ROM 
//std::filesystem::path provides us with system type encoding
bool CHIP_8::LoadROM(const std::filesystem::path& filename){

    std::ifstream file_(filename, std::ios::binary | std::ios::ate); //move pointer to end to fetch size

    if(!file_){
        std::printf("Failed to: Open_File");
        return false;
    }

    std::streampos file_end = file_.tellg(); //Used to check valid size for memory  
    
    //Check for failure | streampos gets us location 
    if(std::streampos{-1} == file_end){
        std::printf("Failed to access: File_End\n");
        return false;
    }
    
    //Check for Valid ROM Size
    const auto ROM_size = static_cast<u16>(file_end);
    if(ROM_size > REMAINDER){
        std::printf("Failed at: ROM_SIZE INVALID");
        return false;
    }

    //Return to beginning   
    file_.seekg(0, std::ios::beg);
    
    if(!file_){
        std::printf("Failed at: SEEKG FAILED");
        return false;
    }

    //read file contents into memory  |access indx 1 + shift by st add | streamsize expected size to read
    file_.read(reinterpret_cast<char*>(memory.data() + ST_ADDRESS), static_cast<std::streamsize>(ROM_size));
    if(!file_){
        std::printf("Failed at: MEMORY NOT READ INTO");
        return false;
    }


    return true;
}








