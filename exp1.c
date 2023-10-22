#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MATCH_TIMES  2
#define MAX_P       20
//#define EVERY

//队列的部分
//数据
typedef struct Person {
    int id;
    char gender;
} Person;
//节点
typedef struct QueueNode {
    Person person;
    struct QueueNode* next;
} QueueNode;
//队列
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int num;
} Queue;

void initQueue(Queue* queue) {
    memset(queue, 0, sizeof(Queue));
}

bool isEmpty(Queue* queue) {
    return queue->front == NULL;
}

void enqueue(Queue* queue, Person person) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    assert(newNode);
    newNode->person = person;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = newNode;
    }
    else {
        queue->rear->next = newNode;
    }

    queue->rear = newNode;
    queue->num++;
}

Person dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("队列为空，无法出队\n");
        Person emptyPerson = { -1, '\0' };
        return emptyPerson;
    }

    QueueNode* frontNode = queue->front;
    Person person = frontNode->person;
    queue->front = frontNode->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(frontNode);
    queue->num--;
    return person;
}

#ifdef EVERY
//链表的部分
typedef struct Match {
    Person female;      //女舞伴
    int n1;              //男舞伴与女舞伴配对的第一次
    int n2;              //男舞伴与女舞伴配对的第二次
}Match;

typedef struct Node {
    Match data;
    struct Node* next;
}NODE, *LPNODE;

typedef struct maleNode {
    Person male;
    LPNODE maleNode;
    struct maleNode* next;
}MaleNode, *LMaleNode;

LMaleNode createHead(){
    LMaleNode headNode = (LMaleNode)malloc(sizeof(MaleNode));
    assert(headNode);
    headNode->next = NULL;
    return headNode;
}

LMaleNode CreateMaleNode(Person male) {
    LMaleNode newNode = (LMaleNode)malloc(sizeof(MaleNode));
    assert(newNode);
    newNode->male = male;
    newNode->maleNode = NULL;
    newNode->next = NULL;
    return newNode;
}

