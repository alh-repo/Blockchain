Blockchain 

This is a blockchain built to tokenize a Real Estate Asset and record its 
title history.  Following the bitcoin design this blockchain is optimized via 
a merkle tree data structure. 

A Merkle Tree is a data structure used in blockchain technology to efficiently 
and securely verify the integrity of data. 
It organizes transactions in a tree-like structure where each leaf node 
represents a transaction's hash, and each non-leaf node represents the hash of 
its child nodes.

FEATURES

Efficiency: Quickly verify large data sets.  
Integrity: Ensure data has not been tampered with.  
Scalability: Handle large numbers of transactions.

HOW IT WORKS

Leaf Nodes: Each transaction's hash is a leaf node.  
Parent Nodes: Combine hashes of two child nodes and hash them to create a parent
node.  
Root Hash: The topmost node, called the Merkle Root, represents the entire data
set.

USAGE IN BLOCKCHAIN

Verify Transactions: Quickly check if a transaction is part of the block.  
Improve Security: Detect any changes to the transaction data.

The application default is for one transaction per block but it is easily 
modified to accept multiple transactions per block. 
See code comments in Blockchain.cpp for more details.