    

#include<iostream>
using namespace std;
#define listinitsize 100
typedef struct
{int *elem;
 int length;
 int listsize;
}sqlist;
sqlist l1;
int m;

void  initlist(int m)                 //����˳���
{int n,i,*p;
  l1.elem=(int *)malloc(listinitsize*sizeof(int));
  l1.listsize=listinitsize;
 cout<<"������"<<m<<"������"<<endl;
   p=l1.elem+1;
  for(i=1;i<=m;i++)
    {
		cin>>n;
     *p=n;
      p++;}
   for(i=1;i<=m;i++)
   {cout<<l1.elem[i]<<" ";
   }
   cout<<endl;
}

  void  listinsert(int i,int e)          //����Ԫ��
 {int j;
 if(i<1||i>m+1)
printf("i is error");
 else
{ for(j=m;j>=i;j--)
  l1.elem[j+1]=l1.elem[j];
  l1.elem[i]=e;
    m++;
    for(i=1;i<=m;i++)
    cout<<l1.elem[i];
  cout<<endl;}
 }

void listdelete(int i,int e)               //ɾ��Ԫ��
{int j;
 if(i<1||i>m)
 printf("i is error");
 else
 {e=l1.elem[i];
  for(j=i+1;j<=m;j++)
  l1.elem[j-1]=l1.elem[j];
   m--;
  cout<<"e="<<e<<endl;
  for(j=1;j<=m;j++)
  cout<<l1.elem[j];
  cout<<endl;}
 }

 int   main()
{ int i,e,j,k;
 
 do
  {  
	 cout<<"*******************************"<<endl;
	 cout<<"������ѡ�"<<endl;
	 cout<<"1:  ����     2:  ɾ��      3:  ����    0:  �˳�"<<endl;
     cin>>k;
	 switch(k)
	 {
	   case '1':
	   printf("����������λ�ã�");
	   cin>>i;
	   printf("������Ԫ�أ�");
	   cin>>e; 
	   listinsert(i,e);
	   break;
	   case '2':
	   printf("������Ҫɾ��Ԫ�ص�λ�ã�");
	   cin>>j;
	   listdelete(j,e);
	   break;
       case '3':
	   cout<<"������Ҫ������ĳ��ȣ�"<<endl;
       cin>>m;
       initlist(m); 	
	   break;
	   case '0':return 0;
	   default:cout<<"��������"<<endl;break;
	 }
  }while(k);
  return 0;
}