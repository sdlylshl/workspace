#include<iostream>
using namespace std;
#define OK  1
#define ERROR  0
#define OVERFLOW -2
typedef struct QNode{
	int data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
int InitQueue(LinkQueue &Q)             //建立空队列
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}
int EnQueue(LinkQueue &Q,int e)        //进队
{
	QNode *p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}
int DeQueue(LinkQueue & Q,int &e)      //出对
{
	QNode *p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	free(p);
	return OK;
}

void creat(LinkQueue &Q,int n)           //创建新队列
{
	
	int i,data;
	for(i=1;i<=n;i++)
	{
		cout<<"请输入第"<<i<<"个元素"<<endl;
		cin>>data;
		EnQueue(Q,data);
	}


}
int show(LinkQueue Q)                    //显示链队列
{
	if(Q.front==Q.rear)
		return 0;
	QNode *p;
	p=Q.front->next;
	while(p)
	{
		cout<<(p->data)<<" ";
		p=p->next;
	}
	cout<<endl;
	return 0;
}

int main()
{
	int k,e,n;
	LinkQueue Q1;
	InitQueue(Q1);
	do{ 
		cout<<"********************************************"<<endl;
		cout<<"请输入选项："<<endl;
		cout<<"1:创建新队列，2：进队，3：出队，0：退出 "<<endl;
		cin>>k;
		switch(k)
		{case 1: cout<<"新队列元素个数："<<endl;
				 cin>>n;
				 creat(Q1,n);
				 show(Q1);
				 break;
		case 2: 
				cout<<"请输入进队元素："<<endl;
				cin>>e;
				EnQueue(Q1,e);
				cout<<"进队后，队列为：   ";
				show(Q1);
				break;
		case 3:
				DeQueue(Q1,e);
			   cout<<"出队元素：e="<<e<<endl;
			   cout<<"出队后，队列为：   ";
				show(Q1);
				break;
		case 0: return 0;
		default:cout<<"输入有误！"<<endl;break;
		}
	}while(k);
	return 0;
}
