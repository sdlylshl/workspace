    

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

void  initlist(int m)                 //建立顺序表
{int n,i,*p;
  l1.elem=(int *)malloc(listinitsize*sizeof(int));
  l1.listsize=listinitsize;
 cout<<"请输入"<<m<<"个数字"<<endl;
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

  void  listinsert(int i,int e)          //插入元素
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

void listdelete(int i,int e)               //删除元素
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
	 cout<<"请输入选项："<<endl;
	 cout<<"1:  插入     2:  删除      3:  建立    0:  退出"<<endl;
     cin>>k;
	 switch(k)
	 {
	   case '1':
	   printf("请输入插入的位置：");
	   cin>>i;
	   printf("请输入元素：");
	   cin>>e; 
	   listinsert(i,e);
	   break;
	   case '2':
	   printf("请输入要删除元素的位置：");
	   cin>>j;
	   listdelete(j,e);
	   break;
       case '3':
	   cout<<"请输入要建立表的长度："<<endl;
       cin>>m;
       initlist(m); 	
	   break;
	   case '0':return 0;
	   default:cout<<"输入有误！"<<endl;break;
	 }
  }while(k);
  return 0;
}