#include "listNode.h"

ListNode* removeDuplicatesFromSortedList(ListNode * head)
{
	ListNode* pre = head;
	if (head == nullptr)
		return nullptr;
	ListNode* cur;

	for (cur = pre->next; cur != nullptr; cur = cur->next)
	{
		if (cur->val == pre->val){
			pre->next = cur->next;
			delete cur;
		}
		else
			pre = cur;
	}
	return head;
}

