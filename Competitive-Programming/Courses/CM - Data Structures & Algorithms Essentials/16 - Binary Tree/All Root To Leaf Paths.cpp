#include <bits/stdc++.h>
using namespace std;

class Node{

    public:
        int data;
        Node *left;
        Node *right;
    
    Node(int d){
        data = d;
        left = right = NULL;
    }
};
Node* preOrderBuildTree(){
    int d;
    cin >> d;
    if(d == -1){
        return NULL;
    }
    Node * n = new Node(d);
    n -> left = preOrderBuildTree();
    n -> right = preOrderBuildTree();
    return n;
}

void printRoot2LeafPaths(Node * root, vector<int> &path){
    if(root == NULL){
        return;
    }
    if(root -> left == NULL and root -> right == NULL){
        for(int node : path){
            cout<<node<<"->";
        }
        cout<<root->data ;
        cout<<endl;
        return;
    }
    path.push_back(root->data);
    printRoot2LeafPaths(root->left,path);
    printRoot2LeafPaths(root->right,path);
    path.pop_back();
    return;
}

int main()
{
    // Input: 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
    Node * root = preOrderBuildTree();
    vector<int>path;
    printRoot2LeafPaths(root,path);
    return 0;
}