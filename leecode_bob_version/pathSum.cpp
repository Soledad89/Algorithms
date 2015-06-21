void pathSum(TreeNode* root , int gap, vector<int> &cur, 
		vector<vector<int> > &result){
	if (root == NULL) return ;

	cur.push_back(root->val);

	if (root->left == NULL && root->right == NULL) {
		if (gap == root->val)
			result.push_back(cur);
	}
	pathSum(root->left, gap - root->val, cur, result);
	pathSum(root->right, gap - root->val, cur, result);

	cur.pop_back();
}


