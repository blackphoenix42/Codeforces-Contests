#include <bits/stdc++.h>
using namespace std;
/* 
PreOrder Input: 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1 
LevelOrder Input: 1 2 3 4 5 -1 6 -1 -1 7 -1 -1 -1 -1 -1


-1 = NULL
                              1
                      2               3
                4          5               6
                        7
*/

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


// Preorder Build of Tree: Root -> Left -> Right
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

Node * levelOrderBuild(){
    int d;
    cin >> d;
    Node * root = new Node(d);
    queue<Node *> q;
    q.push(root);
    while(!q.empty()){
        Node * current = q.front();
        q.pop();
        int c1, c2;
        cin >> c1 >> c2;
        if(c1 != -1){
            current->left = new Node(c1);
            q.push(current->left);
        }
        if(c2 != -1){
            current->right = new Node(c2);
            q.push(current->right);
        }
    }
    return root;
}


void printPreorder(Node * root){

    if(root == NULL){
        return;
    }
    cout << root -> data << " ";
    printPreorder(root -> left);
    printPreorder(root -> right);

}

void printInorder(Node * root){
    if( root == NULL){
        return;
    }
    printInorder(root -> left);
    cout << root -> data << " ";
    printInorder(root -> right);

}

void printPostorder(Node * root){
    if( root == NULL){
        return;
    }
    printPostorder(root -> left);
    printPostorder(root -> right);
    cout << root -> data << " ";

}

void printLevelOrder(Node * root){
    queue<Node *> q;

    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node * temp = q.front();
        if( temp == NULL){
            cout<<endl;
            q.pop();
            if(!q.empty()){
                q.push(NULL);
            }
        }else{
            q.pop();
            cout << temp->data << " ";
            if(temp -> left){
                q.push(temp -> left);
            }
            if(temp -> right){
                q.push(temp -> right);
            }
        }
    }
    return ;
}

int height(Node * root){
    if(root == NULL){
        return 0;
    }
    int h1 = height(root -> left);
    int h2 = height(root -> right);

    return max(h1,h2) + 1;
}

// Time - O(N^2)
int diameter(Node * root){
    if(root == NULL ){
        return 0;
    }
    int D1 = height(root -> left) + height(root -> right);
    int D2 = diameter(root -> left);
    int D3 = diameter(root -> right);

    return max(D1, max(D2, D3));
}
// Diameter Optimised
// Time - O(N)
class HDPair{
    public:
        int height;
        int diameter;
};

HDPair optDiameter(Node * root){
    HDPair p;
    if(root == NULL ){
        p.height = p.diameter = 0;
        return p;
    }
    HDPair Left = optDiameter(root -> left);
    HDPair Right = optDiameter(root -> right);

    p.height = max(Left.height, Right.height) + 1;

    int D1 = Left.height + Right.height;
    int D2 = Left.diameter;
    int D3 = Right.diameter;

    p.diameter = max(D1,max(D2,D3));
    return p;
}

int main()
{   
    Node * root = levelOrderBuild();
    // printPreorder(root);
    // printInorder(root);
    // printPostorder(root);
    // printLevelOrder(root); 
    // cout << height(root);
    // cout << diameter(root);
    cout << optDiameter(root).diameter;
    return 0;
}