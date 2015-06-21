int minimumDepthofBinaryTree(const TreeNode *root, bool hasbrother){
	if (!root) return hasbrother ? INT_MAX : 0;

	return 1 + min(minimumDepthofBinaryTree(root->left, root->right != NULL),
			minimumDepthofBinaryTree(root->right, root->left != NULL));
}

