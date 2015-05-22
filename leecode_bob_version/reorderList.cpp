#include "listNode.h"
//找到中间节点，把后半节链表reverse，然后合并成一个大的链表
ListNode* reverse(ListNode* head);
void reorderList(ListNode* head){
	if (head == NULL || head->next == NULL)
		return;
	ListNode* slow = head;
	ListNode* fast = head;
	ListNode* prev = NULL;
	while (fast && fast->next){
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	prev->next = NULL;
	slow = reverse(slow);
	ListNode* cur = head;
	while (cur->next){
		ListNode* tmp = cur->next;
		cur->next = slow;
		slow = slow->next;
		cur->next->next = tmp;
		cur = tmp;
	}
	cur->next = slow;
}

ListNode* reverse(ListNode* head){
	if (head == NULL || head->next == NULL)
		return head;

	ListNode* prev = head;
	ListNode* tmp = head->next;
	ListNode* cur = tmp->next;
	head->next = NULL;
	while(cur->next){
		tmp->next = prev;
		prev = tmp;
		tmp = cur;
		cur = cur->next;
	}
	tmp->next = prev;
	cur->next = tmp;;
	return cur;
}


