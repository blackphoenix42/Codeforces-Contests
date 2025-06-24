#include <bits/stdc++.h>
using namespace std;

struct Node
{
    string key;
    vector<Node *> child;
    bool locked = false;
    Node *Parent;
    int lockedDes = 0;
    int uid;
};

unordered_map<string, Node *> nodemap;
Node *newNode(string value, Node *parent = NULL)
{
    Node *nNode = new Node;
    nNode->key = value;
    nNode->Parent = parent;
    return nNode;
}

Node *BuildKaryTree(int n, int m)
{
    int count = 1;
    queue<Node *> q;
    string rootstring;
    string childstring;
    cin >> rootstring;
    Node *root = newNode(rootstring);
    nodemap[rootstring] = root;
    q.push(root);
    while (q.size() > 0 && count < n)
    {
        Node *parent = q.front();
        q.pop();
        count += m;
        for (int i = 1; i <= m; i++)
        {
            cin >> childstring;
            Node *x = newNode(childstring, parent);
            nodemap[childstring] = x;
            parent->child.push_back(x);
            q.push(x);
        }
    }
    return root;
}

// Node* searchNode(Node* root,string x){
//     if(root->key==x) return root;
//     queue<Node*> q;
//     q.push(root);
//     while(q.size()>0){
//         Node* parent= q.front();
//         q.pop();
//         for (auto it: parent->child) {
//             if(it->key== x) return it;
//             q.push(it);
//         }
//     }
//     return NULL;
// }

bool canlock(Node *node)
{
    if (node->lockedDes > 0)
        false;
    Node *temp = node->Parent;
    while (temp != NULL)
    {
        if (temp->locked)
            return false;
        temp = temp->Parent;
    }
    return true;
}

string lockNode(Node *root, string x, int uid)
{
    Node *t = nodemap[x];
    if (t->locked)
        return "false";
    else if (!canlock(t))
        return "false";
    else
    {
        t->locked = true;
        t->uid = uid;
        Node *parentNode = t->Parent;
        while (parentNode != NULL)
        {
            parentNode->lockedDes++;
            parentNode = parentNode->Parent;
        }
        return "true";
    }
}

string unlockNode(Node *root, string x, int uid)
{
    // Node* t= searchNode(root,x);
    Node *t = nodemap[x];
    if (!t->locked)
        return "false";
    else if (t->uid != uid)
        return "false";
    else
    {
        t->locked = false;
        t->uid = 0;
        Node *parentNode = t->Parent;
        while (parentNode != NULL)
        {
            parentNode->lockedDes--;
            parentNode = parentNode->Parent;
        }
        return "true";
    }
}

string upgradelock(Node *root, string x, int uid, int m)
{
    Node *t = nodemap[x];
    if (t->locked)
        return "false";
    int flag = 0;
    vector<Node *> lockednodes;
    queue<Node *> q;

    for (auto it : t->child)
    {
        if (it->locked)
        {
            if (it->uid != uid)
            {
                flag = 1;
                break;
            }
            else
                lockednodes.push_back(it);
        }
        else if (it->lockedDes > 0)
            q.push(it);
    }

    while (q.size() > 0)
    {
        Node *x = q.front();
        q.pop();
        for (auto it : x->child)
        {
            if (it->locked)
            {
                if (it->uid != uid)
                {
                    flag = 1;
                    break;
                }
                else
                    lockednodes.push_back(it);
            }
            else if (it->lockedDes > 0)
                q.push(it);
        }
    }

    if (flag)
        return "false";

    for (auto it : lockednodes)
    {
        it->locked = false;
        it->uid = 0;
        Node *temp = it->Parent;
        while (temp != NULL)
        {
            temp->lockedDes--;
            temp = temp->Parent;
        }
    }
    t->locked = true;
    t->uid = uid;
    t->lockedDes = 0;
    Node *temp = t->Parent;
    while (temp != NULL)
    {
        temp->lockedDes++;
        temp = temp->Parent;
    }
    return "true";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    Node *root = BuildKaryTree(n, m);
    int type, uid;
    string name;
    for (int i = 0; i < q; i++)
    {
        cin >> type >> name >> uid;
        if (type == 1)
            cout << lockNode(root, name, uid) << endl;
        else if (type == 2)
            cout << unlockNode(root, name, uid) << endl;
        else if (type == 3)
            cout << upgradelock(root, name, uid, m) << endl;
    }
    cout << endl;
    return 0;
}