#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    double data;
    struct node *link;
} Node;

int Search(Node *ptr, double searchNum);
int insertLast(Node *ptr, double insertNum);
int freeList(Node *ptr);

int main()
{
    int countNumber = 0;
    int extraNumber = 0;
    int searchcount = 0;

    Node *rootNode = (Node *)malloc(sizeof(Node));
    rootNode->data = -1;
    rootNode->link = NULL;

    FILE *pFile = fopen("input.txt", "r");
    double intTemp = -1;

    // 파일 읽기 성공
    while (!feof(pFile))
    {
        fscanf(pFile, "%lf", &intTemp);
        if (rootNode->data == -1)
        {
            countNumber++;
            Node *newNode = (Node *)malloc(sizeof(Node));
            newNode->data = intTemp;
            newNode->link = NULL;
            rootNode = newNode;

            if (intTemp > 5000)
            {
                extraNumber++;
            }
        }

        else
        {
            searchcount = 0;
            searchcount = Search(rootNode, intTemp);

            if (searchcount == 5)
            {
                countNumber++;
                insertLast(rootNode, intTemp);
            }

            if (intTemp > 5000)
            {
                extraNumber++;
            }
        }
    }

    printf("The total number of nodes: %d\n", countNumber);
    printf("More than 5000 values: %d", extraNumber);

    fclose(pFile); //close file
    freeList(rootNode);
    return 0;
}

int Search(Node *ptr, double searchNum)
{
    while (ptr != NULL)
    {
        if (ptr->data == searchNum)
            return 1;
        else
            ptr = ptr->link;
    }
    return 5;
}

int insertLast(Node *ptr, double insertNum)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = insertNum;
    newNode->link = NULL;

    while (ptr->link != NULL)
    {
        ptr = ptr->link;
    }
    ptr->link = newNode;

    return 0;
}

int freeList(Node *ptr)
{
    Node *prev = NULL;
    while (ptr != NULL)
    {
        prev = ptr;
        ptr = ptr->link;
        free(prev);
    }
    return 0;
}