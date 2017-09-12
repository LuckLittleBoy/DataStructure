#include "T10.h"



T10::T10()
{
}
void T10::R_Rotate(BSTree & T)
{
	BSTree p;
	p = T->lchild;
	T->lchild = p->rchild;
	p->rchild = T;
	T=p;
}

void T10::L_Rotate(BSTree & T)
{
	BSTree p;
	p = T->rchild;
	T->rchild = p->lchild;
	p->lchild = T;
	T=p;
}

void T10::LeftBalance(BSTree & T)
{
	BSTree lc,rd;
	lc = T->lchild;
	switch(lc->data.bf)
	{
	case LH:
		T->data.bf = lc->data.bf = EH;
		R_Rotate(T);break;
	case RH:
		rd = lc->rchild;
		switch(rd->data.bf)
		{
		case LH:
			T->data.bf = RH;
			lc->data.bf = EH;break;
		case EH:T->data.bf = lc->data.bf = EH;break;
		case RH:T->data.bf = EH;lc->data.bf=LH;break;
		}
		rd->data.bf = EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
	}
}

void T10::RightBalance(BSTree & T)
{
	BSTree rc,ld;
	rc = T->rchild;
	switch(rc->data.bf)
	{
	case RH:
		T->data.bf = rc->data.bf = EH;
		L_Rotate(T);break;
	case LH:
		ld = rc->lchild;
		switch(ld->data.bf)
		{
		case LH:
			T->data.bf = EH;
			rc->data.bf = RH;break;
		case EH:T->data.bf = rc->data.bf = EH;break;
		case RH:T->data.bf = LH;rc->data.bf=EH;break;
		}
		ld->data.bf = EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
	}
}

void T10::PrintBST(BSTree T,int m)
{
	int i;
	if(T->rchild)
		PrintBST(T->rchild,m+1);
	for(i=1;i<=m;i++)
		cout << "	";
	cout << T->data.key << endl;
	if(T->lchild)
		PrintBST(T->lchild,m+1);
}
void T10::InsertBST(BSTree & T, ElemType10 e,bool &taller)
{
	if (!T)
	{
		BSTNode *S = new BSTNode;
		S->data = e;
		S->lchild = S->rchild = NULL;
		S->data.bf=EH;
		taller = true;
		T = S;
	}
	else
	{
		if(e.key==T->data.key)
		{
			taller = false;
			cout << "二叉排序树中已有" << e.key << ",无法插入" << endl;
			return;
		}
		if (e.key<T->data.key)
		{
			InsertBST(T->lchild,e,taller);
			if(taller)
			{
				switch(T->data.bf)
				{
				case LH:
					LeftBalance(T);taller = false;break;
				case EH:
					T->data.bf = LH;taller = true;break;
				case RH:
					T->data.bf = EH;taller = false;break;
				}
			}
		}
		if (e.key>T->data.key)
		{
			InsertBST(T->rchild,e,taller);
			if(taller)
			{
				switch(T->data.bf)
				{
				case LH:
					T->data.bf = EH;taller = false;break;
				case EH:
					T->data.bf = RH;taller = true;break;
				case RH:
					RightBalance(T);taller = false;break;
				}
			}
		}
		
	}
}

void T10::CreatBST(BSTree & T)
{
	int m;
	bool taller=false;
	T = NULL;
	ElemType10 e;
	cout << "请依次输入序列（以-1为结束标志）：" << endl;
	cin >> e.key;
	while (e.key != -1)
	{
		InsertBST(T,e,taller);
		cin >> e.key;
	}

	m=0;
	cout << "平衡二叉树创建结束，横向打印出树状结构：" << endl;
	if(T)
		PrintBST(T,m);
	else
	{
		cout << "这是一颗空树" << endl;
		return;
	}
}

void T10::FirstSequenceTraversal(BSTree T)
{
	if (T)
	{
		cout << T->data.key << "  ";
		FirstSequenceTraversal(T->lchild);
		FirstSequenceTraversal(T->rchild);
	}
}

void T10::InOrderTraverse(BSTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		cout << T->data.key << "  ";
		InOrderTraverse(T->rchild);
	}
}

void T10::AfterTheSequenceTraversal(BSTree T)
{
	if (T)
	{
		AfterTheSequenceTraversal(T->lchild);
		AfterTheSequenceTraversal(T->rchild);
		cout << T->data.key << "  ";
	}
}

void T10::run()
{
	BSTree T;

	CreatBST(T);

	cout << "输出二叉树的三种遍历序列：" << endl;

	cout << "先序遍历序列：" << endl;
	FirstSequenceTraversal(T);
	cout << endl;

	cout << "中序遍历序列：" << endl;
	InOrderTraverse(T);
	cout << endl;

	cout << "后序遍历序列：" << endl;
	AfterTheSequenceTraversal(T);
	cout << endl;
}


T10::~T10()
{
}