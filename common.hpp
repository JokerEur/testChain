#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "include/Hash.hpp"

void print_hex(const char *label, const uint8_t *v, size_t len) {
    size_t i;

    printf("%s: ", label);
    for (i = 0; i < len; ++i) {
        printf("%02x", v[i]);
    }
    printf("\n");
}

std::string getMerkleRoot(const std::vector<std::string> &merkle) {
    printf("\nFinding Merkle Root.... \n");
    if (merkle.empty())
        return "";
    else if (merkle.size() == 1){
        return sha256(merkle[0]);
    }

    std::vector<std::string> new_merkle = merkle;

    while (new_merkle.size() > 1) {
        if ( new_merkle.size() % 2 == 1 )
            new_merkle.push_back(merkle.back());

        std::vector<std::string> result;
            
        for (ptrdiff_t i{0}; i < new_merkle.size(); i += 2){
            std::string var1 = sha256(new_merkle[i]);
            std::string var2 = sha256(new_merkle[i+1]);
            std::string hash = sha256(var1+var2);
            result.emplace_back(hash);
        }
        new_merkle = result;
    }
    return new_merkle.at(0);

}

std::pair<std::string,std::string> findHash(uint64_t index, std::string prevHash, std::vector<std::string> &merkle) {
    std::string header = std::to_string(index) + prevHash + getMerkleRoot(merkle);
    unsigned int nonce;
    for (nonce = 0; nonce < 100000; nonce++ ) {
        std::string blockHash = sha256(header + std::to_string(nonce));
        if (blockHash.substr(0,2) == "00"){
            return std::make_pair(blockHash,std::to_string(nonce));
            break;
        }
    }
    return std::make_pair("fail","fail");
}