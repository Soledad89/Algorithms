#include "listNode.h"
#define nullptr NULL
ListNode* removeDuplicatesFromLists2(ListNode* head)
{
	if (head->next == nullptr)
		return head;
	ListNode dummy(INT_MIN);//头节点
	dummy.next = head;
	ListNode *prev = &dummy, *cur = head;
	while(cur != nullptr){
		bool duplicated = false;
		while (cur->next!=nullptr && cur->val == cur->next->val){
			duplicated = true;
			ListNode *temp = cur;
			cur = cur->next;
			delete temp;
		}
		if (duplicated){//删除重复的最后一个元素
			ListNode* temp = cur;
			cur = cur->next;
			delete temp;
			continue;
		}
		prev->next = cur;
		prev = prev->next;
		cur = cur->next;
	}
	prev->next = cur;
	return dummy.next;
}


