#include<iostream>
#include <string>
using namespace std;
struct info{
	int key;
	string name;
}info;
struct info stuInfo[50];
typedef struct{
	struct info * r;
	int length;
}SqList;
void create_sq(SqList &L,int n)
{
	for(int i=1;i<=n;i++)
	{
		cout<<"输入第"<<i<<"个学生的学号（关键字 key）:"<<'\t';
		cin>>stuInfo[i].key;
		cout<<'\n'<<"输入第"<<i<<"个学生的姓名："<<'\t';
		cin>>stuInfo[i].name;
		cout<<endl;
	}
	L.r=stuInfo;
	L.length=n;	
}
void InsertSort(SqList &L)
{
	int i,j;
	for(i=2;i<=L.length;++i)
		if(L.r[i].key<L.r[i-1].key)
		{
			L.r[0]=L.r[i];
			L.r[i]=L.r[i-1];
			for(j=i-2;L.r[0].key<L.r[j].key;--j)
				L.r[j+1]=L.r[j];
			L.r[j+1]=L.r[0];
		}
}
void BInsertSort(SqList &L)
{
	int i,j,m,low,high;
	for(i=2;i<=L.length;i++)
	{
		if(L.r[i].key<L.r[i-1].key)
		{
			L.r[0]=L.r[i];
			low=1;
			high=i-1;
			while(low<=high)
			{
				m=(low+high)/2;
				if(L.r[0].key<L.r[m].key)
					high=m-1;
				else low=m+1;
			}
			for(j=i-1;j>=high+1;--j)
				L.r[j+1]=L.r[j];
			L.r[high+1]=L.r[0];
		}
	}
}
void BubbleSort(SqList &L)
{
	int i,j;
	struct info m;
	bool k=false;
	for(i=L.length;i>0;i--)
	{
		for(j=0;j<i;j++)
		{
			if(L.r[j].key>L.r[j+1].key)
			{
				m.key=L.r[j+1].key;
				m.name=L.r[j+1].name;
				L.r[j+1].key=L.r[j].key;
				L.r[j+1].name=L.r[j].name;
				L.r[j].key=m.key;
				L.r[j].name=m.name;
				k=true;
			}
		}
		if(!k)
			break;
	}
}
int Partition(SqList &L,int low,int high)
{
	L.r[0]=L.r[low];
	int pivotkey=L.r[low].key;
	while(low<high)
	{
		while(low<high&&L.r[high].key>=pivotkey)
			high--;
		L.r[low]=L.r[high];
		while(low<high&&L.r[low].key<=pivotkey)
			low++;
		L.r[high]=L.r[low];
	}
	L.r[low]=L.r[0];
	return low;
}
void QSort(SqList &L,int low,int high)
{
	if(low<high)
	{
		int pivotloc=Partition(L,low,high);
		QSort(L,low,pivotloc-1);
		QSort(L,pivotloc+1,high);
	}
}
void QuickSort(SqList &L)
{
	QSort(L,1,L.length);
}
void Print(SqList L)
{
	for(int k=1;k<=L.length;k++)
	{
		cout<<'\t'<<L.r[k].key<<'\t';
		cout<<L.r[k].name<<endl;
	}
}
int main()
{
	int choice,data;
	SqList L;
	cout<<"********************************"<<endl;
	cout<<"请输入您的选择： "<<endl;
	cout<<"1：创建表，2：直接插入排序，3：折半排序，4：起泡排序，5：快速排序，0：退出"<<endl;
	cin>>choice;
	while(choice)
	{
		switch(choice)
		{
		case 1: cout<<"表中记录的总数目："<<endl;
				cin>>data;
				create_sq(L,data);
				Print(L);break;
		case 2: InsertSort(L);
				cout<<"排序后："<<endl;
				Print(L);break;
		case 3: BInsertSort(L);
				cout<<"排序后："<<endl;
				Print(L);break;
		case 4: BubbleSort(L);
				cout<<"排序后："<<endl;
				Print(L);break;
		case 5: QuickSort(L);
				cout<<"排序后："<<endl;
				Print(L);break;
		default: cout<<"没有此选项！"<<endl;
		}
		cout<<"********************************"<<endl;
		cout<<"请输入您的选择： "<<endl;
		cout<<"1：创建表，2：直接插入排序，3：折半排序，4：起泡排序，5：快速排序，0：退出"<<endl;
		cin>>choice;
	}
	return 0;
}
