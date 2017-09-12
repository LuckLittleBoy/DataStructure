#pragma once
#include<iostream>
using namespace std;

#define LH +1
#define EH 0
#define RH -1

typedef struct
{
	int key;
	int bf;
}ElemType10;
typedef struct BSTNode
{
	ElemType10 data;
	struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

class T10
{
public:
	T10();
	void R_Rotate(BSTree &T);
	void L_Rotate(BSTree &T);
	void LeftBalance(BSTree &T);
	void RightBalance(BSTree &T);
	void PrintBST(BSTree T,int m);
	void InsertBST(BSTree &T, ElemType10 e,bool &taller);
	void CreatBST(BSTree &T);
	void FirstSequenceTraversal(BSTree T);
	void InOrderTraverse(BSTree T);
	void AfterTheSequenceTraversal(BSTree T);
	void run();
	~T10();
};
