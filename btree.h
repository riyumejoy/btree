#pragma once
//�������Ļ��������㷨
#include <stdio.h>
#include <malloc.h>
#include<iostream>
using namespace std;
#define MaxSize 100
typedef char ElemType;
typedef struct node
{
	ElemType data;			//����Ԫ��
	struct node* lchild;	//ָ�����ӽ��
	struct node* rchild;	//ָ���Һ��ӽ��
} BTNode;
void CreateBTree(BTNode*& b, char* str)	//����������
{
	BTNode* St[MaxSize], * p = NULL;
	int top = -1, k, j = 0;
	char ch;
	b = NULL;				//�����Ķ�������ʼʱΪ��
	ch = str[j];
	while (ch != '\0')  	//strδɨ����ʱѭ��
	{
		switch (ch)
		{
		case '(':top++; St[top] = p; k = 1; break;		//Ϊ���ӽ��
		case ')':top--; break;
		case ',':k = 2; break;                      		//Ϊ���ӽ���ҽ��
		default:p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch; p->lchild = p->rchild = NULL;
			if (b == NULL)                    	 	//*pΪ�������ĸ����
				b = p;
			else  								//�ѽ��������������
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
void DestroyBTree(BTNode*& b)	//���ٶ�����
{
	if (b != NULL)
	{
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
int BTHeight(BTNode* b)		//�������b�ĸ߶�
{
	int lchildh, rchildh;
	if (b == NULL) return(0); 				//�����ĸ߶�Ϊ0
	else
	{
		lchildh = BTHeight(b->lchild);	//���������ĸ߶�Ϊlchildh
		rchildh = BTHeight(b->rchild);	//���������ĸ߶�Ϊrchildh
		return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
void DispBTree(BTNode* b)  //�����ű�ʾ�����������
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");						//�к��ӽ��ʱ�����(
			DispBTree(b->lchild);				//�ݹ鴦��������
			if (b->rchild != NULL) printf(",");	//���Һ��ӽ��ʱ�����,
			DispBTree(b->rchild);				//�ݹ鴦��������
			printf(")");						//�к��ӽ��ʱ�����)
		}
	}
}

void PreOrder(BTNode* b)  			//��������ĵݹ��㷨
{
	if (b != NULL)
	{
		printf("%c ", b->data);		//���ʸ����
		PreOrder(b->lchild);		//�ݹ����������
		PreOrder(b->rchild);		//�ݹ����������
	}
}
void PreOrder1(BTNode* b)			//����ǵݹ�����㷨
{
	BTNode* St[MaxSize], * p;
	int top = -1;
	if (b != NULL)
	{
		top++;						//������ջ
		St[top] = b;
		while (top > -1)				//ջ��Ϊ��ʱѭ��
		{
			p = St[top];				//��ջ�����ʸý��
			top--;
			printf("%c ", p->data);
			if (p->rchild != NULL)	//���Һ���,�����ջ
			{
				top++;
				St[top] = p->rchild;
			}
			if (p->lchild != NULL)	//������,�����ջ
			{
				top++;
				St[top] = p->lchild;
			}
		}
		printf("\n");
	}
}
void InOrder(BTNode* b)   		//��������ĵݹ��㷨
{
	if (b != NULL)
	{
		InOrder(b->lchild);		//�ݹ����������
		printf("%c ", b->data);	//���ʸ����
		InOrder(b->rchild);		//�ݹ����������
	}
}
void InOrder1(BTNode* b)		//����ǵݹ�����㷨
{
	BTNode* St[MaxSize], * p;
	int top = -1;
	if (b != NULL)
	{
		p = b;
		while (top > -1 || p != NULL)
		{
			while (p != NULL)		//ɨ����p���������½�㲢��ջ
			{
				top++;
				St[top] = p;
				p = p->lchild;
			}
			if (top > -1)
			{
				p = St[top];		//��ջ���p������
				top--;
				printf("%c ", p->data);
				p = p->rchild;
			}
		}
		printf("\n");
	}
}
void PostOrder(BTNode* b) 			//��������ĵݹ��㷨
{
	if (b != NULL)
	{
		PostOrder(b->lchild);		//�ݹ����������
		PostOrder(b->rchild);		//�ݹ����������
		printf("%c ", b->data);		//���ʸ����
	}
}
void PostOrder1(BTNode* b)			//����ǵݹ�����㷨
{
	BTNode* St[MaxSize];
	BTNode* p;
	int top = -1;								//ջָ���ó�ֵ
	bool flag;
	if (b != NULL)
	{
		do
		{
			while (b != NULL)					//��b�����������½���ջ
			{
				top++;
				St[top] = b;
				b = b->lchild;
			}
			p = NULL;							//pָ��ǰ����ǰһ���ѷ��ʵĽ��
			flag = true;						//flagΪ���ʾ���ڴ���ջ�����
			while (top != -1 && flag)
			{
				b = St[top];					//ȡ����ǰ��ջ��Ԫ��
				if (b->rchild == p)			//�����������ڻ��ѱ�����,����֮
				{
					printf("%c ", b->data);	//����b���
					top--;
					p = b;					//pָ���򱻷��ʵĽ��
				}
				else
				{
					b = b->rchild;			//bָ��������
					flag = false;				//��ʾ��ǰ���Ǵ���ջ�����	
				}
			}
		} while (top != -1);
		printf("\n");
	}
}
void TravLevel(BTNode* b)				//��α���
{
	BTNode* Qu[MaxSize];				//���廷�ζ���
	int front, rear;						//������׺Ͷ�βָ��
	front = rear = 0;						//�ö���Ϊ�ն�
	if (b != NULL)
		printf("%c ", b->data);
	rear++;								//��������
	Qu[rear] = b;
	while (rear != front)					//���в�Ϊ��
	{
		front = (front + 1) % MaxSize;
		b = Qu[front];					//���ӽ��b
		if (b->lchild != NULL)			//�������,������
		{
			printf("%c ", b->lchild->data);
			rear = (rear + 1) % MaxSize;
			Qu[rear] = b->lchild;
		}
		if (b->rchild != NULL)			//����Һ���,������
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
		if ((T->lchild) && T->lchild->data == x) {    //���Ӳ�Ϊ�� ���ж�������x�Ƿ���� 
			printf("(8)����x��˫�׽��Ϊ:%c:",T->data); return;
		}
		if ((T->rchild) && T->rchild->data == x) {   //�Һ��Ӳ�Ϊ�� ���ж��Һ�����x�Ƿ���� 
			printf("(8)����x��˫�׽��Ϊ:%c", T->data); return; 
		}
		else {
			Parent(T->lchild, x);
			Parent(T->rchild, x);
		}
	}
	
}
//��ָ������·��
void PreOrder_LeavesRoute(BTNode *t, char c, int level)
{
	static char sta[10];//���ڴ�ŴӸ���㵽��ǰ���Ķ�̬���µ�ջ
	if (!t) return; //��ǰ���ʵĽ��Ϊ�գ�ֱ�ӷ���
	sta[level++] = t->data;
	if (t->data == c) { //��ǰ���ʽ���е����ݼ�Ϊ��Ҫ�ҵ�ֵ
		int i = 0;
		cout << "���ڵ㵽��ǰ����·��Ϊ:";
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
	
	cout << "(9)������ָ������ֵ��";
	char c;
	cin >> c;
	PreOrder_LeavesRoute(t, c, 0);
}