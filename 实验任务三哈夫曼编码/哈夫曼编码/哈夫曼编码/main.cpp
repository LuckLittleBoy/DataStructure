#include<iostream>
#include<string>
using namespace std;

typedef struct
{
char data;
float weight;
int parent;
int lchild;
int rchild;
}huffnode,*hufftree;
typedef char **huffcode;

void Select(hufftree &HT,int s,int &s1,int &s2)
{
	int t;
	float w1=8388608,w2;
	w2=w1;
	for(int k=1;k<=s;k++)
	{
		if(HT[k].parent==0&&HT[k].weight<w1)
		{
			s1=k;
			w1=HT[k].weight;
		}
	}
	for(int k=1;k<=s;k++)
	{
		if(HT[k].parent==0&&k!=s1&&HT[k].weight<w2)
		{
			s2=k;
			w2=HT[k].weight;
		}
	}
	if(s1>s2)
	{
		t=s1;
		s1=s2;
		s2=t;
	}
}
void CreateTree(hufftree &HT,int n)
{
	
	if(n<=1)
		return;
	int m=2*n-1;
	HT=new huffnode[m+1];
	for(int i=1;i<=m;i++)
	{
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	cout << "请输入字符及其权值：" << endl;
	for(int i=1;i<=n;i++)
	{
		cin>>HT[i].data;
		cin>>HT[i].weight;
	}
	for(int i=n+1;i<=m;i++)
	{
		int s1,s2;
		Select(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
}

void CreateCode(hufftree HT,huffcode &HC,int n)
{
	HC=new char*[n+1];
	char *cd =new char[n];
	cd[n-1]='\0';
	for(int i=1;i<=n;i++)
	{
		int start=n-1;
		int c=i;
		int f=HT[i].parent;
		while(f!=0)
		{
			--start;
			if(HT[f].lchild==c)
				cd[start]='0';
			else
				cd[start]='1';
			c=f;
			f=HT[f].parent;
		}
		HC[i]=new char[n-start];
		strcpy(HC[i],&cd[start]);
	}
	delete cd;
}
void bianma(hufftree HT,huffcode HC,char c,int n)
{
	for(int i=1;i<=n;i++)
		if(c==HT[i].data)
		{
			cout << "哈夫曼码：" << HC[i] << endl;	
			return;
		}
	cout << "输入字符有误！" << endl;
}

void yima(hufftree HT,huffcode HC,string str,int n)
{
	for(int i=1;i<=n;i++)
		if(str==HC[i])
		{
			cout << "对应的字符：" << HT[i].data << endl;
			return;
		}
	cout << "没有对应的字符！" << endl;
}
void output(huffcode HC,int n)
{
	for(int i=1;i<=n;i++)
		cout << HC[i] << endl;
}
void main()
{
	hufftree HT;
	huffcode HC;
	char c;
	string str;
	int n;
	cout << "请输入字符的个数(即叶子的个数)：" << endl;
	cin >> n;
	CreateTree(HT,n);
	CreateCode(HT,HC,n);
	output(HC,n);
	
	cout << "请输入以上字符中的一个：" << endl;
	cin >> c;
	bianma(HT,HC,c,n);
	
	cout << "请输入哈夫曼码：" << endl;
	cin >> str;
	yima(HT,HC,str,n);
}