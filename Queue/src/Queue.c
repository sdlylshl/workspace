/*
 * Queue.c
 *
 *  Created on: 2015年2月9日
 *      Author: star
 */

#include"Queue.h"
#include<stdlib.h>
#include<stdio.h>

	unsigned char buff[4]={1,2,3,4};
/*构造一个空队列*/
Queue *InitQueue()
{
    Queue *pqueue = (Queue *)malloc(sizeof(Queue));
    if(pqueue!=NULL)
    {
        pqueue->head = NULL;
        pqueue->tail = NULL;
        pqueue->size = 0;
    }
    return pqueue;
}

/*销毁一个队列*/
void DestroyQueue(Queue *pqueue)
{
    if(IsEmpty(pqueue)!=1)
        ClearQueue(pqueue);
    free(pqueue);
}

/*清空一个队列*/
void ClearQueue(Queue *pqueue)
{
    while(IsEmpty(pqueue)!=1)
    {
        DeQueue(pqueue,NULL);
    }

}

/*判断队列是否为空*/
int IsEmpty( Queue *const pqueue)
{
    if(pqueue->head==NULL&&pqueue->tail==NULL&&pqueue->size==0)
        return 1;
    else
        return 0;
}

/*返回队列大小*/
int GetQueueSize( Queue *const pqueue)
{
    return pqueue->size;
}

/*返回队头元素*/
Node * GetQueueHead( Queue *const pqueue,Item *pitem)
{
    if(IsEmpty(pqueue)!=1&&pitem!=NULL)
    {
        pitem = pqueue->head->data;
    }
    return pqueue->head;
}

/*返回队尾元素*/

Node * GetQueueTail( Queue *const pqueue,Item *pitem)
{
    if(IsEmpty(pqueue)!=1&&pitem!=NULL)
    {
        pitem = pqueue->tail->data;
    }
    return pqueue->tail;
}

/*将新元素入队*/
Node * EnQueue(Queue *pqueue,Item * pitem)
{
	int a =sizeof(Node);
	Node * pnode = (Node *)malloc(sizeof(Node));
    if(pnode != NULL)
    {
        pnode->data = pitem;
        pnode->next = NULL;

        if(IsEmpty(pqueue))
        {
            pqueue->head = pnode;
        }
        else
        {
            pqueue->tail->next = pnode;
        }
        pqueue->tail = pnode;
        pqueue->size++;
    }
    return pnode;
}

/*队头元素出队*/
Node * DeQueue(Queue *pqueue,Item *pitem)
{
    Node * pnode = pqueue->head;
    if(IsEmpty(pqueue)!=1&&pnode!=NULL)
    {
        if(pitem!=NULL)
            pitem = pnode->data;
        pqueue->size--;
        pqueue->head = pnode->next;
        free(pnode);
        if(pqueue->size==0)
            pqueue->tail = NULL;
    }
    return pqueue->head;
}

/*遍历队列并对各数据项调用operate函数*/
void QueueTraverse(Queue *pqueue,void (*operate)())
{
    Node * pnode = pqueue->head;
    int i = pqueue->size;
    while(i--)
    {
    	operate(pnode->data);
        pnode = pnode->next;
    }

}


void print(Item *i)
{
    printf("该节点元素为%d\n",i->id);
}
int main(void)
{
    Queue *pq = InitQueue();
    int i;
    Item items ={
    		10,9,8,7,6
    };
    printf("0-9依次入队并输出如下：\n");
    for(i=0;i<10;i++)
    {
        EnQueue(pq,&items);
        GetQueueTail(pq,&items);
        printf("%d ",items.id);
    }

    printf("\n从队头到队尾遍历并对每个元素执行print函数：\n");
    QueueTraverse(pq,print);

    printf("队列中元素依次出队列并输出如下：\n");
    for(i=0;i<10;i++)
    {
        DeQueue(pq,&items);
        printf("%d ",items.used);
    }
    ClearQueue(pq);
    if(IsEmpty(pq))
        printf("\n将队列置空成功\n");
    DestroyQueue(pq);
    printf("队列已被销毁\n");

    return 0;
}

