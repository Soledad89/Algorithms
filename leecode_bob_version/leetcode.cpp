string addBinaryString(string a, string b){
	string result;
	const size_t n = a.size() > b.size() ? a.size(): b.size();
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	int carry = 0; 
	for (size_t i = 0; i < n; i++){
		const int ai = i < a.size() ? a[i] - '0' : 0;
		const int bi = i < b.size() ? b[i] - '0' : 0;
		const int val = (ai + bi + carry) % 2;
		carry = (ai + bi + carry) / 2;
		result.insert(result.begin(), val+'0');
	}

	if (carry == 1){
		result.insert(result.begin(), '1');
	}

	return result;
}


void addDigits(vector<int> &digits, int digit)
{
	int c = digit;

	for (auto it = digits.rbegin(); it != digits.rend(); ++it)
	{
		*it += c;
		c = *it / 10;
		*it %= 10;
	}

	if (c > 0)
		digits.insert(digits.begin(), 1);
}


struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(nullptr) {}
};


ListNode *addTwoNumbers(ListNode *l1, ListNode *l2){
	ListNode dummy(-1);
	int carry = 0;
	ListNode *prev = &dummy;

	for (ListNode *pa = l1, *pb = l2;
			pa != nullptr || pb != nullptr;
			pa = pa == nullptr ? nullptr : pa->next,
			pb = pb == nullptr ? nullptr : pb->next,
			prev = prev->next){
		const int ai = pa == nullptr ? 0: pa->val;
		const int bi = pb == nullptr ? 0: pb->val;
		const int value = (ai + bi + carry) % 10;
		carry = (ai + bi + carry) / 10;
		prev->next = new ListNode(value);
	}

	if (carry > 0)
		prev->next = new ListNode(carry);
	return dummy.next;
}


int atoi_string2integer(const char* str){
	int num = 0; 
	int sign = 1;
	const int n = strlen(str);
	int i = 0;

	//while (str[i] ==' ' && i < n)
	while (isspace(str[i]) && i < n)
		i++;

	if (str[i] == '+'){
		i++;
	}else if (str[i] == '-'){
		sign = -1;
		i++;
	}

	for (; i < n; i++){
	    //	if (str[i] < '0' || str[i] > '9')
		if (!isdigit(str[i])
				break;
		if (num > INT_MAX/10 || (num == INT_MAX / 10 &&
					(str[i] - '0') > INT_MAX % 10)){
			return sign == -1 ? INT_MIN: INT_MAX;
		}

		num = num * 10 + str[i] - '0';
	}

	return num*sign;
}
int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
	int total = 0;
	int j = -1;

	for (int i = 0, sum = 0; i < gas.size(); ++i){
		sum += gas[i] - cost[i];
		total += gas[i] - cost[i];
		if (sum < 0) {
			j = i;
			sum = 0;
		}
	}
	return total >= 0 ? j + 1 : -1;
}


int candyGiven(vector<int> &ratings)
{
	const int n = ratings.size();
	vector<int> increment(n);

	//scan from left to right 
	for (int i = 1, inc = 1; i < n; i ++){
		if (ratings[i] > ratings[i-1])
			increment[i] = max(inc++, increment[i]);
		else
			inc = 1;
	}

	//scan from right to left
	for (int i = n - 1, inc = 1; i >= 0; i--){
		if (ratings[i] > ratings[i+1])
			increment[i] = max(inc++, increment);
		else
			inc = 1;
	}

	return accumulate(&increment[0], &increment[0] + n, n);
}


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

int evalRPN(vector<string> &tokens){
	stack<string> s;
	for (auto token: tokens){
		if (!is_operator(token))
			s.push(token);
		else {
			int y = stoi(s.top());
			s.pop();
			int x = stoi(s.top());
			s.pop();
			if (token[0] == '+')	x += y;
			else if (token[0] == '-')	x -= y;
			else if (token[0] == '*')	x *= y;
			else						x /= y;
			s.push(to_string(x));
		}
	}
	return stoi(s.top());
}

