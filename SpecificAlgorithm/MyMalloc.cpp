#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef long Align;	//定义块首对其的类型：长整型
union header {	//块首
	struct {
		union header *next; 	//指向下一空闲块的指针
		unsigned int size;  	//空闲块的大小
	} s;
	Align x;	//对齐
};

typedef union header Header;	

#define NALLOC 1024	//请求的最小单位数，设每页大小为1KB
static Header* Moresys(unsigned int nu);	//向系统申请一块内存
void* Malloc(unsigned int nbytes);	//从用户管理区申请内存
void Free(void *ap);	//释放内存，放入到用户管理区

static Header base;	//定义空闲链头
static Header *free_list = NULL;	//空闲链的起始查询指针

//用户管理区内存分配函数
void* Malloc(unsigned int nbytes)
{
	Header *p, *prev;
	unsigned int nunits;
	//将申请的字节数nbytes转换成nunits个块首单位，多计算一个作为管理块首
	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if ((prev = free_list) == NULL) {	//如果无空闲链，定义空闲链
		base.s.next = free_list = prev = &base;
		base.s.size = 0;	//
        
	}
	for (p = prev->s.next; ; p = p->s.next, prev = p) {	//遍历空闲链，查找合适空闲块
		if (p->s.size >= nunits) {	//空闲块够大
			if (p->s.size == nunits)
				prev->s.next = p->s.next;
			else {	//偏大，切出需要的一块
				p->s.size -= nunits;
				p += p->s.size;	//被分配块的起始地址
				p->s.size = nunits;	//填写被分配块大小
			}
			free_list = prev;	//记录前一空块的地址
			return(void *)(p+1);	//跳过管理块首，返回
		}

		if(p == free_list)
			if((p = Moresys(nunits)) == NULL)	//无合适块，向系统申请
				return NULL;
	}
}

//向系统申请内存空间
static Header* Moresys(unsigned int nu)
{
	char *cp;
	Header *up;

	if(nu < NALLOC)
		nu = NALLOC;	//向系统申请的最小量
	cp = (char*) sbrk(nu * sizeof(Header));
	printf("sbrk: %X -- %X\n", cp, cp + nu * sizeof(Header));	//调试用
	if(cp == (char *) -1)
		return NULL;	//无空闲页面，返回空地址
	up = (Header *)cp;	//强制转换成header结构
	up->s.size = nu;
	Free(up + 1);	//将申请到的空闲块链如用户空闲链，指向第二个header指针（free函数的要求）
	return free_list;	//返回free_list指针
}

//回收内存到空闲链上
void Free(void *ap)
{
	Header *bp, *p;
	bp = (Header *)ap - 1;	//指向块首

	for(p = free_list; !(bp>p && bp<p->s.next); p = p->s.next)	//按地址定位空闲块在链表
	//中的位置
	if(p>=p->s.next && (bp>p || bp<p->s.next))
		break;	//空闲块在两端
	if(bp + bp->s.size == p->s.next) {	//看空闲块是否与已有的块相邻，相邻就合并
		bp->s.size += p->s.next->s.size;
		bp->s.next = p->s.next->s.next;
	}
	else
		bp->s.next = p->s.next;
   
	if(p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.next = bp->s.next;
	}
	else 
		p->s.next = bp;

	free_list = p;
}

//打印内存分配结果函数
void print_list(void)
{
	Header *p;
	int i = 0;
	printf("base: %X, base.next: %X, base.next.next: %X, free: %X\n", 
	&base, base.s.next, base.s.next->s.next, free_list);
	for (p = base.s.next; p != &base; p = p->s.next) {
		i++;
		printf("block %d, size=%d", i, p->s.size);
		if(p > free_list)
			printf(" It is not searched after this point. \n");
		else
			printf(" It is a searched free block!\n");
	}
}

//测试编写的malloc函数
int main()
{
	char *p[200];
	int i;
    int n_ = sizeof(Header);

	for(i = 0; i < 20; i++ ) {
		p[i] = (char *)Malloc(8);
		printf("malloc %d, %s\n", i , p[i]);
		print_list();
	}

	for (i =0; i < 20; i++) {
		Free(p[i]);
		printf("free %d\n", i);
		print_list();
	}
	return 0;
}