#include "listNode.h"

ListNode* rotateRightList(ListNode *head, int k){
	if (head == NULL || k == 0)
		return head;

	int len = 1;
	ListNode* p = head;
	while (p->next){
		len++;
		p = p->next;
	}

	k = len - k % len;
	p->next = head;
	for (int step = 0; step < k; step++)
		p = p->next;

	head = p->next;
	p->next = NULL;
	return head;
}


