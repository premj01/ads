#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
    bool rightThread;

    Node(int val)
    {
        data = val;
        left = right = nullptr;
        rightThread = true;
    }
};

class ThreadedBST
{
private:
    Node *root;

public:
    ThreadedBST()
    {
        root = nullptr;
    }

    void insert(int val)
    {
        Node *ptr = root;
        Node *parent = nullptr;

        while (ptr != nullptr)
        {
            if (val == ptr->data)
            {
                cout << "Duplicate value not allowed.\n";
                return;
            }
            parent = ptr;

            if (val < ptr->data)
            {
                if (ptr->left != nullptr)
                    ptr = ptr->left;
                else
                    break;
            }
            else
            {
                if (!ptr->rightThread)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        Node *newNode = new Node(val);

        if (parent == nullptr)
        {
            root = newNode;
        }
        else if (val < parent->data)
        {
            parent->left = newNode;
            newNode->right = parent;
        }
        else
        {
            newNode->right = parent->right;
            parent->right = newNode;
            parent->rightThread = false;
        }
    }

    void inorderTraversal()
    {
        Node *curr = root;
        while (curr != nullptr && curr->left != nullptr)
            curr = curr->left;

        while (curr != nullptr)
        {
            cout << curr->data << " ";

            if (curr->rightThread)
                curr = curr->right;
            else
            {
                curr = curr->right;
                while (curr != nullptr && curr->left != nullptr)
                    curr = curr->left;
            }
        }
        cout << endl;
    }

    void display()
    {
        cout << "In-order Display of Threaded Binary Tree: ";
        inorderTraversal();
    }
};

int main()
{
    ThreadedBST tbt;
    int choice, value;

    do
    {
        cout << "\n--- Threaded Binary Tree Menu ---\n";
        cout << "1. Insert\n2. In-order Traversal\n3. Display\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tbt.insert(value);
            break;
        case 2:
            cout << "In-order Traversal: ";
            tbt.inorderTraversal();
            break;
        case 3:
            tbt.display();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
