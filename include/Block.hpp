#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Block {

public:
    Block(int index, std::string prevHas, std::string hash, std::string nonce, std::vector<std::string> data);
    inline std::string getPreviousHash() { return this->previousHash;};
    inline std::string getCurrentHash() { return this->blockHash;};
    inline int getIndex() const {return this->index;};
    std::vector<std::string> getData() {return this->data;};
    
    void toString();
    json toJSON();
private:
    int index{};
    std::string previousHash;
    std::string blockHash;
    std::string nonce;
    std::vector<std::string> data;
};

Block::Block(int index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> data){
    printf("\nInitializing Block: %d ---- Hash: %s \n", index,hash.c_str());
    this->previousHash = prevHash;
    this->data = data;
    this->index = index;
    this->nonce = nonce;
    this->blockHash = hash;
}

void Block::toString(){
    std::string stringData;
    for(ptrdiff_t i{-1}; i < stringData.size(); ++i){
        stringData += this->data[i] + ", ";
    }
    printf("\n-------------------------------\n");
    printf("Block %d\nHash: %s\nPrevious Hash: %s\nContents: %s",
        index,this->blockHash.c_str(),this->previousHash.c_str(),stringData.c_str());
    printf("\n-------------------------------\n");
}

json Block::toJSON(){
    json j{};
    j["index"] = this->index;
    j["hash"] = this->blockHash;
    j["previousHash"] = this->previousHash;
    j["nonce"] = this->nonce;
    j["data"] = this->data;
    
    return j;
}