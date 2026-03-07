#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
    TreeNode(int x,TreeNode* left,TreeNode* right):val(x),left(left),right(right){}
};
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x),next(NULL){}
};
class Solution {
public:
TreeNode* buildTree(const vector<string>& nodes)
{
    if(nodes.empty()||nodes[0]=="null")return nullptr;
    TreeNode* root= new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i=1;
    while(i<nodes.size())
    {
        TreeNode* cur=q.front();
        q.pop();
        if(i<nodes.size()&&nodes[i]!="null")
        {
            cur->left=new TreeNode(stoi(nodes[i]));
            q.push(cur->left);
        }
        i++;
        if(i<nodes.size()&&nodes[i]!="null")
        {
            cur->right=new TreeNode(stoi(nodes[i]));
            q.push(cur->right);
        }
        i++;
    }
    return root;
}


//前序遍历
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorderHelper(root, result);
        return result;
    }
//层序遍历
vector<vector<int>> levelOrder(TreeNode* root){
    vector<vector<int>> result;
    queue<TreeNode*> q;
    if(root!=nullptr){
        q.push(root);
    }
    while (!q.empty())
    {
        int size=q.size();
        vector<int> vec;
        for(int i=0;i<size;i++){
            TreeNode* node=q.front();
            q.pop();
            vec.push_back(node->val);
            if(node->left)
            {
                q.push(node->left);
            }
            if(node->right)
            {
                q.push(node->right);\
            }
        }
        result.push_back(vec);
    }
    return result;
    

}
//二叉树的右视图
vector<int> rightSideView(TreeNode* root)
{
    vector<int> result;
    queue<TreeNode*> q;
    if(root!=nullptr){
        q.push(root);
    }
    while(!q.empty())
    {
        int size=q.size();
        for(int i=0;i<size;i++){
            TreeNode* node=q.front();
            q.pop();
            if(i==size-1)
            {
                result.push_back(node->val);
            }
            if(node->left)
            {
                q.push(node->left);
            }
            if(node->right)
            {
                q.push(node->right);
            }
        }
  
    }
    return result;
}
//从中序与后序遍历序列构造二叉树
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
{
    if (inorder.size() == 0 || postorder.size() == 0) return NULL;
    return traversal(inorder, postorder);
}
ListNode* reverseKGroup(ListNode* head, int k)
{
    int n=0;
    while(head!=nullptr)
    {
        n++;
        head=head->next;
    }
    ListNode dummy(0);
    dummy.next=head;
    ListNode* p0=&dummy;
    
    ListNode* pre=nullptr;
    ListNode* cur=head;
    for(;n>=k;n-=k)
    {
        for(int i=0;i<k;i++)
        {
            ListNode* nxt=cur->next;
            cur->next=pre;
            pre=cur;
            cur=nxt;
        }
        ListNode* nxt=p0->next;
        p0->next->next=cur;
        p0->next=pre;
        p0=nxt;
    }
    return dummy.next;
}
private:
    void preorderHelper(TreeNode* node, vector<int>& result) {
       if(node==nullptr){return;}
       result.push_back(node->val);
       preorderHelper(node->left, result);
       preorderHelper(node->right, result);
    }
    TreeNode* traversal(vector<int>& inorder,vector<int>& postorder)
    {
        if(inorder.size()==0||postorder.size()==0)
        {
            return nullptr;
        }
        int rootVal=postorder.back();
        TreeNode* root=new TreeNode(rootVal);
        int index;
        for(index=0;index<inorder.size();index++)
        {
            if(inorder[index]==rootVal)
            {
                break;
            }
        }
        vector<int> leftInorder(inorder.begin(),inorder.begin()+index);
        vector<int> rightInorder(inorder.begin()+index+1,inorder.end());

        postorder.resize(postorder.size() - 1);
        vector<int> leftPostorder(postorder.begin(),postorder.begin()+leftInorder.size());
        vector<int> rightPostorder(postorder.begin()+leftInorder.size(),postorder.end());
        root->left=traversal(leftInorder,leftPostorder);
        root->right=traversal(rightInorder,rightPostorder);
        return root;
    }
};

int main() {
    
    Solution solution;
    vector<string> nodes = {"1", "2", "3", "8", "null", "4", "3"};
    TreeNode* root = solution.buildTree(nodes);
    vector<int> preorder = solution.preorderTraversal(root);
    cout << "前序遍历结果: ";
    for (int val : preorder) {  
        cout << val << " ";
    }
    cout << endl;
    return 0;
}