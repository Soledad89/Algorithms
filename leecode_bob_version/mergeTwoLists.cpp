ListNode *mergeTwoLists(ListNode *l1, ListNode *l2){
	if (l1 == NULL) return l2;
	if (l2 == NULL) return l1;

	ListNode dummy(-1);
	ListNode *p = &dummy;
	for (; l1 != NULL && l2 != NULL; p = p -> next){
		if (l1->val > l2->val){
			p->next = l2;
			ls = l2->next;
		}else{
			p->next = l1;
			l1 = l1->next;
		}
	}
	p->next = l1 != NULL ? l1 : l2;
	return dummy.next;
}


