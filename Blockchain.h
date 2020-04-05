/**********************************************
 *   Adam Hennefer
 *   Latest update: 4.4.20     
 *  
 * 
 ************************************************/

#ifndef _BLOCKCHAIN_H
#define _BLOCKCHAIN_H
#include <vector>
#include <iomanip>
#include <string>
#include <iostream>
#include "Merkle.h"
using namespace std;

struct TxData {
    string from, to, data, merkleRoot, blockData;
    int stake;
    TxData() : from(""), to(""), data("\n\tProperty:\n"
                                    "\tAddress: 1 Market Plaza\n"
                                    "\tCounty: San Francisco\n"
                                    "\tState: CA\n"
                                    "\tPropety Type: Commercial - General Office\n"
                                    "\tSize: 1,600,000 square feet\n"
                                    "\tLot Size: 2.6 Acre\n"
                                    "\tYear Built: 1979\n"
                                    "\tParking: 162") {
        blockData+="\t"+from+" "+to+" "+" "+data+"\n";
    }
    TxData(std::string from, std::string to, int stake, std::string data)
        : from(from), to(to), stake(stake), data(data) {
            blockData+=from+" "+to+" "+std::to_string(stake)+" "+data;
    }
    ~TxData() {}
    string getData() { return "\tSold From: " + from +
                                "\n\tSold To: " + to +
                                "\n\tOwnership Share: " + std::to_string(stake) +
                                "\n\tPrice: " + data + "\n";
    }
    public:
    bool valid(){ if(stake < 50) return false; }
    //void PrintData() { std::cout << getData(); }
};

class Block {
    int index, nounce;
    std::time_t timestamp;
    TxData data; // trasaction record
    std::string merkle_hash, previous;

public:
    Block() {}
    Block(int index, TxData data, std::string previous);
    ~Block() {}
    string toString();
    std::time_t getTimestamp() { return timestamp; }
    TxData* getData() { return &data; }
    string getHash() { 
        // if (previous=="") return "N/A";
        return merkle_hash; }
};

//Block Constructor
Block::Block(int index, TxData data, std::string p=""):
    index(index), data(data), timestamp(std::time(nullptr)), previous(p) {
    nounce = 0;
    do {
        merkle_hash = sha256::hash256_hex_string(
                std::to_string(index) +
                std::to_string(timestamp) +
                data.merkleRoot +
                previous + 
                std::to_string(nounce++)
                );
        
    } while( merkle_hash.substr(0,1) != "0" );
}

string Block::toString() {
    return std::to_string(index) + "\n" +
        "nounce: " + std::to_string(nounce) + "\n" +
        "Previous hash: " + previous + "\n" +
        "Timestamp: " + std::asctime(std::gmtime(&timestamp)) + 
        "Data: {\n" + data.blockData + "}\n" +
        "Merkle hash: " + merkle_hash + "\n";
}

class Blockchain {
    std::vector<Block> blocks;
    Block* current;
public:
    Blockchain() {
        blocks.push_back(Block(0, TxData(), ""));
        current = &(blocks[0]);
        cout << "Created Blockchain\nAdded Block: " << current->toString() << endl;
    }
    ~Blockchain() {}
    void AddBlock(TxData data);
};

void Blockchain::AddBlock(TxData data) {
    if(data.stake <= 100 &&  blocks.size() == 1  ){
        blocks.push_back( Block(blocks.size(), data, current->getHash() ));
        current = &(blocks.back());
        cout << "Added Block: " << current->toString() << endl;
    }
    else if(data.stake <= 100 && blocks.size() > 1 
        && current->getData()->to == data.from  ){
            blocks.push_back( Block(blocks.size(), data, current->getHash() ));
            current = &(blocks.back());
            cout << "Added Block: " << current->toString() << endl;
    }else{
        cout << "Block addition denied.\nTransaction invalid.\n" << endl;
    }
}
#endif