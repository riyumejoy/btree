#include"btree.h"
#include<stdio.h>
#include<string.h>


	int main()
	{
		BTNode* b, * p, * lp, * rp;;
		char str1[] = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
		printf("�������Ļ�����������:\n");
		printf("(1)����������\n");
		CreateBTree(b, str1);
		printf("(2)���������:"); DispBTree(b); printf("\n");
		printf("\n");
		printf("(3)������b�ĸ߶�:%d\n", BTHeight(b));
		printf("(4)��α�������:");
		TravLevel(b);
		printf("(5)�����������:\n");
		printf("    �ݹ��㷨:"); PreOrder(b); printf("\n");
		printf("  �ǵݹ��㷨:"); PreOrder1(b);
		printf("(6)�����������:\n");
		printf("    �ݹ��㷨:"); InOrder(b); printf("\n");
		printf("  �ǵݹ��㷨:"); InOrder1(b);
		printf("(7)�����������:\n");
		printf("    �ݹ��㷨:"); PostOrder(b); printf("\n");
		printf("  �ǵݹ��㷨:"); PostOrder1(b);
		Parent(b, 'M');                      //�󣨣���˫�׽��
		printf("\n");
		Find(b);                            //�����·��
		printf("(10)�ͷŶ�����b\n");
		DestroyBTree(b);
		return 1;
	}
