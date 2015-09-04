/* By Vamei */

/* 
 * leftist heap
 * bassed on binary tree 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node *position;
typedef int ElementTP;

struct node {
    ElementTP element;
    int npl;
    position lchild;
    position rchild;
};

typedef struct node *LHEAP;

LHEAP insert(ElementTP, LHEAP);
ElementTP find_min(LHEAP);
LHEAP delete_min(LHEAP);
LHEAP merge(LHEAP, LHEAP);
static LHEAP merge1(LHEAP, LHEAP);
static LHEAP swap_children(LHEAP);

int main(void)
{
    LHEAP h1=NULL;
    LHEAP h2=NULL;
    h1 = insert(7, h1);
    h1 = insert(3, h1);
    h1 = insert(5, h1);

    h2 = insert(2, h2);
    h2 = insert(4, h2);
    h2 = insert(8, h2);

    h1 = merge(h1, h2);
    printf("minimum: %d\n", find_min(h1));
    return 0;
}

/*
 * insert:
 * merge a single-node leftist heap with a leftist heap
 * */
LHEAP insert(ElementTP value, LHEAP h)
{
    LHEAP single;
    single = (position) malloc(sizeof(struct node));

    // initialze
    single->element  = value;
    single->lchild   = NULL;
    single->rchild   = NULL;

    return  merge(single, h);
}

/*
 * find_min:
 * return root value in the tree
 * */
ElementTP find_min(LHEAP h)
{
    if(h != NULL) return h->element;
    else exit(1);
}

/*
 * delete_min:
 * remove root, then merge two subheaps
 * */
LHEAP delete_min(LHEAP h)
{
    LHEAP l,r;
    l = h->lchild;
    r = h->rchild;
    free(h);
    return merge(l, r);
}

/*
 * merge two leftist heaps
 * */
LHEAP merge(LHEAP h1, LHEAP h2) 
{

    // if one heap is null, return the other
    if(h1 == NULL) return h2;
    if(h2 == NULL) return h1;

    // if both are not null
    if (h1->element < h2->element) { 
        return merge1(h1, h2);
    }
    else {
        return merge1(h2, h1);
    }
}

// h1->element < h2->element
static LHEAP merge1(LHEAP h1, LHEAP h2)
{
    if (h1->lchild == NULL) { 
        /* h1 is a single node, npl is 0 */
        h1->lchild = h2; 
    /* rchild is NULL, npl of h1 is still 0 */
    }
    else {
        // left is not NULL
    // merge h2 to right
    // swap if necessary
        h1->rchild = merge(h1->rchild, h2);
    if(h1->lchild->npl < h1->rchild->npl) {
        swap_children(h1);
    }
        h1->npl = h1->rchild->npl + 1; // update npl
    }
    return h1;
}

// swap: keep leftist property
static LHEAP swap_children(LHEAP h) 
{
    LHEAP tmp;
    tmp       = h->lchild;
    h->lchild = h->rchild;
    h->rchild = tmp;
}