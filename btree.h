#pragma once
//二叉树的基本运算算法
#include <stdio.h>
#include <malloc.h>
#include<iostream>
using namespace std;
#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;			//数据元素
	struct node* lchild;	//指向左孩子结点
	struct node* rchild;	//指向右孩子结点
} BTNode;
void CreateBTree(BTNode*& b, char* str)	//创建二叉树
{
	BTNode* St[MaxSize], * p = NULL;
	int top = -1, k, j = 0;
	char ch;
	b = NULL;				//建立的二叉树初始时为空
	ch = str[j];
	while (ch != '\0')  	//str未扫描完时循环
	{
		switch (ch)
		{
		case '(':top++; St[top] = p; k = 1; break;		//为左孩子结点
		case ')':top--; break;
		case ',':k = 2; break;                      		//为孩子结点右结点
		default:p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch; p->lchild = p->rchild = NULL;
			if (b == NULL)                    	 	//*p为二叉树的根结点
				b = p;
			else  								//已建立二叉树根结点
			{
				switch (k)
				{
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}
void DestroyBTree(BTNode*& b)	//销毁二叉树
{
	if (b != NULL)
	{
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
int BTHeight(BTNode* b)		//求二叉树b的高度
{
	int lchildh, rchildh;
	if (b == NULL) return(0); 				//空树的高度为0
	else
	{
		lchildh = BTHeight(b->lchild);	//求左子树的高度为lchildh
		rchildh = BTHeight(b->rchild);	//求右子树的高度为rchildh
		return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
void DispBTree(BTNode* b)  //以括号表示法输出二叉树
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");						//有孩子结点时才输出(
			DispBTree(b->lchild);				//递归处理左子树
			if (b->rchild != NULL) printf(",");	//有右孩子结点时才输出,
			DispBTree(b->rchild);				//递归处理右子树
			printf(")");						//有孩子结点时才输出)
		}
	}
}

void PreOrder(BTNode* b)  			//先序遍历的递归算法
{
	if (b != NULL)
	{
		printf("%c ", b->data);		//访问根结点
		PreOrder(b->lchild);		//递归访问左子树
		PreOrder(b->rchild);		//递归访问右子树
	}
}
void PreOrder1(BTNode* b)			//先序非递归遍历算法
{
	BTNode* St[MaxSize], * p;
	int top = -1;
	if (b != NULL)
	{
		top++;						//根结点进栈
		St[top] = b;
		while (top > -1)				//栈不为空时循环
		{
			p = St[top];				//退栈并访问该结点
			top--;
			printf("%c ", p->data);
			if (p->rchild != NULL)	//有右孩子,将其进栈
			{
				top++;
				St[top] = p->rchild;
			}
			if (p->lchild != NULL)	//有左孩子,将其进栈
			{
				top++;
				St[top] = p->lchild;
			}
		}
		printf("\n");
	}
}
void InOrder(BTNode* b)   		//中序遍历的递归算法
{
	if (b != NULL)
	{
		InOrder(b->lchild);		//递归访问左子树
		printf("%c ", b->data);	//访问根结点
		InOrder(b->rchild);		//递归访问右子树
	}
}
void InOrder1(BTNode* b)		//中序非递归遍历算法
{
	BTNode* St[MaxSize], * p;
	int top = -1;
	if (b != NULL)
	{
		p = b;
		while (top > -1 || p != NULL)
		{
			while (p != NULL)		//扫描结点p的所有左下结点并进栈
			{
				top++;
				St[top] = p;
				p = p->lchild;
			}
			if (top > -1)
			{
				p = St[top];		//出栈结点p并访问
				top--;
				printf("%c ", p->data);
				p = p->rchild;
			}
		}
		printf("\n");
	}
}
void PostOrder(BTNode* b) 			//后序遍历的递归算法
{
	if (b != NULL)
	{
		PostOrder(b->lchild);		//递归访问左子树
		PostOrder(b->rchild);		//递归访问右子树
		printf("%c ", b->data);		//访问根结点
	}
}
void PostOrder1(BTNode* b)			//后序非递归遍历算法
{
	BTNode* St[MaxSize];
	BTNode* p;
	int top = -1;								//栈指针置初值
	bool flag;
	if (b != NULL)
	{
		do
		{
			while (b != NULL)					//将b结点的所有左下结点进栈
			{
				top++;
				St[top] = b;
				b = b->lchild;
			}
			p = NULL;							//p指向当前结点的前一个已访问的结点
			flag = true;						//flag为真表示正在处理栈顶结点
			while (top != -1 && flag)
			{
				b = St[top];					//取出当前的栈顶元素
				if (b->rchild == p)			//右子树不存在或已被访问,访问之
				{
					printf("%c ", b->data);	//访问b结点
					top--;
					p = b;					//p指向则被访问的结点
				}
				else
				{
					b = b->rchild;			//b指向右子树
					flag = false;				//表示当前不是处理栈顶结点	
				}
			}
		} while (top != -1);
		printf("\n");
	}
}
void TravLevel(BTNode* b)				//层次遍历
{
	BTNode* Qu[MaxSize];				//定义环形队列
	int front, rear;						//定义队首和队尾指针
	front = rear = 0;						//置队列为空队
	if (b != NULL)
		printf("%c ", b->data);
	rear++;								//根结点进队
	Qu[rear] = b;
	while (rear != front)					//队列不为空
	{
		front = (front + 1) % MaxSize;
		b = Qu[front];					//出队结点b
		if (b->lchild != NULL)			//输出左孩子,并进队
		{
			printf("%c ", b->lchild->data);
			rear = (rear + 1) % MaxSize;
			Qu[rear] = b->lchild;
		}
		if (b->rchild != NULL)			//输出右孩子,并进队
		{
			printf("%c ", b->rchild->data);
			rear = (rear + 1) % MaxSize;
			Qu[rear] = b->rchild;
		}
	}
	printf("\n");
}


void Parent(BTNode *T, char x) {
	if (T) {
		if ((T->lchild) && T->lchild->data == x) {    //左孩子不为空 ，判断左孩子与x是否相等 
			printf("(8)存在x的双亲结点为:%c:",T->data); return;
		}
		if ((T->rchild) && T->rchild->data == x) {   //右孩子不为空 ，判断右孩子与x是否相等 
			printf("(8)存在x的双亲结点为:%c", T->data); return; 
		}
		else {
			Parent(T->lchild, x);
			Parent(T->rchild, x);
		}
	}
	
}
//求指定结点的路径
void PreOrder_LeavesRoute(BTNode *t, char c, int level)
{
	static char sta[10];//用于存放从根结点到当前结点的动态更新的栈
	if (!t) return; //当前访问的结点为空，直接返回
	sta[level++] = t->data;
	if (t->data == c) { //当前访问结点中的数据即为所要找的值
		int i = 0;
		cout << "根节点到当前结点的路径为:";
		while (i < level - 1)
			cout << sta[i++] << "->";
		cout << sta[i] << endl;
		return;
	}
	PreOrder_LeavesRoute(t->lchild, c, level);
	PreOrder_LeavesRoute(t->rchild, c, level);
	level--;
}
void Find(BTNode* t)
{
	
	cout << "(9)请输入指定结点的值：";
	char c;
	cin >> c;
	PreOrder_LeavesRoute(t, c, 0);
}