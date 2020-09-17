#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Node{
public:
    int val;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int data){
        this->val = data;
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
    cout<< node->val << " ";
    inOrder(node->right);
}

int size(Node* node){
    return node == nullptr ? 0 : size(node->left) + size(node->right) + 1;
}

int maximum(Node* node){
    return node == nullptr ? -1e8 : max(max(maximum(node->left), maximum(node->right)), node->val);
}

int minimum(Node* node){
    return node == nullptr ? 1e8 : min(min(minimum(node->left), minimum(node->right)), node->val);
}

int height(Node* node){
    return node == nullptr ? -1 : max(height(node->left), height(node->right)) + 1;
}

bool find(Node* node, int val){
    if(node == nullptr){
        return false;
    }
    if(node->val == val){
        return true;
    }
    return find(node->left, val) || find(node->right, val);
}

bool rootTONodePath(Node* node, int val, vector<Node *>& path){
    if(node == nullptr){
        return false;
    }
    if(node->val == val){
        path.push_back(node);
        return true;
    }
    bool res = rootTONodePath(node->left, val, path) || rootTONodePath(node->right, val, path);
    if(res){
        path.push_back(node);
    }
    return res;
}

vector<Node *> rootTONodePath_02(Node* node, int data){
    if(node == nullptr){
        return {};
    }
    if(node->val == data){
        vector<Node *> base;
        base.push_back(node);
        return base;
    }

    vector<Node *> la = rootTONodePath_02(node->left, data);
    if(la.size() != 0){
        la.push_back(node);
        return la;
    }

    vector<Node *> ra = rootTONodePath_02(node->right, data);
    if(ra.size() != 0){
        ra.push_back(node);
        return ra;
    }
    return {};
}

Node* LCA(Node* root, Node* p, Node* q){
    vector<Node *> arr1, arr2;
    bool res = rootTONodePath(node->left, p->val, arr1) && rootTONodePath(node->right, q->val, arr2);
    if(!res){
        return nullptr;
    }
    int c1 = arr1.size() - 1;
    int c2 = arr2.size() - 1;
    Node* LCA = nullptr;
    while(c1 >= 0 && c2 >= 0){
        if(arr1[c1]->val != arr2[c2]->val){
            break;
        }
        LCA = arr1[c1];
        c1--;
        c2--;
    }
    return LCA;
}

int distanceBWNodes(Node* node, int p, int q){
    vector<Node* > arr1, arr2;
    bool res = rootTONodePath(node->left, p, arr1) && rootTONodePath(node->right, q, arr2);
    if(!res){
        return 0;
    }
    int c1 = arr1.size() - 1;
    int c2 = arr2.size() - 1;
    int LCA = 0;

    while(c1-- > 0 && c2-- > 0){
        if(arr1[c1]->val != arr2[c2]->val){
            break;
        }
        LCA++;
    }
    return (arr1.size() * arr2.size() - 2 * LCA); //in terms of edge
}

int diameter(Node* node){
    if(node == nullptr){
        return 0;
    }
    int ld = diameter(node->left);
    int rd = diameter(node->right);

    int lh = height(node->left);
    int rh = height(node->right);

    return max(max(ld, rd), lh + rh + 2);
}

pair<int, int> diameter_02(Node* node){
    if(node == nullptr){
        return {0, -1};
    }

    pair<int, int> lp = diameter_02(node->left);
    pair<int, int> rp = diameter_02(node->right);

    int dia = max(max(lp.first, rp.first), lp.second + rp.second + 2);
    int height = max(lp.second, rp.second) + 1;

    return {dia, height};
}

int dia_ = 0;
int diameter_03(Node* node){
    if(node == nullptr){
        return -1;
    }
    int la = diameter_03(node->left);
    int ra = diameter_03(node->right);

    dia_ = max(dia_, la + ra + 2);
    return max(la, ra) + 1;
}


//All Solution Class Pair------------------------------------------------------>>>>>>>>>>>>>>>>>>>>>>>

class allSolPair{
public:
    bool isBST = false;
    int maxEle = -1e8;
    int minEle = 1e8;

    int countOfBST = 0;

    int maxSizeOfBST = 0;
    Node *maxBSTNode = nullptr;

    bool isBal = false;
    int height = -1;
};

allSolPair allSolution(Node* node){
    if(node == nullptr){
        allSolPair base;
        base.isBST = true;
        base.isBal = true;
        return base;
    }

    allSolPair lp = allSolution(node->left);
    allSolPair rp = allSolution(node->right);

    allSolPair myPair;
    if(lp.isBST && rp.isBST && lp.maxEle < node->val && node->val < rp.minEle){
        myPair.isBST = true;
        myPair.countOfBST += 1;
        myPair.maxSizeOfBST = lp.maxSizeOfBST + rp.maxSizeOfBST + 1;
        myPair.maxBSTNode = node;
    }

    myPair.countOfBST += lp.countOfBST + rp.countOfBST;

    myPair.maxEle = max(max(lp.maxEle, rp.maxEle), node->val);
    myPair.minEle = min(min(lp.minEle, rp.minEle), node->val);

    if(!myPair.isBST){
        myPair.maxSizeOfBST = lp.maxSizeOfBST < rp.maxSizeOfBST ? rp.maxSizeOfBST : lp.maxSizeOfBST;
        myPair.maxBSTNode = lp.maxSizeOfBST < rp.maxSizeOfBST ? rp.maxBSTNode : lp.maxBSTNode;
    }

    if(lp.isBal && rp.isBal && abs(lp.height - rp.height) < 2){
        myPair.isBal = true;
    }

    myPair.height = max(lp.height, rp.height) + 1;
    return myPair;
}

