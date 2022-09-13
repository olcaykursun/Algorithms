/*
Generating random binary trees
Created on Sat Mar 26 14:19:10 2022
@author: Dr. Olcay Kursun, AUM Dept. of Computer Science
*/

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    string val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string x) : val(x), left(nullptr), right(nullptr) {}
};

bool operator==(const TreeNode& lhs, const TreeNode& rhs)
{
    return lhs.val == rhs.val
        && ((lhs.left == nullptr && rhs.left == nullptr)
            || (lhs.left != nullptr && rhs.left != nullptr && *lhs.left == *rhs.left))
        && ((lhs.right == nullptr && rhs.right == nullptr)
            || (lhs.right != nullptr && rhs.right != nullptr && *lhs.right == *rhs.right));
}

TreeNode* createBinaryTree(int treeSize, int key = 1)
{
    if (treeSize == 0)
        return nullptr;
    TreeNode* root = new TreeNode(to_string(key));
    int leftSize = rand() % treeSize;
    int rightSize = treeSize - (leftSize + 1);
    root->left = createBinaryTree(leftSize, key + 1);
    root->right = createBinaryTree(rightSize, key + leftSize + 1);
    return root;
}

int computeTreeHeight(TreeNode* t)
{
    if (t == nullptr)
        return -1;
    return int(max({ computeTreeHeight(t->left), computeTreeHeight(t->right) }))+1;
}

int catalanNumber(int n)
{
    if (n == 0)
        return 1;
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += catalanNumber(i) * catalanNumber(n - i - 1);
    }
    return res;
}


int main()
{
    srand(time(NULL));
    int numNodesCreated;
    int numRandomTrees;

    cout << "Enter the number of nodes and the number of random trees to generate: ";
    //Make sure random tree number is large enough otherwise it may not generate all possibilities

    cin >> numNodesCreated >> numRandomTrees;
    vector<TreeNode*> trees;

    int* heights = new int[numNodesCreated - 1];
    for (int i = 0; i < numNodesCreated; i++)
        heights[i] = 0;

    for (int i = 0; i < numRandomTrees; i++)
    {
        TreeNode* myTree = createBinaryTree(numNodesCreated);
        bool isNewTree = true;
        for (const auto& tree : trees)
        {
            if (*tree == *myTree)
            {
                isNewTree = false;
                break;
            }
        }
        int newHeight = computeTreeHeight(myTree);
        ++heights[newHeight];
        if (isNewTree)
        {
            trees.push_back(myTree);
        }
    }
    cout << trees.size() << " unique trees are found!\n";
    cout << "n-th Catalan number is " << catalanNumber(numNodesCreated) << "\n";

    for (int i = 0; i < numNodesCreated; i++)
        cout << i << ": " << double(heights[i])/numRandomTrees << "\n";

};