bool is_operator(const string *op){
	return op.size() == 1 && string("+-*/").find(op) != string::npos;
}

unsigned int binary_to_gray(unsigned int n)
{
	return n ^ (n >> 1);
}


vector<int> grayCode(int n)
{
	vector<int> result;
	const size_t size = 1 << n;
	result.reserve(size);
	for (size_t i = 0; i < size; ++i)
		result.push_back(binary_to_gray(i));
	return result;
}


bool hasPathSum(TreeNode* root, int sum){
	if (root == NULL) return false;

	if (root->left == NULL && root->right == NULL)
		return sum == root->val;

	return hasPathSum(root->left, sum - root->val) ||
		hasPathSum(root->right, sum - root->val);
}


bool isMatch(const char *s, const char *p){
	if (*p == '\0') return *s == '\0';

	//next char is not '*', then must current characters
	if (*(p+1) != '*'){
		if (*p == *s || (*p == '.'&& *s != '\0')){
				return isMatch(s + 1, p + 1);
		}else { //next char is '*'
			while (*p == *s || (*p == '.' && *s != '\0')){
				if (isMatch(s, p+2))
						return true;
				s++;
			}
			return isMatch(s, p+2);
		}
	}
}



bool isMatch_iterate(const char *s, const char *p){
	bool star = false;
	const char *str, *ptr;
	for (str = s, ptr = p; *str != '\0'; str++, ptr++){
		switch (*ptr){
			case '?': 
				break;
			case '*':
				star = true;
				s = str, p = ptr;
				while (*p == '*')
					p++;//skip continuous '*'
				if (*p == '\0') return true;
				str = s - 1;
				ptr = p - 1;
				break;
			default:
				if (*str != *ptr){
					//如果前面没有‘*’，则匹配不成功
					if (!star)
						return false;
					s++;
					str = s- 1;
					ptr = p -1;
				}
		}
	}
	while (*ptr == '*')
		ptr++;
	return (*ptr == '\0');
}

bool isPalindrome(string s){
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	auto left = s.begin(), right = prev(s.end());
	while(left < right){
		if (!::isalnum(*left))
			++left;
		else if (!::isalnum(*right))
			--right;
		else if (*left != *right)
			return false;
		else {
			left++;
			right--;
		}

	}
	return true;
}


int lengthOfLastWord(const char *s)
{
	int len = 0;
	while (*s){
		if (*s++ != ' ')
			++len;
		else if (*s && *s != ' ')
			len = 0;
	}
	return len;
}

#include "listNode.h"

ListNode* listDetectCycle(ListNode* head){
	ListNode* slow = head, *fast = head;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast){
			ListNode * slow2 = head;
			while (slow2 != slow){
				slow2 = slow2->next;
				slow = slow->next;
			}
			return slow2;
		}
	}
	return NULL;
}

#include "listNode.h"

bool listHasCycle(ListNode* head){
	ListNode *slow = head;
	ListNode *fast = head;
	while (fast && fast->next){
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) return true;
	}

	return false;
}

string longestCommonPrefix(vector<string> &strs){
	if (strs.empty()) return "";

	for (int idx = 0; idx < strs[0].size(); ++idx){
		for (int i = 1; i < strs.size(); ++i){
			if (strs[i][idx] != strs[0][idx])
				return strs[0].substr(0,idx);
		}
	}
	return strs[0];
}

#include <vector>
#include <unordered_map>

int longestConsecutive(const vector<int> &num)
{
	unordered_map<int, bool> used;
	int longest = 0;
	for (auto i : num)
	{
		if (used[i]) continue;
		int length = 0;
		used[i] = true;
		for (int j = i + 1; used.find(j) != used.end(); ++j)
		{
			used[j] = true;
			++length;
		}

		for (int j = i - 1; used.find(j) != used.end(); --j)
		{
			used[j] = true;
			++length;
		}
		longest = max(longest, length);
	}
	return longest;
}


