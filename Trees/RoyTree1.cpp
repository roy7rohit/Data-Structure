#include<iostream>
#include<vector>
using namespace std;

class Node{
public:
    int data;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int data){
        this->data = data;
    }
};

int idx = 0;

Node* constructTree(vector<int>& arr){
    if(idx == arr.size() || arr[idx] == -1){
        idx++;
        return nullptr;
    }

    Node* node = new Node(arr[idx++]);
    node->left = constructTree(arr);
    node->right = constructTree(arr);

    return node;
}

void inOrder(Node* node){
    if(node == nullptr){
        return;
    }
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

int size(Node* node){
    return node == nullptr ? 0 : size(node->left) + size(node->right) + 1;
}

int height(Node* node){
    return node == nullptr ? -1 : max(height(node->left), height(node->right)) + 1;
}

int maximum(Node* node){
    return node == nullptr ? -1e8 : max(max(maximum(node->left), maximum(node->right)), node->data);
}

int minimum(Node* node){
    return node == nullptr ? 1e8 : min(min(minimum(node->left), minimum(node->right)), node->data);
}

bool find(Node* node, int data){
    if(node == nullptr){
        return false;
    }
    if(node->data == data){
        return true;
    }
    return find(node->left, data) || find(node->right, data);
}

bool rootToNodePath(Node* node, int data, vector<Node *>& path){
    if(node == nullptr){
        return false;
    }
    if(node->data == data){
        path.push_back(node);
        return true;
    }
    bool res = rootToNodePath(node->left, data, path) || rootToNodePath(node->right, data, path);
    if(res){
        path.push_back(node);
    }
    return res;
}

vector<Node *> rootToNodePath_02(Node* node, int data){
    if(node == nullptr){
        return {};
    }
    if(node->data == data){
        vector<Node *> base;
        base.push_back(node);
        return base;
    }

    vector<Node *> la = rootToNodePath_02(node->left, data);
    if(la.size() != 0){
        la.push_back(node);
        return la;
    }


    vector<Node *> ra = rootToNodePath_02(node->right, data);
    if(ra.size() != 0){
        ra.push_back(node);
        return ra;
    }
    return {};
}

Node* lowestCommonAncestor(Node *node, Node *p, Node *q){
    vector<Node *> arr1, arr2;
    bool res = rootToNodePath(node, p->data, arr1) && rootToNodePath(node, q->data, arr2);
    if(!res){
        return nullptr;
    }
    int c1 = arr1.size() - 1;
    int c2 = arr2.size() - 1;

    Node *LCA = nullptr;
    while(c1-- > 0 && c2-- > 0){
        if(arr1[c1]->data != arr2[c2]->data){
            break;
        }
        LCA = arr1[c1];
    }
    return LCA;
}

int distanceBWNodes(Node *node, int p, int q){
    vector<Node *> arr1, arr2;
    bool res = rootToNodePath(node, p, arr1) && rootToNodePath(node, q, arr2);
    if(!res){
        return 0;
    }
    int c1 = arr1.size() - 1;
    int c2 = arr2.size() - 1;
    int LCA = 0;

    while(c1-- > 0 && c2-- > 0){
        if(arr1[c1]->data != arr2[c2]->data){
            break;
        }
        LCA++;
    }
    return (arr1.size() + arr2.size() - 2 * LCA);
}

int diameter(Node *node){
    if(node == nullptr){
        return 0;
    }

    int ld = diameter(node->left);
    int rd = diameter(node->right);

    int lh = height(node->left);
    int rh = height(node->right);

    return max(max(ld, rd), lh + rh + 2);
}

pair<int, int> diameter_02(Node *node){
    if(node == nullptr){
        return {0, -1};
    }
    pair<int, int> la = diameter_02(node->left);
    pair<int, int> ra = diameter_02(node->right);

    int dia = max(max(la.first, ra.first), la.second + ra.second + 2);
    int height = max(la.second, ra.second) + 1;

    return {dia, height};
}

int dia_ = 0;
int diameter_03(Node *node){
    if(node == nullptr){
        return -1;
    }

    int la = diameter_03(node->left);
    int ra = diameter_03(node->right);

    dia_ = max(dia_, la + ra + 2);
    return max(la, ra) + 1;
}

void display(Node *node){
    if(node == nullptr){
        return;
    }
    string str = "";
    str += node->left != nullptr ? to_string(node->left->data) : ".";
    str += " <- " + to_string(node->data) + " -> ";
    str += node->right != nullptr ? to_string(node->right->data) : ".";
    cout << str << endl;

    display(node->left);
    display(node->right);
}

void solve()
{
    vector<int> arr = {10, 20, 30, 40, -1, -1, 50, -1, -1, 60, 70, -1, 80, -1, -1, -1, 90, 100, -1, 120, -1, -1, 110, 130, -1, -1, -1};
    Node *root = constructTree(arr);
    inOrder(root);
    cout << endl ;
    cout << "======================================================================" << endl;
    display(root);
}


int main(){

    solve();
    return 0;
}
