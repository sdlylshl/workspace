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
int InitQueue(LinkQueue &Q)             //�����ն���
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}
int EnQueue(LinkQueue &Q,int e)        //����
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
int DeQueue(LinkQueue & Q,int &e)      //����
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

void creat(LinkQueue &Q,int n)           //�����¶���
{
	
	int i,data;
	for(i=1;i<=n;i++)
	{
		cout<<"�������"<<i<<"��Ԫ��"<<endl;
		cin>>data;
		EnQueue(Q,data);
	}


}
int show(LinkQueue Q)                    //��ʾ������
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
		cout<<"������ѡ�"<<endl;
		cout<<"1:�����¶��У�2�����ӣ�3�����ӣ�0���˳� "<<endl;
		cin>>k;
		switch(k)
		{case 1: cout<<"�¶���Ԫ�ظ�����"<<endl;
				 cin>>n;
				 creat(Q1,n);
				 show(Q1);
				 break;
		case 2: 
				cout<<"���������Ԫ�أ�"<<endl;
				cin>>e;
				EnQueue(Q1,e);
				cout<<"���Ӻ󣬶���Ϊ��   ";
				show(Q1);
				break;
		case 3:
				DeQueue(Q1,e);
			   cout<<"����Ԫ�أ�e="<<e<<endl;
			   cout<<"���Ӻ󣬶���Ϊ��   ";
				show(Q1);
				break;
		case 0: return 0;
		default:cout<<"��������"<<endl;break;
		}
	}while(k);
	return 0;
}
