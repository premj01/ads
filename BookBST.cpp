#include <iostream>
using namespace std;

class Book
{
public:
    string title, author;
    double price;

    Book() {}
    Book(string title, string author, double price)
    {
        this->author = author;
        this->title = title;
        this->price = price;
    }
};
class node
{
public:
    Book data;
    node *left, *right;

    node(string title, string author, double price)
    {
        data.author = author;
        data.title = title;
        data.price = price;
        left = right = nullptr;
    }
};

class BST
{
public:
    node *root;
    BST()
    {
        root = nullptr;
    }

    void insert(string title, string author, double price)
    {
        node *temp = new node(title, author, price);

        if (root == nullptr)
        {
            root = temp;
        }

        node *n = root;
        while (true)
        {
            if (n->data.title < temp->data.title)
            {
                if (n->right == nullptr)
                {
                    n->right = temp;
                    return;
                }
                else
                {
                    n = n->right;
                }
            }
            else if (n->data.title > temp->data.title)
            {
                if (n->left == nullptr)
                {
                    n->left = temp;
                    return;
                }
                else
                {
                    n = n->left;
                }
            }
            else
            {
                return;
            }
        }
    }

    node *inorderSuccessor(node *n)
    {
        if (n == nullptr)
            return n;

        n = n->right;
        while (n->left != nullptr)
        {
            n = n->left;
        }
        return n;
    }

    node *deleteNode(node *n, string title)
    {
        if (n == nullptr)
            return n;

        if (n->data.title < title)
        {
            n->right = deleteNode(n->right, title);
        }
        else if (n->data.title > title)
        {
            n->left = deleteNode(n->left, title);
        }
        else
        {
            if (n->right == nullptr)
            {
                cout << "Deleting " << n->left->data.title;
                node *temp = n->left;
                n->left = nullptr;
                delete temp;
                return n;
            }
            else if (n->left == nullptr)
            {
                cout << "Deleting " << n->right->data.title;
                node *temp = n->right;
                n->right = nullptr;
                delete temp;
                return n;
            }
            else
            {
                node *sucessor = inorderSuccessor(n);
                n->data = sucessor->data;
                deleteNode(n->right, sucessor->data.title);
                return n;
            }
        }
        return n;
    }
    void inorder(node *n)
    {
        if (n == nullptr)
        {
            return;
        }

        inorder(n->left);
        cout << n->data.title << "\t" << n->data.author << "\t" << n->data.price << endl;
        inorder(n->right);
    }
    node *search(node *n, string title)
    {
        if (n == nullptr || n->data.title == title)
        {
            return root;
        }

        if (n->data.title < title)
        {
            return search(n->right, title);
        }

        return search(n->left, title);
    }
    void updateTitle(string title, string newTitle)
    {
        node *n = search(root, title);
        if (n != nullptr)
        {
            n->data.title = newTitle;
        }
        else
        {
            cout << "Book not found" << endl;
        }
    }
};

int main()
{
    BST catalog;
    int choice;
    string title, author, newTitle;
    double price;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Insert a Book\n";
        cout << "2. Delete a Book\n";
        cout << "3. Display Catalog (In-Order)\n";
        cout << "4. Search for a Book\n";
        cout << "5. Update Book Title\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter book title: ";
            cin.ignore(); // To clear the input buffer
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            cout << "Enter price: ";
            cin >> price;
            catalog.insert(title, author, price);
            cout << "Book inserted successfully!\n";
            break;

        case 2:
            cout << "Enter title of the book to delete: ";
            cin.ignore();
            getline(cin, title);
            catalog.deleteNode(catalog.root, title);
            cout << "Book deleted successfully if it existed.\n";
            break;

        case 3:
            cout << "\nCatalog:\n";
            catalog.inorder(catalog.root);
            break;

        case 4:
            cout << "Enter title of the book to search: ";
            cin.ignore();
            getline(cin, title);
            if (catalog.search(catalog.root, title) != nullptr)
            {
                cout << "Book found: " << title << endl;
            }
            else
            {
                cout << "Book not found.\n";
            }
            break;

        case 5:
            cout << "Enter title of the book to update: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter new title: ";
            getline(cin, newTitle);
            catalog.updateTitle(title, newTitle);
            break;

        case 6:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
