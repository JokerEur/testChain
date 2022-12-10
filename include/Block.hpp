#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Block final{

public:
    Block() = delete;
    Block(int index, std::string prevHas, std::string hash, std::string nonce, std::vector<std::string> data);
    inline const std::string getPreviousHash() const { return this->previousHash;};
    inline const std::string getCurrentHash() const { return this->blockHash;};
    inline const uint64_t getIndex() const {return this->index;};
    std::vector<std::string> getData() {return this->data;};
    
    void toString();
    json toJSON();
private:
    uint64_t index{};
    std::string previousHash;
    std::string blockHash;
    std::string nonce;
    std::vector<std::string> data;
};