int longestValidParentheses(string s)
{
	int max_len = 0, last = -1;
	stack<int> lefts;

	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '(')
			lefts.push(i);
		else {
			if (lefts.empty())
				last = i;
			else {
				lefts.pop();
				if (lefts.empty())
					max_len = max(max_len, i-last);
				else
					max_len = max(max_len, i-lefts.top());
			}
		}
	}
	return max_len;
}

void mergeSortedArray(int A[], int m, int B[], int n){
	int ia = m - 1, ib = n - 1, icur = m + n - 1;
	while (ia >= 0 && ib >= 0){
		A[icur--] = A[ia] >= B[ib] ? A[ia--] : B[ib--];
	}

	while (ib >= 0){
		A[icur--] = B[ib--];
	}
}

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


int minimumDepthofBinaryTree(const TreeNode *root, bool hasbrother){
	if (!root) return hasbrother ? INT_MAX : 0;

	return 1 + min(minimumDepthofBinaryTree(root->left, root->right != NULL),
			minimumDepthofBinaryTree(root->right, root->left != NULL));
}

int maxDepthOfBinaryTree(TreeNode* root){
	if (root == NULL) return 0;

	return max(maxDepthOfBinaryTree(root->left), maxDepthOfBinaryTree(root->right)) + 1;
}

char* myStrStr(const char* haystack, const char* needle){
	if (*needle == NULL) return (char*)haystack;

	const char* p1;
	const char* p2;
	const char* p1_advance = haystack;

	for (p2 = &needle[1]; *p2; ++p2){
		p1_advance++;
	}

	for (p1 = haystack; *p1_advance; p1_advance++){
		char* p1_old = (char*) p1;
		p2 = needle;
		while (*p1 && *p2 && *p1 == *p2){
			p1++;
			p2++;
		}

		if(*p2 == NULL) return p1_old;
		p1 = p1_old + 1;
	}
	return NULL;
}


#include "listNode.h"
ListNode* partitionList(ListNode* Head, int x)
{
	ListNode left_dummy(-1);
	ListNode right_dummy(-1);

	auto left_cur = &left_dummy;
	auto right_cur = &right_dummy;

	for (ListNode *cur = Head; cur; cur = cur->next)
	{
		if (cur->val < x){
			left_cur->next = cur;
			left_cur = cur;
		}
		else{
			right_cur->next = cur;
			right_cur = cur;
		}
		left_cur->next = right_dummy.next;
		right_cur->next = nullptr;
	}
}



void pathSum(TreeNode* root , int gap, vector<int> &cur, 
		vector<vector<int> > &result){
	if (root == NULL) return ;

	cur.push_back(root->val);

	if (root->left == NULL && root->right == NULL) {
		if (gap == root->val)
			result.push_back(cur);
	}
	pathSum(root->left, gap - root->val, cur, result);
	pathSum(root->right, gap - root->val, cur, result);

	cur.pop_back();
}


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


#include "listNode.h"

ListNode *reverseLinkedList2(ListNode *head, int m, int n)
{
	ListNode dummy(-1);
	dummy.next = head;

	ListNode *prev = &dummy;
	for (int i = 0; i < m - 1; ++i)
		prev = prev -> next;
	ListNode* const head2 = prev;

	prev = head2->next;
	ListNode *cur = prev->next;
	for (int i = m; i < n; i++){
		prev->next = cur->next;
		cur->next = head2->next;
		head2->next = cur;
		cur = prev->next;
	}
	return dummy.next;
}




void rotateImage(vector<vector<int> > & matrix)
{
	const int n = matrix.size();

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n-1; ++j)
			swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
	}

	for (int i = 0; i < n/2; ++i)
		for (int j = 0; j < n; ++j)
			swap(matrix[i][j], matrix[n-1-i][j]);
}


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


