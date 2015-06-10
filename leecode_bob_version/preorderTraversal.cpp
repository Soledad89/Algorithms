vector<int> preorderTraversal(TreeNode *root){
	vector<int> result;
	const TreeNode *p;
	stack<const TreeNode *> s;

	p = root;
	if (p != NULL) s.push(p);

	while (!s.empty()) {
		p = s.top();
		s.pop();
		result.push_back(p->val);

		if ( p->right != NULL) s.push(p->right);
		if ( p->left != NULL) s.push(p->left);
	}
	return result;
}


