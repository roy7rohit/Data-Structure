// Definition for a binary tree node.
class TreeNode {
public:
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class PairSum{
public:

    int maxSumLTL = 0;
    int maxSumNTL = 0;
    string maxPathLTL = "";
    string maxPathNTL = "";

    PairSum(int a, int b, string c, string d){
        maxSumLTL = a;
        maxSumNTL = b;
        maxPathLTL = c;
        maxPathNTL = d;
    }
};

PairSum LTLPathSum(TreeNode *node){
    if(node == nullptr){
        PairSum base(-1e8, -1e8, "", "");
        return base;
    }

    PairSum lp = LTLPathSum(node->left);
    PairSum rp = LTLPathSum(node->right);

    PairSum myPair(-1e8, -1e8, "", "");
    if(node->left == nullptr && node->right == nullptr){ // it's node not a leaf
        PairSum base(-1e8, node->val, "", to_string(node->val));
        return base;
    }

    if(node->left != nullptr  && node->right != nullptr){ // it must be a leaf
        myPair.maxPathLTL = max(max(lp.maxSumLTL, rp.maxSumLTL), lp.maxSumNTL + rp.maxSumNTL + node->val)
        if(myPair.maxSumLTL == lp.maxSumLTL){
            myPair.maxPathLTL = lp.maxPathLTL;
        }
        else if(myPair.maxSumLTL == rp.maxSumLTL){
            myPair.maxPathLTL = rp.maxPathLTL;
        }
        else{
            myPair.maxPathLTL = lp.maxPathNTL + " " + to_string(node->val) + " " + rp.maxPathNTL;
        }
    }
    else{
        if(lp.maxSumLTL > rp.maxSumLTL){
            myPair.maxSumLTL = lp.maxSumLTL;
            myPair.maxPathLTL = lp.maxPathLTL;
        }
        else{
            myPair.maxSumLTL = rp.maxSumLTL;
            myPair.maxPathLTL = rp.maxPathLTL;
        }
    }
    if(lp.maxSumNTL > rp.maxSumNTL){
        myPair.maxSumNTL = lp.maxSumNTL + node->val;
        myPair.maxPathNTL = lp.maxPathNTL + " " + to_string(node->val);
    }
    else{
        myPair.maxSumNTL = rp.maxSumNTL + node->val;
        myPair.maxPathNTL = rp.maxPathNTL + " " + to_string(node->val);
    }
    return myPair;
}


//=================================================================================================

//===============================================================================================

void display(TreeNode *node){
    if(node == nullptr){
        return;
    }
    string str = "";
    str += node->left != nullptr ? to_string(node->left->val) : " . ";
    str += " <- " + to_string(node->val) + " -> ";
    str += node->right != nullptr ? to_string(node->right->val) : " . ";
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
    display(root);

    pairSum p = LTLPathSum(root);
    cout << p.maxPathLTL << " @ " << p.maxSumLTL << endl;

    // set1(root);
}

int main()
{
    solve();
    return 0;
}
