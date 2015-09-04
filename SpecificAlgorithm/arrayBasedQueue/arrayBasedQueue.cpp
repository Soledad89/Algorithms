#include <stdio.h>
#include <stdlib.h>

struct QueueRecord;
typedef struct QueueRecord *Queue;

#define MinQueueSize (5)

struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	int *Array;
};

/*
 * 创建 队列。
 */
Queue CreateQueue(int capacity)
{
	Queue queue;
	queue = (Queue)malloc(sizeof(Queue));
	if (queue == NULL)
	{
		printf("out of space!!!\n");
	}
	queue->Array = (int *)malloc(capacity * sizeof(int));
	if (queue->Array == NULL)
	{
		printf("out of space!!!\n");
	}
	queue->Size = 0;
	queue->Rear = -1;
	queue->Front = 0;
	
	return queue;
}



/*
 * if full ,return 0; else return 1;
 */
int IsFull(Queue queue, int capacity)
{
	return (queue->Size < capacity);
}

/* if null return 1. else 0 */
int IsEmpty(Queue queue)
{
	return (queue->Size == 0);
}

/*
 * 打印队列。
 */
int ShowQueue(Queue queue, int capacity)
{
	int i;
	
	printf("queue->Front = %d\n", queue->Front);
	printf("queue->Rear = %d\n", queue->Rear);
	if (!IsEmpty(queue))
	{
		for (i = queue->Front; i <= queue->Rear; i++)
			{
				if (i < queue->Rear)
				{
					printf("%d, ", queue->Array[i]);	
				}
				else
				{
					printf("%d ", queue->Array[i]);
				}

			}
	}
	else
	{
		printf("oh, sorry. it is empty.");
	}

}
/* 进队 */
void Enqueue(Queue queue, int a, int capacity)
{
	queue->Rear++;
	queue->Array[queue->Rear] = a;
	queue->Size++;

	if (IsFull(queue, capacity))
	{
		if (queue->Rear == capacity)
		{
			queue->Rear = 0;
		}
			
	}
	
}

/* 出队 */
void Dequeue(Queue queue, int capacity)
{
	queue->Front++;
	queue->Size--;
	
	if (IsFull(queue, capacity))
	{
		if (queue->Front== capacity)
		{
			queue->Front = 0;
		}
			
	}
}

int main(void)
{
	Queue queue;
	int capacity = 10;
	if (capacity < MinQueueSize)
	{
		printf("it is too small.\n");
	}
	
	queue = CreateQueue(capacity);
	Enqueue(queue, 1, capacity);
	Enqueue(queue, 2, capacity);
	Enqueue(queue, 3, capacity);
	Enqueue(queue, 4, capacity);
	Enqueue(queue, 5, capacity);
	Enqueue(queue, 6, capacity);
	Dequeue(queue, capacity);
	Enqueue(queue, 12, capacity);
	//Enqueue(queue, 3, capacity);
	ShowQueue(queue, capacity);
	
}



