// AVL Tree

#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    int height;
    Node *right;
    Node *left;
    Node(int x)
    {
        data = x;
        height = 1;
        right = left = NULL;
    }
};

int height(Node *node)
{

    if (!node)
        return 0;

    return 1 + max(height(node->left), height(node->right));
}

Node *rotateLeft(Node *node)
{
    Node *mid = node->right;
    Node *child = mid->left;
    mid->left = node;
    node->right = child;

    node->height = 1 + max(height(node->left), height(node->right));
    mid->height = 1 + max(height(mid->left), height(mid->right));

    return mid;
}

Node *rotateRight(Node *node)
{
    Node *mid = node->left;
    Node *child = mid->right;
    mid->right = node;
    node->left = child;

    node->height = 1 + max(height(node->left), height(node->right));
    mid->height = 1 + max(height(mid->left), height(mid->right));

    return mid;
}

void inorder(Node *node)
{
    if (node)
    {
        inorder(node->left);
        cout << node->data << "\t";
        inorder(node->right);
    }
}

Node *insert(Node *node, int value)
{

    if (!node)
    {
        return new Node(value);
    }

    else if (value < node->data)
    {
        node->left = insert(node->left, value);
    }

    else if (value > node->data)
    {
        node->right = insert(node->right, value);
    }

    else
    {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = height(node->left) - height(node->right);

    if (balance > 1 && value < node->left->data)
    { // LL
        return rotateRight(node);
    }

    else if (balance > 1 && value > node->left->data)
    { // LR
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    else if (balance < -1 && value > node->right->data)
    { // RR
        return rotateLeft(node);
    }

    else if (balance < -1 && value < node->right->data)
    { // RL
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    else
    {
        return node;
    }
}

void search(Node *node, int target)
{
    if (!node)
    {
        cout << " not found" << endl;
        return;
    }
    else if (target < node->data)
    {
        search(node->left, target);
    }

    else if (target > node->data)
    {
        search(node->right, target);
    }
    else
    {
        cout << "found" << endl;
        return;
    }
}

int main()
{
    Node *root = NULL;

    int arr[5] = {4, 1, 7, 6, 5};

    for (int i = 0; i < 5; i++)
    {
        root = insert(root, arr[i]);
    }
    cout << "\ninorder traversal" << endl;
    inorder(root);

    search(root, 10);
    return 0;
}