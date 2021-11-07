#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP_SIZE 200

typedef struct node
{
    char word;  //글자
    int number; //카운트
    struct node *left;
    struct node *right;
} Node;

typedef struct
{
    int number;
    char word;
    Node *tree;
} element;

typedef struct
{
    element heap[MAX_HEAP_SIZE];
    int heapsize;
} Heap;

typedef struct alphabet
{
    char word;
    int count;
    struct alphabet *link;
} Alphabet;

int insertLast(Alphabet *ptr, char word, int count)
{

    Alphabet *tempNode = (Alphabet *)malloc(sizeof(Alphabet));
    tempNode->word = word;
    tempNode->link = NULL;
    tempNode->count = count;

    while (ptr->link != NULL)
    {
        ptr = ptr->link;
    }

    ptr->link = tempNode;
    return 0;
}

int searchFunc(Alphabet *ptr, char word)
{
    if (ptr->word == '$')
    {
        ptr->word = word;
        ptr->count = 1;
    }

    while (ptr->link != NULL)
    {
        if (ptr->word == word)
        {
            ptr->count++;
            return 0;
        }
        ptr = ptr->link;
    }

    if (ptr->word == word)
    {
        ptr->count++;
        return 0;
    }
    return 1;
}

int main()
{
    char str[200];
    int length = 0;

    printf("Put the string to encode: ");
    scanf("%s", str);
    length = strlen(str); //입력 받은 문자열 길이 count에 저장
    printf("%d\n", length);

    Alphabet *rootNode = (Alphabet *)malloc(sizeof(Alphabet));
    rootNode->link = NULL;
    rootNode->count = 0;
    rootNode->word = '$';

    for (int i = 0; i < length; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'z')
        {

            if (searchFunc(rootNode, str[i]) == 1)
            {
                insertLast(rootNode, str[i], 1);
            }
        }
    }

    for (rootNode; rootNode != NULL; rootNode = rootNode->link)
    {
        printf("%c", rootNode->word);
        printf("%d", rootNode->count);
    }

    //printf("encoding...\n\n");
    //printf("Encoded result: ");
    //printf("decoding...\n\n");
    //printf("Decoded result: ",);

    return 0;
}

/*if (rootNode->word == '$')
            {
                printf("a4");
                rootNode->word = str[i];
                rootNode->count = 1;
            }

            else
            {
                printf("a5");
                for (rootNode; rootNode->link != NULL; rootNode = rootNode->link)
                {
                    if (rootNode->word == tempNode->word)
                    {
                        printf("a6");
                        rootNode->count++;
                    }
                }

                if (rootNode->word == tempNode->word)
                {
                    printf("a6");
                    rootNode->count++;
                }*/