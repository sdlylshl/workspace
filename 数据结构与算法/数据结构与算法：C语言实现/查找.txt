#include<iostream>
#include<string>
using namespace std;
struct info{
	int key;
	string name;
}info;
struct info stuInfo[40];
typedef struct{
	struct info *elem;
	int length;
}SSTable;
void Create(SSTable &st)
{
	
	int num,k;
	cout<<"总记录条数："<<endl;
	cin>>num;
	for(k=1;k<=num;k++)
	{
		cout<<"关键字 key;"<<'\t';
		cin>>stuInfo[k].key;
		cout<<endl;
		cout<<"学生姓名："<<'\t';
		cin>>stuInfo[k].name;
		cout<<endl;
	}

	st.elem=&stuInfo[0];
	st.length=num;

}
void Print(SSTable st,int i)
{
	cout<<st.elem[i].key<<'\t'<<st.elem[i].name<<endl;
}
int Search_Seq(SSTable ST,int key)
{
	int i;
	ST.elem[0].key=key;
	for(i=ST.length;ST.elem[i].key!=key;i--);
	return i;
}
int Search_Bin(SSTable ST,int key)
{
	int low,high,mid;
	low=1;
	high=ST.length;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(key==ST.elem[mid].key)
			return mid;
		else if(key<ST.elem[mid].key)
			high=mid-1;
		else low=mid+1;
	}
	return 0;
}
int main()
{
  int k;
  int data,location;
  SSTable ST;
  cout<<"请输入您的选择："<<endl;
  cout<<"1: 创建表，2：顺序查找，3：折半查找，0：退出"<<endl;
  cout<<"****************************************"<<endl;
  cin>>k;
  while(k)
  {
	  switch(k)
	  {case 1: Create(ST);break;
	  case 2: cout<<"请输入您要查找的关键字 key: "<<'\t';
		  cin>>data;
		  location=Search_Seq(ST,data);
		  if(location)
		  {cout<<"您要查找的记录位于表中第"<<location<<"个位置"<<endl;
		  Print(ST,location);
		  }
		  else cout<<"没有此条记录!"<<endl;
		  break;
	  case 3: cout<<"请输入您要查找的关键字 key: "<<'\t';
		  cin>>data;
		  location=Search_Bin(ST,data);
		  if(location)
		  {cout<<"您要查找的记录位于表中第"<<location<<"个位置"<<endl;
		  Print(ST,location);
		  }
		  else cout<<"没有此条记录!"<<endl;
		  break;
	  case 0: break;
	  default: cout<<"没有此选项!"<<endl;
	  }
	cout<<"请输入您的选择："<<endl;
    cout<<"1: 创建表，2：顺序查找，3：折半查找，0：退出"<<endl;
    cout<<"****************************************"<<endl;
    cin>>k;
  }
  return 0;
}