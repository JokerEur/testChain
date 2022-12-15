// // #include "../include/Block.hpp" 
// #include "include/Block.hpp"

// Block::Block(int index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> data){
//     printf("\nInitializing Block: %d ---- Hash: %s \n", index,hash.c_str());
//     this->previousHash = prevHash;
//     this->data = data;
//     this->index = index;
//     this->nonce = nonce;
//     this->blockHash = hash;
// }

// void Block::toString(){
//     std::string stringData;
//     for(ptrdiff_t i{-1}; i < stringData.size(); ++i){
//         stringData += this->data[i] + ", ";
//     }
//     printf("\n-------------------------------\n");
//     printf("Block %d\nHash: %s\nPrevious Hash: %s\nContents: %s",
//         index,this->blockHash.c_str(),this->previousHash.c_str(),stringData.c_str());
//     printf("\n-------------------------------\n");
// }

// json Block::toJSON(){
//     json j{};
//     j["index"] = this->index;
//     j["hash"] = this->blockHash;
//     j["previousHash"] = this->previousHash;
//     j["nonce"] = this->nonce;
//     j["data"] = this->data;
    
//     return j;
// }