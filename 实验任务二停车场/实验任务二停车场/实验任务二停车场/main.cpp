#include<iostream>
using namespace std;
#define MAXSIZE 2         //停车场的容量

//顺序栈指针的类型结构
typedef struct SElemType
{
	char information;     //汽车进出信息
	int num;              //汽车编号
	float time;           //汽车进出时间
}SElemType;

//顺序栈的存储结构
typedef struct SqStack
{
	SElemType *base;      //栈底指针类型
	SElemType *top;       //栈顶指针类型
	int stacksize;
}SqStack;

//队列的链式存储结构
typedef struct QNode
{
	SElemType data;       //队列的数据域
	struct QNode *next;   //队列的指针域
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;       //队头指针
	QueuePtr rear;        //队尾指针
}LinkQueue;

//顺序栈的初始化
void InitStack(SqStack &S)
{
	S.base=new SElemType[MAXSIZE];        //申请空间
	if(!S.base)
		cout << "储存分配失败！" << endl;
	S.top=S.base;                         //top初始化为base，空栈
	S.stacksize=MAXSIZE;
}

//链式队列的初始化
void InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=new QNode;   //生成新结点作为头结点，队头和队尾指针指向该结点 
	Q.front->next=NULL;         //头结点的指针域置空
}

//链队的入队
void EnQueue(LinkQueue &Q,SElemType e)
{
	QNode *p=new QNode;
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}

//链队的出队
SElemType DeQueue(LinkQueue &Q)
{
	SElemType s;
	QNode *p;
	
	p=Q.front->next;
	s=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	delete p;
	return s;
}

//输出停车场所有车辆的信息
void OutputInformation(SqStack S)
{
	while(S.top!=S.base)
	{
		S.top--;
		cout << (*S.top).information << "	";
		cout << (*S.top).num << "	";
		cout << (*S.top).time << "	";
		cout << endl;
		
	}
}

//副栈和顺序栈的入栈
void Push(SqStack &S,LinkQueue &Q,SElemType e)
{
	                         
	if(S.top-S.base==S.stacksize)
	{
		cout << "栈满，不能再插入！" << endl;
		cout << "在外面等候！" << endl;
		                           
		EnQueue(Q,e);                           //链队的入队
	}
	else
	{
		*S.top=e;
		S.top++;
	}
}

//副栈的出栈
SElemType Pop1(SqStack &S1)
{
	SElemType e;
	--S1.top;
	e=*S1.top;
	return e;
}

//副栈的出栈，顺序栈的入栈
void Push1(SqStack &S,SqStack &S1)
{	
	*S.top=Pop1(S1);
	S.top++;
}

//停车费的计算
void StopingPrice(SElemType e,SElemType s)
{
	cout << e.num << " 号车一共在停车场停了 ";
	cout << e.time-s.time << " 小时" ;
	cout << "需要交纳停车费:" << e.time-s.time << "美元" << endl;
}

//顺序栈的出栈
void Pop(SqStack &S,SqStack &S1,LinkQueue &Q,SElemType e)
{ 
	SElemType s;
	if(S.top==S.base)              //停车厂没有车辆
	{
		cout << "栈空！" << endl;
		return;
	}
	S.top--;
	s=*S.top;
	
	while(s.num!=e.num)           //查找车辆的编号
	{
		if(S.top==S.base)         //未找到
		{
			cout << "未找到！" << endl;
		    break;
	    }
		Push(S1,Q,s);            //将车辆放入副栈
		S.top--;                 
		s=*S.top;
	}
	while(S1.top!=S1.base)       //将副栈的车辆放回停车场 
		Push1(S,S1);
	
	while((Q.front!=Q.rear)&&S.top-S.base!=S.stacksize)       //将在外面等候的车辆放入停车场
	{
		Push(S,Q,DeQueue(Q));
	}

	StopingPrice(e,s);           //计算产生的停车费
	OutputInformation(S);        //输出车辆信息
}

int main()
{
	SqStack S;
	SqStack S1;
	LinkQueue Q;
	SElemType e;
	
	InitStack(S);
	InitStack(S1);
	InitQueue(Q); 
	while(1)
	{
		cout << "请输入汽车到达或离去信息，序号及到达或离去的时刻" << endl;
		cin >> e.information; 
		if(e.information=='A')
		{
			cin >> e.num >> e.time;
			Push(S,Q,e);
		}
		if(e.information=='D')
		{
			cin >> e.num >> e.time;
			Pop(S,S1,Q,e);
		}
		if(e.information=='E')
			break;
	}
	
	return 0;
}