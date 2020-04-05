/**********************************************
 *   Adam Hennefer
 *   Latest update: 4.4.20     
 *  
 *   Simple blockchain modeling a property title report.       
 *   This setup includes one property per chain and one transaction per block
 *   but it can also handle multiple transactions per block to model a coin 
 *   based system.
 *   TODO:  Create share based system.
 ************************************************/

#include <string>
#include "../sha256.h"
#include "Blockchain.h"
using namespace std;

vector<TxData>  txList = { // 9 transactions
    {"Morgan Stanley Real Estate Paramount Group, Inc.", "Adam Leonard Hennefer", 100, "$1.00"},
    {"Adam Leonard Hennefer", "The Blackstone Group", 100, "$1,000,000,000.00"},
    {"The Blackstone Group", "Brookfield Properties", 100, "$1,100,000,000.00"},
    {"Brookfield Properties", "LaSalle Investment Management", 100, "$1,200,000,000.00"},
    {"LaSalle Investment Management", "Tishman Speyer", 100, "$1,300,000,000.00"},
    {"Tishman Speyer", "Hines", 100, "$1,400,000,000.00"},
    {"Hines", "Boston Properties", 100, "$1,500,000,000.00"},
    {"Boston Properties", "CBRE Global Investors", 100, "$1,600,000,000.00"},
    {"CBRE Global Investors", "KBS", 100, "$1,700,000,000.00"}
};

// Driver
int main() {
    vector<string> txHashVec;
    string txHash, blockData;
    
    Blockchain chain = Blockchain();

    // Use a simple loop to provide a test scenario:
    //   allow the last block to have less than magic(n) transactions.
    for( auto x:txList ) { 
        // create a txHash per transaction 
        txHash = sha256::hash256_hex_string(x.getData());
        blockData += "\ttxHash: " + txHash +"\n" + x.getData() ;
        txHashVec.push_back(txHash);
        // edit magic(1) number to make blocks of multiple transactions
        if (txHashVec.size() == 1) {
            x.merkleRoot = merkle(txHashVec);
            x.blockData = blockData;
            chain.AddBlock(x);
            txHashVec.clear();
            blockData.clear();
        }
    }
    return 0;
}