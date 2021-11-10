#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP_SIZE 200

typedef struct alphabet
{
    char word;
    int count;
    struct alphabet *link;
    struct alphabet *left;
    struct alphabet *right;
} Alphabet;

Alphabet *rootNode2;

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

int insertLast2(Alphabet *ptr, Alphabet **ptr2, Alphabet *addnode)
{
    Alphabet *tempNode = (Alphabet *)malloc(sizeof(Alphabet));
    Alphabet *search = (*ptr2)->link;
    tempNode->count = addnode->count;

    tempNode->link = NULL;

    if ((*ptr2)->link == NULL)
    {
        (*ptr2)->link = tempNode;
        return 0;
    }

    //*(ptr2)->link
    while (search->link != NULL)
    {
        search = search->link;
    }
    search->link = tempNode;
    return 0;
}

int searchFunc(Alphabet *ptr, char word)
{
    if (ptr->word == '$')
    {
        ptr->word = word;
        ptr->count = 1;
        return 0;
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

Alphabet *findVertex(Alphabet *ptr, char word)
{
    while (ptr->link != NULL)
    {
        if (ptr->word == word)
        {
            printf("Yes. %c\n", ptr->word);
            return ptr;
        }
        ptr = ptr->link;
    }

    if (ptr->word == word)
    {
        printf("Yes. %c\n", ptr->word);
        return ptr;
    }
    else
    {
        printf("No.\n");
        return NULL;
    }
}

Alphabet *findSmall(Alphabet *ptr, Alphabet **ptr2)
{
    int small = 10000;
    Alphabet *tempNode = (*ptr2)->link;
    Alphabet *smallNode;

    if ((*ptr2)->link == NULL)
    {
        return NULL;
    }

    //반복하며 최소 찾기
    while (tempNode->link != NULL)
    {

        if (tempNode->count < small)
        {
            small = tempNode->count;
            smallNode = tempNode;
        }
        tempNode = tempNode->link;
    }

    //마지막
    if (tempNode->count < small)
    {
        small = (*ptr2)->link->count;
        smallNode = tempNode;
    }

    //여기까지 왔을 때
    //smallNode는 가장 count가 적은 노드임
    /* if (smallNode == ptr)
    {
        if (ptr->link == NULL)
        {
            Alphabet* temp = ptr;
            temp->count = ptr->count;
            temp->word = ptr->word;
            temp->link = NULL;
            (*ptr2)->link = NULL;
            printf("S%d", (*ptr2)->link);
            return temp;
        }
        ptr = ptr->link;
    }
    */

    if (smallNode == (*ptr2)->link) //가장작은노드가 맨앞에있을때
    {
        if ((*ptr2)->link->link == NULL) //노드가 하나일때
        {
            Alphabet *temp = (*ptr2)->link;
            temp->count = (*ptr2)->link->count;
            temp->word = (*ptr2)->link->word;
            temp->link = NULL;
            (*ptr2)->link = NULL;
            return temp;
        }
        else
        { //노드가 여러개일때
            (*ptr2)->link = (*ptr2)->link->link;
        }
    }

    else if (smallNode != (*ptr2)->link)
    {
        Alphabet *prevNode = (*ptr2)->link;
        while (prevNode->link != smallNode)
        //while(prevNode!=smallNode)
        {
            prevNode = prevNode->link;
        }
        prevNode->link = smallNode->link;
    }
    smallNode->link = NULL;

    return smallNode;
}

int main()
{
    char str[200];
    int length = 0;
    char fv[1];

    printf("Put the string to encode: ");
    scanf("%s", str);
    length = strlen(str); //입력 받은 문자열 길이 count에 저장
    //printf("%d\n", length);

    Alphabet *rootNodepoint = (Alphabet *)malloc(sizeof(Alphabet));
    Alphabet *rootNode = (Alphabet *)malloc(sizeof(Alphabet));
    rootNodepoint->link = rootNode;

    rootNode->link = NULL; //알파벳 세기 위해 사용하는 link
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

    //printf("find vertex :");
    //scanf("%s", fv);

    //Alphabet *find = findVertex(rootNode, fv[0]);

    while (rootNodepoint->link != NULL)
    {
        Alphabet *find1 = findSmall(rootNode, &rootNodepoint);
        Alphabet *find2 = findSmall(rootNode, &rootNodepoint);
        if (find2 == NULL)
        {
            rootNodepoint->link = find1;
            break;
        }

        Alphabet *haffman = (Alphabet *)malloc(sizeof(Alphabet));
        haffman->link = NULL;
        haffman->left = find1;
        haffman->right = find2;
        haffman->count = find1->count + find2->count;
        insertLast2(rootNode, &rootNodepoint, haffman);
    }

    printf("마지막 노드의 카운트:%d\n", rootNodepoint->link->count);

    //printf("%d", (rootNodepoint->link)->count);

    //printf("encoding...\n\n");
    //printf("Encoded result: ");
    //printf("decoding...\n\n");
    //printf("Decoded result: ",);

    return 0;
}
