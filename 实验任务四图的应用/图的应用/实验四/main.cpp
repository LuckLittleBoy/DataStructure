#include<iostream>
using namespace std;
#include<string>
#define MaxInt 32767
#define MVNum 30

//图的邻接矩阵储存表示
typedef struct
{
	int vexs[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum,arcnum;
}AMGraph;

typedef struct
{
	int info;
}ArcNode;
int LocateVex(AMGraph G,int v)
{
	for(int i=0;i<G.vexnum;i++)
		if(v==G.vexs[i])
			v=i;
	return v;
}
void CreateDN(AMGraph &G)
{
	cin>>G.vexnum>>G.arcnum;
	int i,j,k;
	for(i=0;i<G.vexnum;i++)
		G.vexs[i]=i+1;
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j]=MaxInt;
	for(k=0;k<G.arcnum;k++)
	{
		int v1,v2;
		ArcNode arc;
		cout << "输入一条边依附的顶点及权值：" << endl;
		cin>>v1>>v2>>arc.info;
		int i=LocateVex(G,v1);
		int j=LocateVex(G,v2);
		G.arcs[i][j]=arc.info;
		//G.arcs[j][i]=G.arcs[i][j];
	}
}
void output(AMGraph G)
{
	for(int i=0;i<G.vexnum;i++)
	{
		for(int j=0;j<G.vexnum;j++)
			cout << G.arcs[i][j] << "  ";
		cout << endl;
	}
}
bool visited[MVNum]={false};

/*int FirstAdjVex(AMGraph G,int v)
{
	for(int i=0;i<G.vexnum;i++)
		if(G.arcs[v][i]!=MaxInt)
			return i;
	return -1;
}
int NextAdjVex(AMGraph G,int v,int w)
{
	for(int i=0;i<G.vexnum;i++)
		if((G.arcs[v][i]!=MaxInt)&&(w!=i))
			return i;
	return -1;
}
void DFS(AMGraph G,int v)
{
	int w;
	cout << G.vexs[v];
	visited[v]=true;
	for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
		if(!visited[w])
			DFS(G,w);
}*/
void DFS_AM(AMGraph G,int v)
{
	cout << G.vexs[v];
	visited[v]=true;
	for(int w=0;w<G.vexnum;w++)
		if((G.arcs[v][w]!=MaxInt)&&(!visited[w]))
			DFS_AM(G,w);
}

struct Closedge
{
	int adjvex;
	int lowcost;
}closedge[MVNum];


void MiniSpanTree_Prim(AMGraph G,int u)
{
	int k=LocateVex(G,u);
	for(int j=0;j<G.vexnum;j++)
	{
		if(j!=k)
		{
			closedge[j].adjvex=u;
			closedge[j].lowcost=G.arcs[k][j];
		}
	}
	closedge[k].lowcost=0;

	for(int i=1;i<G.vexnum;i++)
	{
		int kmin=MaxInt,a;
	    for(a=0;a<G.vexnum;a++)
		{
			if((closedge[a].lowcost!=0)&&(closedge[a].lowcost<kmin))
			{
				kmin=closedge[a].lowcost;
				k=a;
		    }
		}
		int u0=closedge[k].adjvex;
		int v0=G.vexs[k];
		cout << "(" << u0 << ","<< v0 << ")";
		closedge[k].lowcost=0;
		for(int j=0;j<G.vexnum;j++)
		{
			if(G.arcs[k][j]<closedge[j].lowcost)
			{
				closedge[j].adjvex=G.vexs[k];
				closedge[j].lowcost=G.arcs[k][j];
			}
		}
	}
}
void ShortestPath_DIJ(AMGraph G,int v0)
{
	int n,v,w;
	int min;
	n = G.vexnum;
	bool S[MVNum];
	int D[MVNum]; 
	int Path[MVNum];
	for(v=0;v<n;++v)
	{
		S[v] = false;
		D[v] = G.arcs[v0][v];
		if(D[v]<MaxInt)
			Path[v] = v0;
		else
			Path[v] = -1;
	}
	S[v0] = true;
	D[v0] = 0;
	for(int i=1;i<n;i++)
		cout << v0 << "到" << G.vexs[i] << "的最短路径为：" << D[i]<<endl; 
	/*-------------------------初始化结束，开始主循环----------------------------*/
	for(int i=1 ; i<n; ++i)
	{
		min = MaxInt;
		for(w=0 ; w<n; ++w) 
		{
			if(!S[w]&&D[w]<min)
			{
				v = w;
				min = D[w];
			}
			S[v] = true;
			for(w=0; w<n; ++w)
			{
				if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
				{
					D[w] = D[v]+G.arcs[v][w];
					Path[w] = v;
				}
			}
		}
	}

	for(int i=1;i<n;i++)
		cout << v0 << "到" << G.vexs[i] << "的最短路径为：" << D[i]<<endl; 
	/*int v1,v2;
	cout << endl << "请输入求最短路径的两个点。" << endl;
	cin >> v1 >> v2;
	int s1 = LocateVex(G,v1);
	int s2 = LocateVex(G,v2);
	cout << v1 << "到" << v2 << "的最短路径为" << D[i][j] << endl;88*/
	for(int i=0;i<n;i++)
	{
	    int k = i; 
		
		while(1)
		{
			if(Path[k] == -1)
			{
				cout<<G.vexs[k]<<" ← ";
			    break;
			}
			cout<<G.vexs[k]<<" ← ";
			k = Path[k];
			
		}
	}
}

void main()
{
	AMGraph G;
	cout << "请输入顶点个数和边数：" << endl;
	CreateDN(G);
	output(G);
	int v;
	cout << "请输入遍历时的初始顶点的坐标：" << endl;
	cin >> v;
	DFS_AM(G,v);
	cout << endl;
	int u;
	cout << "请输入最小生成树的初始顶点：" << endl;
	cin >> u;
	MiniSpanTree_Prim(G,u);
	cout << endl;
	int v0;
	cout << "请输入有向网G的v0顶点（输出v0到其余点的最短路径）" << endl;
	cin >> v0;
	ShortestPath_DIJ(G,v0);
}