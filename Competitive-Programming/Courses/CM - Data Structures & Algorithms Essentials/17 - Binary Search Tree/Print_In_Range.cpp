/*
    Print all elements of BST which lie in range k1 and k2
*/

#include <bits/stdc++.h>
using namespace std;

class Node{

    public:
        int key;
        Node *left;
        Node *right;
    
    Node(int key){
        this->key = key;
        left = right = NULL;
    }
};

Node * insert( Node * root, int key){
    if(root == NULL){
        return new Node(key);
    }

    if(key < root -> key){
        root -> left = insert(root -> left, key);
    }
    else{
        root -> right = insert(root -> right, key);
    }

    return root;
}

void printInorder(Node * root){
    if(root == NULL){
        return;
    }
    printInorder(root -> left);
    cout << root -> key<< " ";
    printInorder(root -> right);
}

void printRange(Node*root, int k1, int k2){
    if(root == NULL){
        return;
    }

    if(root -> key >= k1 and root -> key <= k2 ){
        printRange(root->left,k1,k2);
        cout<<root->key<<" ";
        printRange(root->right,k1,k2);
    }
    else if( root -> key > k2){
        printRange(root -> left, k1, k2);
    }
    else{
        // root -> key < k1
        printRange(root -> right, k1, k2);
    }
}

int main()
{
    Node * root = NULL;
    int a [] = {8,3,10,1,6,14,4,7,13};

    for(int x: a){
        root = insert(root,x);
    }
    // printInorder(root);
    printRange(root,5,12);
    return 0;
}