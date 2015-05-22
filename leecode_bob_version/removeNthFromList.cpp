#include "listNode.h"

ListNode* removeNthFromList(ListNode* head, int n)// 只扫描了一次
{
	ListNode dummy(-1);
	dummy.next = head;

	ListNode* p = &dummy;
	ListNode* q = &dummy;

	for (int i = 0; i < n; i++)
		q = q->next;

	while (q->next) 
	{	
		q = q->next;
		p = p->next;
	}
	
	ListNode* tmp;
	tmp = p->next;
	p->next = p->next->next;
	delete tmp;
	return dummy.next;
}



