int sumNumbers(TreeNode *root, int sum) {
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return sum * 10 + root->val;

	return sumNumbers(root->left, sum * 10 + root->val) +
		sumNumbers(root->right, sum * 10 + root->val);
}

