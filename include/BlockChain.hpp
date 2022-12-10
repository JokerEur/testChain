#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "Hash.hpp"

using json = nlohmann::json;


class BlockChain{

    public:
        BlockChain(uint64_t genesis = 1);
        Block getBlock(uint64_t index);
        inline const uint64_t getNumOfBlocks() const { return this->blockchain.size();};
        uint64_t addBlock(uint64_t index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> &merkle); 
        inline std::string getLastBlockHash() { return this->blockchain.at(blockchain.size() - 1)->getCurrentHash(); };
        std::string toJSON();
        uint64_t replaceChain(json chain); 
        
    private:
         std::vector<std::unique_ptr<Block>> blockchain;

};
