int minimumDepthofBinaryTree(const TreeNode *root, bool hasbrother){
	if (!root) return hasbrother ? INT_MAX : 0;

	return 1 + min(minimumDepthofBinaryTree(root->left, root->right != NULL),
			minimumDepthofBinaryTree(root->right, root->left != NULL));
}

int maxDepthOfBinaryTree(TreeNode* root){
	if (root == NULL) return 0;

	return max(maxDepthOfBinaryTree(root->left), maxDepthOfBinaryTree(root->right)) + 1;
}

