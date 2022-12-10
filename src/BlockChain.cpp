#include "include/BlockChain.hpp"

BlockChain::BlockChain(uint64_t genesis){
    if (genesis == 0) {
        std::vector<std::string> v;
        v.push_back("Genesis Block!");
        auto hash_nonce_pair = findHash(0,string("00000000000000"),v);
    
        this -> blockchain.push_back(std::make_unique<Block>(0,string("00000000000000"),hash_nonce_pair.first,hash_nonce_pair.second,v));
        printf("Created blockchain!\n");
    }
}


Block BlockChain::getBlock(uint64_t index) {
    for (ptrdiff_t i{0}; i < blockchain.size(); ++i ){
        if (blockchain.at(i)->getIndex() == index) {
            return *(blockchain.at(i));
        }
    }
    throw invalid_argument("Index does not exist.");
}

uint64_t BlockChain::addBlock(uint64_t index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> &merkle) {
    string header = to_string(index) + prevHash + getMerkleRoot(merkle) + nonce;
    if ( (!sha256(header).compare(hash)) && (hash.substr(0,2) == "00" ) && (index == blockchain.size())) {
        printf("Block hashes match --- Adding Block %s \n",hash.c_str());
        this->blockchain.emplace_back(std::make_unique<Block>(index,prevHash,hash,nonce,merkle));
        return 1;
    }
    cout << "Hash doesn't match criteria\n";
    return 0;
}

std::string BlockChain::toJSON() {
    json j;
    j["length"] = this->blockchain.size();
    for (ptrdiff_t i{0}; i < this->blockchain.size(); ++i){
        j["data"][this->blockchain.at(i)->getIndex()] = this->blockchain.at(i)->toJSON();
    }
    return j.dump(3);
}


int BlockChain::replaceChain(json chain) {
    while (this->blockchain.size() > 1){
        this->blockchain.pop_back();
    }
    for (ptrdiif_t a{1}; a <chain["length"].get<int>(); ++a ){
        auto block = chain["data"][a];
        std::vector<std::string> data = block["data"].get<std::vector<std::string> >();
        this->addBlock(block["index"],block["previousHash"],block["hash"],block["nonce"],data);
    } 
    return 1;
}