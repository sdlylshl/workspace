#include<iostream>
using namespace std;
# define OK 1
# define ERROR 0
# define OVERFLOW -2
typedef struct BiTNode{
	int data;
	struct BiTNode * lchild,*rchild;
}BiTNode,* BiTree;
BiTree BT1,T;
BiTree CreateBiTree(BiTree & T)
{
	int ch;
	cout<<"�������ݣ�"<<endl;
	cin>>ch;
	if(ch==0)
		T=NULL;
	else{
		T=(BiTNode *)malloc(sizeof(BiTNode));
		if(!T);
		T->data=ch;
		T->lchild=CreateBiTree(T->lchild);
        T->rchild=CreateBiTree(T->rchild);
	   }	
	return T;
}
int visit(int e)
{
	cout<<e<<' ';
	return OK;
}
int PreOrderTraverse(BiTree T)
{
	if(T)
	{
		visit(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
		return OK;
	}
	else return OK;
}
int InOrderTraverse(BiTree T)
{
 if(T)
	{
	    InOrderTraverse(T->lchild);
		visit(T->data);
		InOrderTraverse(T->rchild);
		return OK;
	}
	else return OK;
}
int PostOrderTraverse(BiTree T)
{
	if(T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		visit(T->data);
		return OK;
	}
	else return OK;
}
int main()
{
	int m,n;
	n=1;
	while(n)
	{
		cout<<"1:������2�����������3�����������4�����������0���˳� "<<endl;
		cout<<"����������ѡ��"<<endl;
		cout<<"****************************************************"<<endl;
		cin>>m;
		switch(m)
		{
		case 1: CreateBiTree(BT1);
				break;
		case 2: PreOrderTraverse(BT1);
				break;
		case 3: InOrderTraverse(BT1);
				break;
		case 4: PostOrderTraverse(BT1);
				break;
		default: n=0;
		}
	
	}
	return 0;
}
