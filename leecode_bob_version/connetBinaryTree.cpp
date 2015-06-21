struct TreeLinkNode{
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) {
		val = x;
		left = NULL;
		right = NULL;
		next = NULL;
	}
}

void connet(TreeLinkNode *root, TreeLinkNode *sibling){
	if (root = NULL)
		return ;
	else 
		root->next = sibling;

	connet(root->left , root->right);
	if (sibling)
		connet(root->right, sibling->left);
	else
		connet(root->right, NULL);
}

