//leetcode oj 98
//https://leetcode.com/problems/validate-binary-search-tree/description/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool foo(struct TreeNode* root,long int *bar)
{
    if(!root)
    {
        return true;
    }
    bool _ = foo(root->left,bar);
    if(root->val<=*bar)
    {
        return false;
    }
    *bar = root->val;
    bool __ = foo(root->right,bar);
    return _ && __;
}
bool isValidBST(struct TreeNode* root) 
{
    long int _ = LONG_MIN;
    return foo(root,&_);
}
