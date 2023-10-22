#include <stdio.h>
#include "main.h"
#include <assert.h>
#include <stdlib.h>

enum MENU { Insert = 1, Search, Modify, Delete, Find, Display, Quit};

void Menu()
{
	printf("------------------------------\n");
	printf("\t1.���������¼\n");
	printf("\t2.���ҳ�����Ϣ\n");
	printf("\t3.�޸ĳ�����Ϣ\n");
	printf("\t4.ɾ��������Ϣ\n");
	printf("\t5.��ѯ������P����С�ڵ���D�ĳ���\n");
	printf("\t6.��ʾ���г�����Ϣ\n");
	printf("\t7.�˳�����ϵͳ\n");
	printf("------------------------------\n");
}

//2.������ͷ�����Ǵ����ṹ�����
LPNODE createHead()
{
	LPNODE headNode = (LPNODE)malloc(sizeof(NODE));
	//struct Node* headNode=(struct Node*)malloc(sizeof(struct Node));   //��Ч������仰
	assert(headNode);
	headNode->next = NULL;			//��ͷ���ݿ��Բ���ʼ��������ָ��һ����Ҫ
	return headNode;
}
//3.�����ڵ� --->Ϊ����׼��--->�����ṹ�����
LPNODE  createNode(CITY data)
{
	LPNODE newNode = (LPNODE)malloc(sizeof(NODE));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//��ӡ����
void PrintList(struct Node* list)
{
	//��ͷ����,��ӡӦ���Ǵӵڶ����ڵ��ӡ
	LPNODE pMove = list->next;		//list��ͷ��list->next ͷ�ڵ����һ��
	printf("������\tx\ty\n");
	while (pMove != NULL)
	{
		printf("%s\t%d\t%d\n", pMove->data.name, pMove->data.pos_x, pMove->data.pos_y);
		pMove = pMove->next;
	}
	printf("\n");
}
//���뷽ʽ
//ͷ�巨(��ӵķ�ʽ)
void insertByHead(struct Node* headNode, CITY data)
{
	LPNODE newNode = createNode(data);
	newNode->next = headNode->next;		//�½ڵ����һ����ͷ�ڵ���һ��
	headNode->next = newNode;			//ͷ�ڵ����һ����Ϊ�½ڵ�
}
//ָ��λ��ɾ��
void deleteByName(LPNODE headNode, const char* name)
{
	//����ָ���ڵ��ָ���ڵ����һ���ڵ�
	LPNODE preNode = headNode;			//ͷ
	LPNODE curNode = headNode->next;	//ͷ����һ��
	while (curNode != NULL && strcmp(curNode->data.name, name))  //�������ܻ�����д
	{
		//preNode = preNode->next;
		//curNode = curNode->next;
		//��Ч��������
		preNode = curNode;
		curNode = preNode->next;			//curNode = curNode->next;
	}
	//�������ҽ��
	if (curNode == NULL)
	{
		printf("δ�ҵ�ָ�����У��޷�ɾ��!\n");
	}
	else
	{
		preNode->next = curNode->next;
		free(curNode);
		curNode = NULL;
	}
}
LPNODE searchDataByName(LPNODE headNode, const char* name)
{
	LPNODE pMove = headNode->next;
	while (pMove != NULL && strcmp(pMove->data.name, name))
	{
		pMove = pMove->next;
	}
	return pMove;
}
void Findcity(LPNODE headNode, int p_x, int p_y, int dis)
{
	LPNODE pMove = headNode->next;
	int distance,flag = 0;
	printf("������\tx\ty\n");
	while (pMove)
	{
		distance = (p_x - pMove->data.pos_x) * (p_x - pMove->data.pos_x) + (p_y - pMove->data.pos_y) * (p_y - pMove->data.pos_y);
		if (distance <= dis * dis)
		{
			flag = 1;
			printf("%s\t%d\t%d\n", pMove->data.name, pMove->data.pos_x, pMove->data.pos_y);
		}
		pMove = pMove->next;
	}
	if (flag == 0)
	{
		printf("δ�ҵ�ָ������\n");
	}
}
void KeyDown(LPNODE list)
{
	CITY temp_city;
	LPNODE result = NULL;
	int userKey = 0;
	int p_x, p_y, dis;
	scanf("%d", &userKey);
	switch (userKey)
	{
	case Insert:
		printf("�����������Ϣ:");
		scanf("%s%d%d", temp_city.name, &temp_city.pos_x, &temp_city.pos_y);
		insertByHead(list, temp_city);
		break;
	case Search:
		printf("������Ҫ���ҵĳ�����:");
		scanf("%s", temp_city.name);
		result = searchDataByName(list, temp_city.name);
		if (result == NULL)
		{
			printf("δ�ҵ���س�����Ϣ!\n");
		}
		else
		{
			printf("������\tx\ty\n");
			printf("%s\t%d\t%d\n", result->data.name, result->data.pos_x, result->data.pos_y);
		}
		break;
	case Modify:
		printf("������Ҫ�޸ĵĳ�����:");
		scanf("%s", temp_city.name);
		result = searchDataByName(list, temp_city.name);
		if (result == NULL)
		{
			printf("δ�ҵ������Ϣ!\n");
		}
		else
		{
			printf("�������µĳ�����Ϣ:");
			scanf("%s%d%d", result->data.name, &result->data.pos_x, &result->data.pos_y);
		}
		break;
	case Delete:
		printf("������ɾ���ĳ�����:");
		scanf("%s", temp_city.name);
		deleteByName(list, temp_city.name);
		break;
	case Find:
		printf("�������P�������Լ��뾶D:");
		scanf("%d%d%d", &p_x, &p_y, &dis);
		Findcity(list, p_x, p_y, dis);
		break;
	case Display:
		PrintList(list);
		break;
	case Quit:
		printf("�����˳�!\n");
		exit(0);
		break;
	}
}
int main()
{
	LPNODE list = createHead();
	while (1)
	{
		Menu();
		KeyDown(list);
		system("pause");
		system("cls");
	}
	return 0;
}