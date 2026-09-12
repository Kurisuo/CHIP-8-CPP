#include "chip-8.hpp"

//Constructor
CHIP_8::CHIP_8(){

    PC = ST_ADDRESS; 

}

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
    std::streamoff ROM_size = file_end - std::streampos{0};

    if(ROM_size > REMAINDER || ROM_size < 0){
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