void setMatrixZeros(vector<vector<int> > &matrix)
{
	const size_t m = matrix.size();
	const size_t n = matrix[0].size();
	vector<bool> row(m, false);
	vectro<bool> col(n, false);

	for (size_t i = 0; i < m; ++i)
	{
		for (size_t j = 0; j < n; ++j)
			if (matrix[i][j] == 0)
				row[i] = col[j] = true;
	}

	for (size_t i = 0; i < m ; ++i)
		if (row[i])
			fill(&matrix[i][0], &matrix[i][0] + n, 0);
	
	for (size_t j = 0; j < n; ++j)
		if (col[j]){
			for (size_t i = 0; i < m; ++i)
				matrix[i][j] = 0;
		}
}


int singleNumber(int A[], int n){
	int x = 0;
	for (size_t i = 0; i < n; i++)
		x ^= A[i];
	return x;
}


int singleNumber2(int A[], int n){
	const int W = sizeof(int) * 8;
	int count[W];
	fill_n(&count[0], W, 0);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < W; j++){
			count[j] += (A[i] >> j) & 1;
			count[j] %= 3;
		}
	}

	int result = 0; 
	for(int i = 0; i < W; i++)
		result += (count[i] << i);

	return result;
}



int sumNumbers(TreeNode *root, int sum) {
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return sum * 10 + root->val;

	return sumNumbers(root->left, sum * 10 + root->val) +
		sumNumbers(root->right, sum * 10 + root->val);
}

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



vector<vector<int> > threeSum(vector<int> & num)
{
    vector<vector<int> > result;
    if (num.size() < 3) return result;
    sort(num.begin(), num.end());
    const int target = 0;

    auto last = num.end();
    for (auto i = num.begin(); i < last - 2; ++i)
    {
        auto j = i + 1;
        if (i > num.begin() && *i = *(i-1)) continue;
        auto k = last - 1;
        while (j < k)
        {
            if (*i + *j + *k < target)
            {
                ++j;
                while ( *j == *(j - 1) && j < k ) ++j;
            }
            else if ( *i + *j + *k > target)
            {
                --k;
                while (*k == *(k + 1) && j < k) --k;
            }
            else
            {
                result.push_back({*i, *j, *k});
                ++j;
                --k;
                while ( *j == *(j - 1) && *k == *(k + 1) && j < k) ++j;
            }
        }
    }
    return result;
}


int threeSumClosest(vector<int> &num, int target)
{
    int result = 0;
    int min_gap = INT_MAX;
    sort(num.begin(), num.end());
    for (auto a = num.begin(); a != prev(num.end(), 2); ++a)
    {
        auto b = next(a);
        auto c = prev(num.end());
        
        while (b < c)
        {
            const int sum = *a + *b + *c;
            const int gap = abs(sum - target);

            if (gap < min_gap)
            {
                result = sum;
                min_gap = gap;
            }

            if (sum < target) ++b;
            else              --c;
        }
    }
    return result;
}

int trappingRainWater(int A[], int n)
{
	int *max_left = new int[n]();
	int *max_right = new int[n]();

	for (int i = 1; i < n ; i++)
	{
		max_left[i] = max(max_left[i-1], A[i-1]);
		max_right[n - i - 1] = max(max_right[n - i], A[n - i]);
	}
	int sum = 0;
	for (int i = 0; i < n; i++){
		int height = min(max_left[i], max_right[i]);
		if (height > A[i])  sum += height - A[i];
	}

	delete[] max_left;
	delete[] max_right;
	return sum;
}


int trappingRainWater2(int a[], int n)
{
	int max = 0;
	for (int i = 0; i < n; i++){
		if (A[i] > A[max]) max = i;
	}

	int water = 0;
	for (int i = 0, peak = 0; i < max; i++){
		if (A[i] > peak) peak = A[i];
		else
			water += peak - A[i];
	}

	for (int i = n - 1, top = 0; i > max; i--){
		if (A[i] > top) top = A[i];
		else
			water += = top - A[i];
	}

	return water;
}


