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
