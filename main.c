#include <stdio.h>
#include "main.h"
#include <assert.h>
#include <stdlib.h>

enum MENU { Insert = 1, Search, Modify, Delete, Find, Display, Quit};

void Menu()
{
	printf("------------------------------\n");
	printf("\t1.插入链表记录\n");
	printf("\t2.查找城市信息\n");
	printf("\t3.修改城市信息\n");
	printf("\t4.删除城市信息\n");
	printf("\t5.查询与坐标P距离小于等于D的城市\n");
	printf("\t6.显示所有城市信息\n");
	printf("\t7.退出链表系统\n");
	printf("------------------------------\n");
}

//2.创建表头，就是创建结构体变量
LPNODE createHead()
{
	LPNODE headNode = (LPNODE)malloc(sizeof(NODE));
	//struct Node* headNode=(struct Node*)malloc(sizeof(struct Node));   //等效上面这句话
	assert(headNode);
	headNode->next = NULL;			//表头数据可以不初始化，但是指针一定更要
	return headNode;
}
//3.创建节点 --->为插入准备--->创建结构体变量
LPNODE  createNode(CITY data)
{
	LPNODE newNode = (LPNODE)malloc(sizeof(NODE));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//打印链表
void PrintList(struct Node* list)
{
	//有头链表,打印应该是从第二个节点打印
	LPNODE pMove = list->next;		//list是头，list->next 头节点的下一个
	printf("城市名\tx\ty\n");
	while (pMove != NULL)
	{
		printf("%s\t%d\t%d\n", pMove->data.name, pMove->data.pos_x, pMove->data.pos_y);
		pMove = pMove->next;
	}
	printf("\n");
}
//插入方式
//头插法(插队的方式)
void insertByHead(struct Node* headNode, CITY data)
{
	LPNODE newNode = createNode(data);
	newNode->next = headNode->next;		//新节点的下一个是头节点下一个
	headNode->next = newNode;			//头节点的下一个成为新节点
}
//指定位置删除
void deleteByName(LPNODE headNode, const char* name)
{
	//先找指定节点和指定节点的上一个节点
	LPNODE preNode = headNode;			//头
	LPNODE curNode = headNode->next;	//头的下一个
	while (curNode != NULL && strcmp(curNode->data.name, name))  //条件不能换过来写
	{
		//preNode = preNode->next;
		//curNode = curNode->next;
		//等效下面两行
		preNode = curNode;
		curNode = preNode->next;			//curNode = curNode->next;
	}
	//分析查找结果
	if (curNode == NULL)
	{
		printf("未找到指定城市，无法删除!\n");
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
	printf("城市名\tx\ty\n");
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
		printf("未找到指定城市\n");
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
		printf("请输入城市信息:");
		scanf("%s%d%d", temp_city.name, &temp_city.pos_x, &temp_city.pos_y);
		insertByHead(list, temp_city);
		break;
	case Search:
		printf("请输入要查找的城市名:");
		scanf("%s", temp_city.name);
		result = searchDataByName(list, temp_city.name);
		if (result == NULL)
		{
			printf("未找到相关城市信息!\n");
		}
		else
		{
			printf("城市名\tx\ty\n");
			printf("%s\t%d\t%d\n", result->data.name, result->data.pos_x, result->data.pos_y);
		}
		break;
	case Modify:
		printf("请输入要修改的城市名:");
		scanf("%s", temp_city.name);
		result = searchDataByName(list, temp_city.name);
		if (result == NULL)
		{
			printf("未找到相关信息!\n");
		}
		else
		{
			printf("请输入新的城市信息:");
			scanf("%s%d%d", result->data.name, &result->data.pos_x, &result->data.pos_y);
		}
		break;
	case Delete:
		printf("请输入删除的城市名:");
		scanf("%s", temp_city.name);
		deleteByName(list, temp_city.name);
		break;
	case Find:
		printf("请输入点P的坐标以及半径D:");
		scanf("%d%d%d", &p_x, &p_y, &dis);
		Findcity(list, p_x, p_y, dis);
		break;
	case Display:
		PrintList(list);
		break;
	case Quit:
		printf("正常退出!\n");
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