#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "Hash.hpp"
#include "../common.hpp"
#include "Block.hpp"

using json = nlohmann::json;

class Block;

class BlockChain{

    public:
        BlockChain(int genesis = 1);
        Block getBlock(int index);
        inline int getNumOfBlocks() { return this->blockchain.size();};
        int addBlock(int index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> &merkle); 
        inline std::string getLastBlockHash() { return this->blockchain.at(blockchain.size() - 1)->getCurrentHash(); };
        std::string toJSON();
        int replaceChain(json chain); 
        
    private:
         std::vector<std::unique_ptr<Block>> blockchain;

};


// BlockChain::BlockChain(int genesis){
//     if (genesis == 0) {
//         std::vector<std::string> v;
//         v.push_back("Genesis Block!");
//         auto hash_nonce_pair = findHash(0,std::string("00000000000000"),v);
    
//         this -> blockchain.push_back(std::make_unique<Block>(0,std::string("00000000000000"),hash_nonce_pair.first,hash_nonce_pair.second,v));
//         printf("Created blockchain!\n");
//     }
// }


// Block BlockChain::getBlock(int index) {
//     for (ptrdiff_t i{0}; i < blockchain.size(); ++i ){
//         if (blockchain.at(i)->getIndex() == index)
//             return *(blockchain.at(i));
//     }
//     throw std::invalid_argument("Index does not exist.");
// }

// int BlockChain::addBlock(int index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> &merkle) {
//     std::string header = std::to_string(index) + prevHash + getMerkleRoot(merkle) + nonce;
//     if ( (!sha256(header).compare(hash)) && (hash.substr(0,2) == "00" ) && (index == blockchain.size())) {
//         printf("Block hashes match --- Adding Block %s \n",hash.c_str());
//         this->blockchain.emplace_back(std::make_unique<Block>(index,prevHash,hash,nonce,merkle));
//         return 1;
//     }
//     std::cout << "Hash doesn't match criteria\n";
//     return 0;
// }

// std::string BlockChain::toJSON() {
//     json j;
//     j["length"] = this->blockchain.size();
//     for (ptrdiff_t i{0}; i < this->blockchain.size(); ++i){
//         j["data"][this->blockchain.at(i)->getIndex()] = this->blockchain.at(i)->toJSON();
//     }
//     return j.dump(3);
// }


// int BlockChain::replaceChain(json chain) {
//     while (this->blockchain.size() > 1){
//         this->blockchain.pop_back();
//     }
//     for (int a{1}; a < chain["length"].get<int>() ; a++){
//         auto block = chain["data"][a];
//         std::vector<std::string> data = block["data"].get<std::vector<std::string> >();
//         this->addBlock(block["index"],block["previousHash"],block["hash"],block["nonce"],data);
//     } 
//     return 1;
// }
