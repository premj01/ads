#include <iostream>
#include <vector>
#include <limits.h>
#include <string>

using namespace std;

struct TreeNode
{
    string key;
    TreeNode *left, *right;
    TreeNode(string key) : key(key), left(nullptr), right(nullptr) {}
};

class OptimalBST
{
private:
    vector<string> keys;
    vector<int> freq;
    vector<vector<int>> cost;
    vector<vector<int>> root;

    TreeNode *buildTree(int i, int j)
    {
        if (i > j)
            return nullptr;
        int r = root[i][j];
        TreeNode *node = new TreeNode(keys[r]);
        node->left = buildTree(i, r - 1);
        node->right = buildTree(r + 1, j);
        return node;
    }

public:
    OptimalBST(vector<string> keys, vector<int> freq) : keys(keys), freq(freq)
    {
        int n = keys.size();
        cost.resize(n, vector<int>(n, 0));
        root.resize(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            cost[i][i] = freq[i];
            root[i][i] = i;
        }

        for (int len = 2; len <= n; len++)
        {
            for (int i = 0; i <= n - len; i++)
            {
                int j = i + len - 1;
                cost[i][j] = INT_MAX;
                int totalFreq = 0;

                for (int k = i; k <= j; k++)
                {
                    totalFreq += freq[k];
                }

                for (int k = i; k <= j; k++)
                {
                    int q = (k > i ? cost[i][k - 1] : 0) + (k < j ? cost[k + 1][j] : 0) + totalFreq;
                    if (q < cost[i][j])
                    {
                        cost[i][j] = q;
                        root[i][j] = k;
                    }
                }
            }
        }
    }

    TreeNode *getOptimalTree()
    {
        return buildTree(0, keys.size() - 1);
    }

    void inorderTraversal(TreeNode *root)
    {
        if (root)
        {
            inorderTraversal(root->left);
            cout << root->key << " ";
            inorderTraversal(root->right);
        }
    }

    bool search(TreeNode *root, const string &key)
    {
        if (!root)
            return false;
        if (root->key == key)
            return true;
        if (key < root->key)
            return search(root->left, key);
        return search(root->right, key);
    }
};

int main()
{
    int n;
    cout << "Enter the number of symbols: ";
    cin >> n;

    vector<string> keys(n);
    vector<int> freq(n);

    cout << "Enter the symbols and their frequencies:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> keys[i];
        cin >> freq[i];
    }

    OptimalBST obst(keys, freq);

    TreeNode *root = obst.getOptimalTree();

    cout << "\nIn-order traversal of the OBST (sorted order): ";
    obst.inorderTraversal(root);
    cout << endl;

    string key;
    cout << "\nEnter a symbol to search: ";
    cin >> key;
    if (obst.search(root, key))
    {
        cout << key << " found in the OBST.\n";
    }
    else
    {
        cout << key << " not found in the OBST.\n";
    }

    return 0;
}
