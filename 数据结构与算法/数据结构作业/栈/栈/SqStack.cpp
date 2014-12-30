#include<iostream>
using namespace std;
#define  STACK_INIT_SIZE 100
#define  OVERFLOW -2
#define  OK  1
#define  ERROR 0
#define  STACKINCREMENT 10
typedef struct{
         int * base;
         int * top;
         int stacksize;
}SqStack;
SqStack S1;
void Print(SqStack &S)               //���ջ
{
 int n=S.top - S.base;
 int i,*p=S.base;
 for(i=0;i<n;i++)
 {
  cout<<*p<<"\t";
  p++;
 }
 cout<<endl;
}
int Creat(SqStack &S,int n)         //����ջ
{
 S.base=(int *)malloc(STACK_INIT_SIZE*sizeof(int));
 if (!S.base) 
  exit(OVERFLOW);    
 S.top=S.base;
 S.stacksize=STACK_INIT_SIZE;
 int *a=S.base;
 int data;
 for(int i=1;i<=n;i++)
 {cout<<"�������"<<i<<"��Ԫ��"<<endl;
 cin>>data;
 *a=data;
 a++;
 S.top++;
 }
 Print(S);
 return OK;
}
int Push(SqStack &S,int e)             //����Ԫ��
{
 if(S.top-S.base>=S.stacksize)
 {
  S.base=(int *)realloc(S.base,(S.stacksize+STACKINCREMENT * sizeof(int)));
  if(!S.base)exit(OVERFLOW);
  S.top=S.base+S.stacksize;
  S.stacksize+=STACKINCREMENT;
 }
 *S.top++=e;
 cout<<"�����"<<endl;
 Print(S);
 return OK;
}
int Pop(SqStack &S,int &e)           //ɾ��Ԫ��
{
 if(S.top==S.base)
  return ERROR;
 e=*--S.top;
 Print(S);
 return OK;
}
int GetTop(SqStack S,int &e)          //ȡջ��Ԫ��
{
 if(S.top==S.base)
  return ERROR;
 e=*(S.top-1);
 return OK;
}
int main()
{
 int e,n;
 char k;
 cout<<"������ѡ�"<<endl;
 cout<<"1: ������2�� ��ջ��3�� ��ջ��4��ȡջ��Ԫ�أ�0���˳�"<<endl;
 cin>>k;
 while(k!='0')
 {
  switch(k)
  {
   case '1': cout<<"�����볤�ȣ�"<<endl;
      cin>>n;
      Creat(S1,n);
	  break;
   case '2': cout<<"������Ҫ�����Ԫ�أ�"<<endl; 
      cin>>e;
      Push(S1,e);
	  break;
   case '3': Pop(S1,e);
      cout<<"e="<<e<<endl;
	  break;
   case '4': GetTop(S1,e);
      cout<<"e="<<e<<endl;
	  S1.top--;
	  break;
   default: cout<<"Error!"<<endl;break;
  }
  cout<<"*********************************************"<<endl;
  cout<<"������ѡ��Ĺ��ܣ�"<<endl;
  cout<<"1: ������2�� ��ջ��3�� ��ջ��4��ȡջ��Ԫ�أ�0���˳�"<<endl;
  cin>>k;
 }
 return 0;
}