//Leaf to Leaf PairSum -------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>

// class PairSum{
// public:
//     int maxSumLTL = 0; // max sum leaf to leaf.
//     int maxSumNTL = 0;
//     string maxPathLTL = "";
//     string maxPathNTL = ""; // max sum node to leaf.

//     pairSum(int a, int b, string c, string d)
//     {
//         maxSumLTL = a;
//         nodeToLeafMaxSum = b;
//         maxPathLTL = c;
//         maxPathNTL = d;
//     }
// };

// PairSum leafToLeafPathSum02(Node* node){
//     if(node == nullptr){
//         PairSum base(-1e8, node->val, "", "");
//         return base;
//     }

//     PairSum lp = leafToLeafPathSum02(node->left);
//     PairSum rp = leafToLeafPathSum02(nodr->right);

//     PairSum myPair(-1e8, -1e8, "", "");
//     if(node->left == nullptr && node->right == nullptr){
//         PairSum base(-1e8, -1e8, "", to_string(node->val));
//         return base;
//     }
//     if(node->left != nullptr && node->right != nullptr){
//         myPair.maxSumLTL = max(max(lp.maxSumLTL, rp.maxSumLTL), lp.maxSumNTL + node->val + rp.maxSumNTL);
//         if(myPair.maxSumLTL == lp.maxSumLTL){
//             myPair.maxPathLTL = lp.maxPathLTL;
//         }
//         else if()
//     }
// }


//--------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Level-Order / BFS----------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void levelOrder(Node* node){
    queue<Node *> q;
    q.push(node);
    while(q.size() != 0){
        Node* rvtx = q.front();
        q.pop();
        cout<< rvtx->val << " ";
        if(rvtx->left != nullptr){
            q.push(rvtx->left);
        }
        if(rvtx->right != nullptr){
            q.push(rvtx->right);
        }
    }
}

void levelOrder_02(Node* node){
    queue<Node *> q;
    q.push(node);
    q.push(nullptr);
    while(q.size() != 1){ // stop the loop when u have the only nullptr in your queue
        Node* rvtx = q.front();
        q.pop();
        cout<< rvtx->val << " ";
        if(rvtx->left != nullptr){
            q.push(rvtx->left);
        }
        if(rvtx->right != nullptr){
            q.push(rvtx->right);
        }

        if(q.front() == nullptr){
            cout<<endl;
            q.pop();
            q.push(nullptr);
        }
    }
}

void levelOrder_03(Node* node){
    queue<Node *>q;
    q.push(node);
    int level = 0;
    while(q.size() != 0){
        int size = q.size();
        cout<< "Level" << level << " ";
        while(size-- > 0){
            Node *rvtx = que.front();
            que.pop();
            cout << rvtx->data << " ";

            if (rvtx->left != nullptr){
                que.push(rvtx->left);
            }
            if (rvtx->right != nullptr){
                que.push(rvtx->right);
            }
        }
        level++;
        cout << endl;
    }
}

// Tree-Views : ---------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void leftView(Node* node){
    queue<Node *> q;
    q.push(node);
    while(q.size() != 0){
        int size = q.size();
        cout<< q.front()->val << " ";
        while(size-- > 0){
            Node* rvtx = q.front();
            q.pop();
            if (rvtx->left != nullptr){
                    que.push(rvtx->left);
                }
            if (rvtx->right != nullptr){
                que.push(rvtx->right);
            }
        }
        cout << endl;
    }
    cout << endl;
}

void rightView(Node* node){
    queue<Node *> q;
    q.push(node);
    while(q.size() != 0){
        int size = q.size();
        Node* prev = nullptr;
        while(size-- > 0){
            Node* rvtx = q.front();
            q.pop();
            if(rvtx->left != nullptr){
                q.push(rvtx->left);
            }
            if(rvtx->right != nullptr){
                q.push(rvtx->right);
            }
            prev = rvtx;
        }
        cout<< prev->val < " ";
        cout<< endl;
    }
    cout<< endl;
}

void width(Node* node, int level, pair<int, int>& maxMin){
    if(node == nullptr){
        return;
    }
    maxMin.first = min(maxMin.first, level);
    maxMin.second = max(maxMin.second, level);

    width(node->left, level - 1, maxMin);
    width(node->right, level + 1, maxMin);
}




//================================================================================================

void display(Node *node)
{
    if (node == nullptr)
        return;
    string str = "";
    str += node->left != nullptr ? to_string(node->left->val) : ".";
    str += " <- " + to_string(node->val) + " -> ";
    str += node->right != nullptr ? to_string(node->right->val) : ".";
    cout << str << endl;

    display(node->left);
    display(node->right);
}

void solve()
{
    vector<int> arr = {10, 20, 30, 40, -1, -1, 50, -1, -1, 60, 70, -1, 80, -1, -1, -1, 90, 100, -1, 120, -1, -1, 110, 130, -1, -1, -1};
    // vector<int> arr = {-15, 5, -8, 2, -1, -1, 6, -1, -1, 1, -1, -1, 6, 3, -1, -1, 9, -1, 0, 4, -1, -1, -2, 10, -1, -1, -1};

    Node *root = constructTree(arr);
    // inOrder(root);
    vector<Node* > path;
    // cout<<rootTONodePath(root, 70, path);
    display(root);

    // pairSum p = leafToLeafPathSum02(root);
    // cout << p.maxPathLTL << " @ " << p.maxSumLTL << endl;

    // set1(root);
}

int main()
{
    solve();
    return 0;
}


