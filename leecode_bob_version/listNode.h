#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x)
	{
		val = x;
		next = NULL;
	}
};

