#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* 树结点的设计 */
typedef struct node
{
    /* 数字和运算符 */
    union
    {
        char oper;
        int data;
    };

    struct node *lchild;
    struct node *rchild;
}TreeNode;

/* 树栈 */
typedef struct Tree_Stack
{
    TreeNode *buf[MAX];         //也可以用vector来实现
    int n;
}TreeStack;

/* 创建空栈 */
TreeStack *create_empty_stack()
{
    TreeStack *pstack;

    pstack = (TreeStack *)malloc(sizeof(TreeStack));
    pstack->n = 0;

    return pstack;
}

/* 入栈 */
int push_stack(TreeStack *p, TreeNode *data)
{
    p->n++;
    p->buf[p->n-1] = data;

    return 0;
}

/* 出栈 */
TreeNode *pop_stack(TreeStack *p)
{
    TreeNode *data;

    data = p->buf[p->n-1];
    p->n--;

    return data;
}

/* 判断栈空 */
int is_empty_stack(TreeStack *p)
{
    if(p->n == 0)
        return 1;
    else
        return 0;
}

/* 创建后缀表达式树 */
TreeNode *create_express_tree(char *str, TreeStack *p)
{
    int i = 0;
    TreeNode *current;
    TreeNode *left, *right;

    while(str[i])
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            current = (TreeNode *)malloc(sizeof(TreeNode));
            current->data = str[i] - '0';
            current->lchild = NULL;
            current->rchild = NULL;
            push_stack(p, current);
        }
        else
        {
            current = (TreeNode *)malloc(sizeof(TreeNode));
            current->oper = str[i];
            right = pop_stack(p);
            left = pop_stack(p);
            current->lchild = left;
            current->rchild = right;
            push_stack(p, current);
        }
        i++;
    }
    if (p->n == 1)
        return p->buf[p->n-1];
    else
        return NULL;
}

/* 打印结点 */
void print_node(TreeNode *p)
{
    if(p->lchild == NULL && p->rchild == NULL)
        printf("%d ", p->data);
    else
        printf("%c ", p->oper);
}

/* 访问结点 */
int visit_node(TreeNode *p)
{
    print_node(p);

    return 0;
}

/* 树的后序遍历 */
void PostOrder(TreeNode *p)
{
    if(p != NULL)
    {
        PostOrder(p->lchild);
        PostOrder(p->rchild);
        visit_node(p);
    }
}

/* 树的中序遍历 */
void InOrder(TreeNode *p)
{
    if(p != NULL)
    {
        InOrder(p->lchild);
        visit_node(p);
        InOrder(p->rchild);
    }
}

/* 树的前序遍历 */
void PreOrder(TreeNode *p)
{
    if(p != NULL)
    {
        visit_node(p);
        PreOrder(p->lchild);
        PreOrder(p->rchild);
    }
}

int main()
{
    TreeNode *thead;
    TreeStack *pstack;
    int i = 0;
    char buf[100];
    while (true) {
        //system("/usr/bin/clear");
        printf("please input the rpn string: \n");
        scanf("%s", buf);

        pstack = create_empty_stack();
        if (NULL == (thead = create_express_tree(buf, pstack)))
        {
            printf("illigal RNP expression: %s\n", buf); continue;
        }
        
        printf("PostOrder:  ");
        PostOrder(thead);
        printf("\n");

        printf("InOrder:  ");
        InOrder(thead);
        printf("\n");

        printf("PreOrder:  ");
        PreOrder(thead);
        printf("\n");
    }

    return 0;
}
