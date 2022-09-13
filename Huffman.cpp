/*
Huffman coding
Created on Thu Apr 14 13:59:01 2022
@author: Dr. Olcay Kursun, Spring 2022, AUM Dept. of Computer Science
*/

#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct TreeNode {

    string val;
    int freq;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string x, int f) : val(x), freq(f), left(nullptr), right(nullptr) {}
    TreeNode(TreeNode* l, TreeNode* r) : val(""), freq(l->freq + r->freq), left(l), right(r) {}
};

class LessFrequent {   //returns true if lhs has lower priority than rhs
public:
    bool operator()(TreeNode*& p1, TreeNode*& p2) const { return p1->freq > p2->freq; };
};

void printHuffmanTree(TreeNode* root, string s)
{
    if (root != nullptr)
    {
        if (root->val != "")
            cout << root->val << " " << s << "\n";
        printHuffmanTree(root->left, s + "0");
        printHuffmanTree(root->right, s + "1");
    }
}

int main()
{
    priority_queue<TreeNode*, vector<TreeNode*>, LessFrequent> q;

    //Example is picked from Chapter 12 of Goodrich's book
    q.push(new TreeNode("_", 9));
    q.push(new TreeNode("a", 5));
    q.push(new TreeNode("b", 1));
    q.push(new TreeNode("d", 3));
    q.push(new TreeNode("e", 7));
    q.push(new TreeNode("f", 3));
    q.push(new TreeNode("h", 1));
    q.push(new TreeNode("i", 1));
    q.push(new TreeNode("k", 1));
    q.push(new TreeNode("n", 4));
    q.push(new TreeNode("o", 1));
    q.push(new TreeNode("r", 5));
    q.push(new TreeNode("s", 1));
    q.push(new TreeNode("t", 2));
    q.push(new TreeNode("u", 1));
    q.push(new TreeNode("v", 1));

    while (q.size() > 1)
    {
        TreeNode* l = q.top();
        q.pop();
        TreeNode* r = q.top();
        q.pop();
        q.push(new TreeNode(l, r));
    }

    TreeNode* huffmanTree = q.top();

    printHuffmanTree(huffmanTree, "");
};
