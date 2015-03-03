/*
 * Queue.h
 *
 *  Created on: 2015年2月9日
 *      Author: star
 */


#ifndef Queue_H
#define Queue_H

//单链表实现的队列
//typedef unsigned char * Item;
typedef struct _data{
	unsigned int id;
	unsigned char checksum;
	unsigned char used;	//数据有效
	unsigned char regedit;//注册到链表中
	unsigned char resend;//发送次数
}Item;
//typedef struct node * PNode;
//定义节点数据
//队列节点包含队列指针 和 数据成员
typedef struct node
{
    Item *data;
    struct node * next;
}Node;
//队列由队列节点组成
typedef struct
{
	Node * head;
	Node * tail;
    int size;
}Queue;

//1.创建一个队列并初始化为空 Queue RecvQueue={0};
//2.创建一个节点 Node RecvNode[100];
//3.将节点添加进队列
/*构造一个空队列*/
Queue *InitQueue();

/*销毁一个队列*/
void DestroyQueue(Queue *pqueue);

/*清空一个队列*/
void ClearQueue(Queue *pqueue);

/*判断队列是否为空*/
int IsEmpty(Queue * const pqueue);

/*返回队列大小*/
int GetQueueSize(Queue * const pqueue);

/*返回队头元素*/
Node * GetQueueHead(Queue * const pqueue,Item *pitem);

/*返回队尾元素*/
Node * GetQueueTail(Queue * const pqueue,Item *pitem);

/*将新元素入队尾*/
Node * EnQueue(Queue *pqueue,Item * pitem);

/*队头元素出队*/
Node * DeQueue(Queue *pqueue,Item *pitem);

/*遍历队列并对各数据项调用visit函数*/
void QueueTraverse(Queue *pqueue,void (*operate)());

#endif
