#include"btree.h"
#include<stdio.h>
#include<string.h>


	int main()
	{
		BTNode* b, * p, * lp, * rp;;
		char str1[] = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
		printf("二叉树的基本运算如下:\n");
		printf("(1)创建二叉树\n");
		CreateBTree(b, str1);
		printf("(2)输出二叉树:"); DispBTree(b); printf("\n");
		printf("\n");
		printf("(3)二叉树b的高度:%d\n", BTHeight(b));
		printf("(4)层次遍历序列:");
		TravLevel(b);
		printf("(5)先序遍历序列:\n");
		printf("    递归算法:"); PreOrder(b); printf("\n");
		printf("  非递归算法:"); PreOrder1(b);
		printf("(6)中序遍历序列:\n");
		printf("    递归算法:"); InOrder(b); printf("\n");
		printf("  非递归算法:"); InOrder1(b);
		printf("(7)后序遍历序列:\n");
		printf("    递归算法:"); PostOrder(b); printf("\n");
		printf("  非递归算法:"); PostOrder1(b);
		Parent(b, 'M');                      //求（）的双亲结点
		printf("\n");
		Find(b);                            //求结点间路径
		printf("(10)释放二叉树b\n");
		DestroyBTree(b);
		return 1;
	}
