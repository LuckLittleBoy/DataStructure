#include<iostream>
using namespace std;
#define MAXSIZE 2         //ͣ����������

//˳��ջָ������ͽṹ
typedef struct SElemType
{
	char information;     //����������Ϣ
	int num;              //�������
	float time;           //��������ʱ��
}SElemType;

//˳��ջ�Ĵ洢�ṹ
typedef struct SqStack
{
	SElemType *base;      //ջ��ָ������
	SElemType *top;       //ջ��ָ������
	int stacksize;
}SqStack;

//���е���ʽ�洢�ṹ
typedef struct QNode
{
	SElemType data;       //���е�������
	struct QNode *next;   //���е�ָ����
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;       //��ͷָ��
	QueuePtr rear;        //��βָ��
}LinkQueue;

//˳��ջ�ĳ�ʼ��
void InitStack(SqStack &S)
{
	S.base=new SElemType[MAXSIZE];        //����ռ�
	if(!S.base)
		cout << "�������ʧ�ܣ�" << endl;
	S.top=S.base;                         //top��ʼ��Ϊbase����ջ
	S.stacksize=MAXSIZE;
}

//��ʽ���еĳ�ʼ��
void InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=new QNode;   //�����½����Ϊͷ��㣬��ͷ�Ͷ�βָ��ָ��ý�� 
	Q.front->next=NULL;         //ͷ����ָ�����ÿ�
}

//���ӵ����
void EnQueue(LinkQueue &Q,SElemType e)
{
	QNode *p=new QNode;
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}

//���ӵĳ���
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

//���ͣ�������г�������Ϣ
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

//��ջ��˳��ջ����ջ
void Push(SqStack &S,LinkQueue &Q,SElemType e)
{
	                         
	if(S.top-S.base==S.stacksize)
	{
		cout << "ջ���������ٲ��룡" << endl;
		cout << "������Ⱥ�" << endl;
		                           
		EnQueue(Q,e);                           //���ӵ����
	}
	else
	{
		*S.top=e;
		S.top++;
	}
}

//��ջ�ĳ�ջ
SElemType Pop1(SqStack &S1)
{
	SElemType e;
	--S1.top;
	e=*S1.top;
	return e;
}

//��ջ�ĳ�ջ��˳��ջ����ջ
void Push1(SqStack &S,SqStack &S1)
{	
	*S.top=Pop1(S1);
	S.top++;
}

//ͣ���ѵļ���
void StopingPrice(SElemType e,SElemType s)
{
	cout << e.num << " �ų�һ����ͣ����ͣ�� ";
	cout << e.time-s.time << " Сʱ" ;
	cout << "��Ҫ����ͣ����:" << e.time-s.time << "��Ԫ" << endl;
}

//˳��ջ�ĳ�ջ
void Pop(SqStack &S,SqStack &S1,LinkQueue &Q,SElemType e)
{ 
	SElemType s;
	if(S.top==S.base)              //ͣ����û�г���
	{
		cout << "ջ�գ�" << endl;
		return;
	}
	S.top--;
	s=*S.top;
	
	while(s.num!=e.num)           //���ҳ����ı��
	{
		if(S.top==S.base)         //δ�ҵ�
		{
			cout << "δ�ҵ���" << endl;
		    break;
	    }
		Push(S1,Q,s);            //���������븱ջ
		S.top--;                 
		s=*S.top;
	}
	while(S1.top!=S1.base)       //����ջ�ĳ����Ż�ͣ���� 
		Push1(S,S1);
	
	while((Q.front!=Q.rear)&&S.top-S.base!=S.stacksize)       //��������Ⱥ�ĳ�������ͣ����
	{
		Push(S,Q,DeQueue(Q));
	}

	StopingPrice(e,s);           //���������ͣ����
	OutputInformation(S);        //���������Ϣ
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
		cout << "�����������������ȥ��Ϣ����ż��������ȥ��ʱ��" << endl;
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