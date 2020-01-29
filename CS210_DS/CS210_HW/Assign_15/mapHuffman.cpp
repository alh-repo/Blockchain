#include <bits/stdc++.h>
using namespace std;

bool TRACE=true;

class Node {
public:
	int	 freq;
	char val;
	string code;
	Node *left, *right;
	Node():left(nullptr), right(nullptr), freq(0), val('_'){} };

class Huffman {
	class cmp {
		public: bool operator() (const Node* a, const Node* b) const 
		{ return  a->freq > b->freq; } };
	class cmp1 {
		public: bool operator() (const Node* a, const Node* b) const 
		{ return  a->freq < b->freq; } };
	Node* root=nullptr;
	priority_queue<Node*, vector<Node*>, cmp> Q;
	priority_queue<Node*, vector<Node*>, cmp1> output;
	vector<Node> list;
 
public:
	Huffman(){}
	void add( int freq, char val ) {
		Node* node = new Node();
		node->freq = freq;
		node->val =val;
		Q.push(node);
	}
		
	void build() {
        while (Q.size() > 1) {
            Node* first = Q.top(); Q.pop();
            Node* second = Q.top(); Q.pop();
            Node* tmp = new Node();
            tmp->val = '_';
            tmp->freq = first->freq + second->freq;
            tmp->left = first;
            tmp->right = second;
            if(TRACE) { root=tmp; draw(); }
            Q.push(tmp);
		}
		root=Q.top();
	}
	void show() {
		if(!root) return;
		show(root, "");
		cout << "\nThe sorted Huffman code list: "<< endl;
		while(output.size()>0){
			Node* temp = output.top(); 
			cout << temp->val << " " << temp-> freq << " " << temp-> code << endl;
			output.pop();
		}
	}
	void show(Node* node, string coding) {
		if (!node)  return;
		if (node->val != '_') {
			Node* tmp = node;
			tmp->val = node->val;
			tmp->freq = node->freq;
			tmp->code = coding;
			output.push(tmp);
			cout << tmp->val <<" " << tmp->freq <<" "<< tmp->code << endl;
			return;
		}
		show(node->left, coding + "0");
		show(node->right, coding + "1");
	}
	void draw() const {
		if(!root) return;
		cout << endl;
		draw(root, " ", " ", "");
		cout << endl;
	}
	void draw(Node* treePtr, string lpad, string rpad, string coding) const {
        string pad = lpad.substr(0, lpad.size() - 1);
        if (treePtr == nullptr)	return;
        draw(treePtr->right, rpad + "    |", rpad + "     ", coding + "1");
        cout << pad << "+--" << setw(3) << treePtr->freq << treePtr->val << coding << endl;
        draw(treePtr->left, lpad + "     ", lpad + "    |", coding + "0");
    }
};

int main () {
    string input;
    cout << "Enter a text string: "; // the ai is hot, iot is not, iota is   
    getline(cin, input);
	
    // map<char, int> freq = { {'A', 2}, {'E', 1}, {'H', 2}, {'I', 6}, 
    // 						{'N', 1}, {'O', 4}, {'S', 3}, {'T', 5} };
    map<char, int> freq;
    // Instead you can process the input words here 
    for (auto ch:input) {
		ch = tolower(ch);
		if( !isalpha(ch)) continue;
		if (!freq[ch]) freq[ch] = 1;
        else freq[ch]++; }
	
	Huffman H;
	multimap<int, char, std::greater<int>> Occur;
    for (auto ch:freq) {
        Occur.insert(pair<int, char>(ch.second, ch.first));
    	H.add( ch.second, ch.first ); }
    	
    for (auto i:Occur)
        cout << "[" << i.first << "]->" << i.second << endl;

	H.build();
	H.show();
	return 0;
}
