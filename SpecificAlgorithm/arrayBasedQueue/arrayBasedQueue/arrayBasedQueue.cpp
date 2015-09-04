#include <stdio.h>
#include <stdlib.h>

struct QueueNOde;
typedef struct QueueNode *Queue;

#define MAXSIZE 10

struct QueueNode
{
	int front;
	int rear;
	int count;
	int Array[MAXSIZE];
};

/*
 * 创建 队列。
 */
Queue CreateQueue()
{
	Queue queue;
	queue = (Queue) malloc (sizeof(Queue));
	if (queue == NULL){
		printf("No space!!!\n");
	}
    
	queue->count = 0;
	queue->rear = -1;
	queue->front = 0;
	
	return queue;
}



/*
 * if full ,return 0; else return 1;
 */
int IsFull(Queue queue)
{
	return (queue->count == MAXSIZE);
}

/* if null return 1. else 0 */
int IsEmpty(Queue queue)
{
	return (queue->count == 0);
}

/*
 * 打印队列。
 */
void DisplayQueue(Queue queue)
{
	printf("queue->Front = %d\n", queue->front);
	printf("queue->Rear = %d\n", queue->rear);
	if (!IsEmpty(queue)){
        int i = queue->front;
        int dest = queue->rear;
        while (i != dest) {
            i = i % MAXSIZE;
            printf("%d  ", queue->Array[i]);
            i++;
        }
        
	}
}

/* 进队 */
void Enqueue(Queue queue, int a)
{
    if (IsFull(queue)) {
        printf("Ooops, it is full\n");
        return;
    }
    int enIndex = (queue->rear == MAXSIZE - 1) ? 0 : (queue->rear + 1);
	queue->Array[enIndex] = a;
    queue->rear = enIndex;
	queue->count++;
	
}

/* 出队 */
void Dequeue(Queue queue)
{
    if (IsEmpty(queue)) {
        printf("Ooops, it is empty\n");
        return;
    }
    int deIndex = (queue->front == MAXSIZE - 1) ? 0 : (queue->front + 1);
    queue->front = deIndex;
	queue->count--;
	
}

int main(void)
{
    Queue queue;
	queue = CreateQueue();
	Enqueue(queue, 1);
    DisplayQueue(queue);
	Enqueue(queue, 2);
    DisplayQueue(queue);
	Enqueue(queue, 3);
    DisplayQueue(queue);
	Enqueue(queue, 4);
    DisplayQueue(queue);
	Enqueue(queue, 5);
    DisplayQueue(queue);
	Enqueue(queue, 6);
    DisplayQueue(queue);
	Dequeue(queue);
    DisplayQueue(queue);
    Dequeue(queue);
    DisplayQueue(queue);
    Dequeue(queue);
    DisplayQueue(queue);
    Dequeue(queue);

	Enqueue(queue, 12);
    Enqueue(queue, 13);
    Enqueue(queue, 14);
    Enqueue(queue, 15);
    Enqueue(queue, 16);
    Enqueue(queue, 17);
	DisplayQueue(queue);
    return 0;
	
}