int binsearch(int x, int A[], int n)
{
	int low, mid, high;
	low = 0; 
	high = n-1;
	while (low <= high)
	{
		mid = (low + high)/2;
		if (x < A[mid])
			high = mid - 1;
		else if (x > A[mid])
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}



int find_kth(int A[], int m, int B[], int n, int k);
// time: O(log(m+n); space: O(log(m+n))
int fubdMedianSortedArray(int A[], int m,  int B[], int n)
{
	int total = m + n;
	if (total & 0x1)				/*test if total is a odd number*/
		return find_kth(A, m, B, n, total / 2 + 1);
	else
		return (find_kth(A, m, B, n, total/2) + find_kth(A, m, B, n, total/2 + 1) / 2.0;

}

int find_kth(int A[], int m, int B[], int n, int k)
{ //always assume thtat m is smaller than n
	if (m > n) return find_kth(B, n, A, m, k);
	if (m == 0) return B[k-1];
	if (k == 1) return min(A[0], B[0]);
	//divide k int two parts
	int is = min(k/2, m), ib = k - ia;
	if (A[is-1] < B[ib-1])
		return find_kth(A + ia, m - ia, B, n, k - ia);
	else if (A[ia-1] > B[ib-1])
		return find_kth(A, m, B + ib, n - ib, k - ib);
	else
		return A[ia -1];
}



	
int removeElement(int A[], int n, int target)
{
	int index = 0;
	int i;
	for (i = 0; i < n; ++i)
	{
		if (A[i] != elem) 
			A[index++] = A[i];
	}
	return index;
}


int remove_duplicates(int a[], int num)
{
	if (num == 0) return 0;
	int i, index = 0;
	for (i = 1; i < num; i++)
		if (a[index] != a[i])
			a[++index] = a[i];
	return index+1;
}

int remove_duplicates2(int a[], int num)
{
	if (num == 0) return 0;
	int i, flag = 0, index = 0;
	for (i = 1; i < num; i++)
		if (a[index] != a[i])
			a[++index] = a[i];
		else{
			if (a[i] == a[i+1])
				i++;
			else
				a[++index] = a[i];
		}

	return index+1;
}

int remove_duplicates3(int a[], int num)
{
	if (num < 3) return num;
	int i, index = 2;
	for (i = 2; i < num; i++)
		if (a[i] != a[index-2])
			a[index++] = a[i];
	return index;
}



int search_in_rotated_sorted_array(int x, int A[], int num)
{
    int first = 0, last = num;
    while (first != last)
    {
        const int mid = first + (last - first) / 2;
        if (A[mid] == x)
            return mid;
        if (A[first] <= A[mid])
        {
            if (A[first] <= x && x < A[mid])
                last = mid;
            else
                first = mid + 1;
        }
        else
        {
            if (A[mid] < x && x <= A[last - 1])
                first = mid - 1;
            else
                last = mid;
        }
    }
    return -1;

}
#include <stdio.h>

int main()
{
	int i;
	for (i = 0; i < 5; i++)
		if ( i == 4)
			break;/*after break occurs, no other program will be executed*/

	printf("%d\n", i);
	return 0;
}

vector<int> twoSum(vector<int> &num, int target)
{
    unordered_map<int, int> mapping;
    vector<int> result;
    for (int i = 0; i < num.size(); i++)
    {
        mapping[num[i]] = i;
    }

    for (int i = 0; i < num.size(); i++)
    {
        const int gap = target - num[i];
        if (mapping.find(gap) != mapping.end() && mapping[gap] > i)
        {
            result.push_back(i + 1);
            result.push_back(mapping[gap] + 1);
            break;
        }
    }

    return result;
}

