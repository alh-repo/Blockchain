/**********************************************
 *   Adam Hennefer
 *   Latest update 5.20.18     
 * 
 * 
 ************************************************/
#ifndef MERKLE_H
#define MERKLE_H
using namespace std;

// Reverse inputs before and after hashing
// due to big-endian / little-endian nonsense
string reverse(string const & str) {
    assert(str.size() % 2 == 0);
    string result;
    result.reserve(str.size());
    for (size_t i = str.size(); i != 0; i -= 2)
    result.append(str, i - 2, 2);
    return result;
}

string hash2(string a, string b) {
    string a1 = reverse(a);
    string b1 = reverse(b);
    string h = sha256::hash256_hex_string(a1+b1);
    h = sha256::hash256_hex_string( h );
    return reverse(h); 
}

// Hash pairs of items recursively until a single value is obtained
string merkle(vector<string> hashList) {
    static int level = 1;
    if (hashList.size() == 1)  return hashList[0]; 
    vector<string> newHashList;
    
    //Process pairs. For odd length, the last is skipped
    for(int i=0; i<hashList.size()-1; i=i+2) {
        string h = hash2( hashList[i], hashList[i+1] );
        newHashList.push_back(h);
    }

    if( (hashList.size() % 2) ) { // odd, hash last item twice
        string last = hashList.end()[-1];
        string h = hash2( last, last );
        newHashList.push_back(h);
    }
    
    return merkle(newHashList);
}
#endif