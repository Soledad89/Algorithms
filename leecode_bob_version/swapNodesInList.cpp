#include "listNode.h"

ListNode* swapNodesInList(ListNode* head){
	if (!head || !head->next)
		return head;
	ListNode dummy(-1);
	dummy.next = head;
	ListNode* prev = &dummy;
	ListNode* cur = prev->next;
	ListNode* next = cur->next;
	while(next)
	{
		prev->next = next;
		cur->next = next->next;
		next->next = cur;

		prev = cur;
		cur = cur->next;
		next = cur ? cur->next : NULL;
	}
	return dummy.next;
}


