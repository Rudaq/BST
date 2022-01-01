// lab 5 - hashtable.cpp 
//Paulina Puchalska 180268

#include <iostream>
#include <string>

using namespace std;

struct node
{
    int key;
    node* left = nullptr, * right = nullptr;
};

node* newNode(int item)
{
    node* temp = new node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

node* insert(node* node, int key) // +
{
    if (node == nullptr) return newNode(key);
    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }

    return node;
}

node* min(node* node)
{
    if (node->left != nullptr)   return min(node->left);

    return node;
}

node* max(node* node)
{
    if (node->right != nullptr)   return max(node->right);

    return node;
}

node* delete_element(node*& n, int key) {
    node* temp;

    if (n == NULL)        return NULL;

    else if (key < n->key)
        n->left = delete_element(n->left, key);
    else if (key > n->key)
        n->right = delete_element(n->right, key);
    else if (n->left && n->right)
    {
        temp = min(n->right);
        n->key = temp->key;
        n->right = delete_element(n->right, n->key);
    }
    else
    {
        temp = n;

        if (n->left == NULL)
            n = n->right;
        else if (n->right == NULL)
            n = n->left;

        delete temp;
    }

    return n;
}

node* find_key(node*& tree, int key) // ?
{
    if (key > tree->key)
    {
        if (tree->right != nullptr)
            return find_key(tree->right, key);
    }
    else if (key < tree->key)
    {
        if (tree->left != nullptr)
            return find_key(tree->left, key);
    }
    if (tree->key == key)   return tree;


    return nullptr;
}

void delete_tree(node*& root) // q
{
    if (root != nullptr)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
        root = nullptr;
    }
}

void PrintPreOrder(node*& node) {
    if (node != NULL) {
        cout << node->key << " ";
        PrintPreOrder(node->left);
        PrintPreOrder(node->right);
    }
}


int main()
{
    char input;
    int key;
    node* tree = nullptr;

    while (true)
    {
        cin >> input;

        if (input == '+')
        {
            cin >> key;
            tree = insert(tree, key);
        }
        else if (input == '-')
        {
            cin >> key;
            delete_element(tree, key);
        }
        else if (input == 'p')
        {
            cout << PrintPreOrder<< " " << endl;
        }
        else if (input == '?')
        {
            cin >> key;

            if (find_key(tree, key))    cout << "1";
            else  cout << "0";

            cout << endl;
        }
        else if (input == 'm')
        {
            cout << min(tree)->key << endl;
        }
        else if (input == 'M')
        {
            cout << max(tree)->key << endl;
        }
        else if (input == 'q')
        {
            delete_tree(tree);
            break;
        }
    }
    return 0;
}

