#include<iostream>
using namespace std;
#define MAX_VERTEX_NUM 20
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
int InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}
int EnQueue(LinkQueue &Q,int e)
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
int DeQueue(LinkQueue & Q,int &e)
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
bool QueueEmpty(LinkQueue Q)
{
	if(Q.front==Q.rear)
		return true;
	else return false;
}
int visited[MAX_VERTEX_NUM];
typedef struct Graph
{
	char vexs[MAX_VERTEX_NUM];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum,arcnum;
}Graph,* graph;
int LocateVex(Graph *g,char c)
{
	int location=-1;
	for(location=0;location<g->vexnum;location++)
	{
		if(g->vexs[location]==c)
			return location;
	}
	return location;

}
void CreateGraph(graph &g)
{
	char vex1,vex2;
	int loc1,loc2;
	cout<<"请输入顶点数："<<endl;
	cin>>(g->vexnum);
	cout<<"请输入边数："<<endl;
	cin>>(g->arcnum);
	for(int j=0;j<(g->vexnum);j++)
		for(int k=0;k<(g->vexnum);k++)
			g->arcs[j][k]=0;
	for(int i=0;i<(g->vexnum);i++)
	{
		cout<<"输入顶点元素数据："<<endl;
		cin>>(g->vexs[i]);
	}
	cout<<"请输入边的有关信息："<<endl;
	for(int k=0;k<(g->arcnum);k++)
	{
		cout<<"tail:"<<'\t';
		cin>>vex1;
		loc1=LocateVex(g,vex1);
		cout<<endl;	
		cout<<"head:"<<'\t';
		cin>>vex2;
		loc2=LocateVex(g,vex2);
		g->arcs[loc1][loc2]=1;
		cout<<endl;
	}
	cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	int m=0;
	for(m=0;m<(g->vexnum);m++)
		cout<<g->vexs[m];
	cout<<"邻接矩阵： "<<endl;
	for(int s=0;s<(g->vexnum);s++)
	{	for(int n=0;n<g->vexnum;n++)
			cout<<g->arcs[s][n]<<" ";
		cout<<endl;
	}
	cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;

}
void visit(graph g,int i)
{
	cout<<(g->vexs[i])<<" ";
}
int FirstAdjVex(graph g,int i)
{
	
	int next=0;
	while(next<g->vexnum)
	{
		if(g->arcs[i][next])
			return next;
		next++;
		
	}	
	if(next>=(g->vexnum))
		return -1;	
	return -1;
}
int NextAdjVex(graph g,int k,int w)
{
	int next=w+1;
	while(next<g->vexnum)
	{
		if(g->arcs[k][next])
			return next;
		next++;
	}
	if(next>=(g->vexnum))
		return -1;
	return -1;
}
void DFS(graph g,int k)
{
		visited[k]=1;
		visit(g,k);
		for(int w=FirstAdjVex(g,k);w>=0;w=NextAdjVex(g,k,w))
		{
			if(!visited[w])
				DFS(g,w);
		}			
}
void DFSTraverse(graph g)
{
	int k=0;
	for(k=0;k<g->vexnum;k++)
		visited[k]=0;
	for(k=0;k<g->vexnum;k++)
	{
		if(visited[k]==0)
			DFS(g,k);
	}
}
void BFSTraverse(graph g)
{
	int i,u;
	LinkQueue Q;
	for(i=0;i<g->vexnum;i++)
		visited[i]=0;
	InitQueue(Q);
	for(i=0;i<g->vexnum;i++)
		if(!visited[i])
		{
			visited[i]=1;
			visit(g,i);
			EnQueue(Q,i);
			while(!QueueEmpty(Q))
			{
				DeQueue(Q,u);
				for(int w=FirstAdjVex(g,u);w>=0;w=NextAdjVex(g,u,w))
					if(!visited[w])
					{
						visited[w]=1;
						visit(g,w);
						EnQueue(Q,w);
					}
			}
		}
}



int main()
{
	int choice;
	graph g=(Graph *)malloc(sizeof(struct Graph));
	cout<<"************************"<<endl;
	cout<<"1：图的创建；2：深度优先遍历；3：广度优先遍历；0：退出"<<endl;
	cout<<"请输入您的选择："<<endl;
	cin>>choice;
	while(choice)
	{
		switch(choice)
		{
		case 1: CreateGraph(g); break;
		case 2: DFSTraverse(g); 
				cout<<endl;
				break;
		case 3: BFSTraverse(g); 
			    cout<<endl;
				break;
		case 0: break;
		default : cout<<"Error!"<<endl;
		}
	cout<<"************************"<<endl;
	cout<<"1：图的创建；2：深度优先遍历；3：广度优先遍历；0：退出"<<endl;
	cout<<"请输入您的选择："<<endl;
	cin>>choice;
	}
	return 0;
}