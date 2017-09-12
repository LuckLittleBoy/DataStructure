#include<iostream>
using namespace std;

typedef struct LNode
{
	int data;
	int num;
	struct LNode *next;
}LNode,*LinkList;

void CreateList(LinkList &L,int n)
{
	L=new LNode;
	L->next=NULL;
	LNode *r;
	r=L;
	
	for(int i=0;i<n;i++)
	{
		LinkList p=new LNode;
		cin >> p->data;
		p->num=i+1;
		p->next=NULL;
		r->next=p;
		r=p;
		r->next=L->next;
	}
}
void StartList(LinkList &L,int &m,int n)
{
	LinkList f,p;
	int Num,k;

	f=L->next;

	for(int i=0;i<n;i++)
	{
		k=1;
		while(k!=m)
		{
			k++;
			f=f->next;	
		}
		m=f->data;
	    Num=f->num;
	    p=f;
	    for(int j=0;j<n-i-1;j++)
			p=p->next;
		LinkList q=p->next;
	    p->next=f->next;
	    f=f->next;
	    delete q;
	    cout << Num<<" ";
	}
}    
int main()
{
	LinkList L;
	int n,m;

	cout << "请输入人数n（n<=30）:" << endl;
	cin >> n;
	while(n<1)
	{
		cout << "人数输入错误！" << endl;
		cout << "请重新输入：" << endl;
		cin >> n;
	}
	cout << "请输入每个人所持的密码：" << endl;
	CreateList(L,n);

	cout << "请输入一个整数作为报数上限值：" << endl;
	cin >> m;

	cout << "出列顺序：" << endl;
	StartList(L,m,n);

	return 0;
}