LPNODE CreateFemaleNode(Match data){
    LPNODE newNode = (LPNODE)malloc(sizeof(NODE));
    assert(newNode);
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void InsertMaleListByTail(LMaleNode headNode, Person male) {
    LMaleNode pMove = headNode;
    while (pMove->next != NULL)  //判断当前节点的next是不是空的
    {
        pMove = pMove->next;	 //走到下一个节点的位置
    }
    //直接放到尾部后面
    LMaleNode newNode = CreateMaleNode(male);
    pMove->next = newNode;
}

void InsertFemaleListByTail(LMaleNode list, Person male, Match female) {
    LMaleNode pMove = SearchDataByMale(list, male);
    pMove = pMove->maleNode;
    while (pMove->next != NULL)  //判断当前节点的next是不是空的
    {
        pMove = pMove->next;	 //走到下一个节点的位置
    }
    //直接放到尾部后面
    LMaleNode newNode = CreateFemaleNode(female);
    pMove->next = newNode;
}

LMaleNode SearchDataByMale(LMaleNode headNode, Person male){
    LMaleNode pMove = headNode->next;
    while (pMove){
        if ((male.gender == pMove->male.gender) 
            && (male.id == pMove->male.id)){
            break;
        }
        pMove = pMove->next;
    }
    return pMove;
}

LPNODE SearchDataByFeMale(LPNODE maleNode, Person female) {
    if (maleNode == NULL) {
        return NULL;
    }
    LPNODE pMove = maleNode;
    while (pMove) {
        if ((female.gender == pMove->data.female.gender)
            && (female.id == pMove->data.female.id)) {
            break;
        }
        pMove = pMove->next;
    }
    return pMove;
}

bool IsFemaleDataEmpty(Match data)
{
    return (data.female.id == 0) && (data.female.gender == 0);
}

bool IsFemaleFullData(Match data) {
    return (data.n2 != 0);
}

int FindLowestMutiple(int a, int b) {//寻找最小公倍数
    int max;
    max = (a > b ? a : b);
    while (1) {
        if (max % a == 0 && max % b == 0) {
            break;
        }
        max++;
    }
    return max;
}
#endif
#ifndef EVERY
void simulateDanceParty(Queue* maleQueue, Queue* femaleQueue, int x, int y) {
    int curSong = 1;
    int flag = 0;

    while (!isEmpty(maleQueue) && !isEmpty(femaleQueue)) {
        Person male = dequeue(maleQueue);
        Person female = dequeue(femaleQueue);

        //printf("第%d曲配对情况：男生%d和女生%d\n", curSong, male.id, female.id);

        if (male.id == x && female.id == y) {
            printf("\t编号为%d的男生和编号为%d的女生在第%d曲配对跳舞\n", x, y, curSong);
            flag++;
        }

        if (MATCH_TIMES == flag) {
            break;
        }

        enqueue(maleQueue, male);
        enqueue(femaleQueue, female);

        curSong++;
    }
}
#else 
void simulateDanceParty(LMaleNode list, Queue* maleQueue, Queue* femaleQueue) {
    int curSong = 1;
    int times = 0;
    
    
    LMaleNode pMale = (LMaleNode)malloc(sizeof(MaleNode));
    memset(pMale, 0, sizeof(MaleNode));

    LPNODE pFemale = (LPNODE)malloc(sizeof(NODE));
    memset(pFemale, 0, sizeof(NODE));

    //改进点：可以做成循环队列
    while (1) {
        if (times == FindLowestMutiple(maleQueue->num, femaleQueue->num)) {
            break;
        }

        Person male = dequeue(maleQueue);
        Person female = dequeue(femaleQueue);

        pMale = SearchDataByMale(list, male);
        pFemale = SearchDataByFeMale(pMale, female);

        if (pMale == NULL) {//空
            InsertMaleListByTail(list, male);
        }
        else if (pFemale == NULL) {//女舞伴信息为空
            Match Temp;
            Temp.female = female;
            Temp.n1 = curSong;

            InsertFemaleListByTail(list, pMale->male, Temp);
        }
        else if (!IsFemaleFullData(pFemale->data)) {//缺少与女舞伴第二次配对信息
            pFemale->data.n2 = curSong;
        }
        else if (IsFemaleFullData(pFemale->data)) {//信息完整
            times++;
        }

        enqueue(maleQueue, male);
        enqueue(femaleQueue, female);

        curSong++;
    }
}

void PrintMatchResult(LMaleNode list) {
    LMaleNode pCur = list->next;
    while (pCur){
        
        printf("编号为%d的男舞伴和编号为%d的女舞伴，在第%d次和第%d次都配对了\n",
            pCur->male.id, pCur->maleNode->data.female.id, 
            pCur->maleNode->data.n1, 
            pCur->maleNode->data.n2);
        pCur = pCur->next;
    }
}
#endif

int main() {
    Queue maleQueue, femaleQueue;
    initQueue(&maleQueue);
    initQueue(&femaleQueue);
    
    int num;
    int id;
    Person p;
    p.gender = 'M';

    printf("input the number of the male:");
    scanf("%d", &num);
    for (int i = 1; i <= num; i++) {
        printf("input the %d id of the male:", i);
        scanf("%d", &p.id);
        enqueue(&maleQueue, p);
    }

    p.gender = 'F';
    printf("input the number of the female:");
    scanf("%d", &num);
    for (int i = 1; i <= num; i++) {
        printf("input the %d id of the female:", i);
        scanf("%d", &p.id);
        enqueue(&femaleQueue, p);
    }
#ifndef EVERY
    //实现了输入对应男和女舞伴的配对
    int x;
    int y;
    printf("input x(男) and y(女):");
    scanf("%d%d", &x, &y);
    simulateDanceParty(&maleQueue, &femaleQueue, x, y);
#else   //实现输出 任意一个男舞伴配对 MATCH_TIMES 次 的女舞伴
    /*
        
    */
    LMaleNode list = createHead();
    simulateDanceParty(list, &maleQueue, &femaleQueue);
    PrintMatchResult(list);

#endif

    return 0;
}
    