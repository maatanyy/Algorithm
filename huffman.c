//2018038076 소프트웨어학과 2학년 노민성 허프만 인코딩 & 디코딩
// 2021.11.11
//**********************************************************************
// frequency 가 동일한 경우 A,B 가 있으면 A가 왼쪽 B가 오른쪽으로 갑니다.
// 하지만 A+B (4) C(4)와 같이 새로 합쳐진 노드와 fequency가 같은 노드가 있으면 늦게 생긴 노드가 오른쪽으로 갑니다
// 새로운 노드를 기존의 연결리스트의 마지막에 추가를 해줘서 최소값을 뽑으면 늦게 나와서 오른쪽으로 갑니다

#include <stdio.h>
#include <stdlib.h> //동적할당하기 위해 추가
#include <string.h> //string 쓰기위해 추가

typedef struct alphabet //Alphabet 구조체 선언
{
    char word;              //char 형 word
    int count;              //글자가 몇번 들어왔나 count할 때 사용
    int count2;             //shownum 함수에서 사용됩니다
    struct alphabet *link;  //연결리스트 만들기 위해 사용
    struct alphabet *left;  //트리의 left에 사용
    struct alphabet *right; //트리의 right에 사용
} Alphabet;

//Alphabet *rootNode2;

char code[500];      //incoding 하는 숫자 담는데 사용 (정수형)
char temp[500];      //incoding에서 decoding 가기위해 사용 code[500]에서 정수형 숫자를 str로 바꿔주기 위해 사용합니다
char save[200][200]; //각 문자의 코드(ex110)을 할당하는데 사용합니다.
int stack[200];      //stack 선언
int top = -1;        //top -1로 선언

void push(int n) //stack 의 push
{
    top += 1; //top을 하나 추가해주고 들어온 정수를 스택에 넣어줍니다
    stack[top] = n;
}

int pop() //stack 의 pop
{
    int number = stack[top]; //스택의 top안에 있는 숫자가 number가 됩니다
    top -= 1;                //top을 하나 줄여줍니다
    return number;           //number를 반환해줍니다
}

int insertLast(Alphabet *ptr, char word, int count) //연결리스트 마지막에 추가하는 함수
{
    Alphabet *tempNode = (Alphabet *)malloc(sizeof(Alphabet)); //tempNode를 동적할당해줍니다
    tempNode->word = word;                                     //노드의 word에 들어온 word를 넣어주고 나머지 모든 link는 NULL로 해줍니다
    tempNode->left = NULL;
    tempNode->right = NULL;
    tempNode->link = NULL;
    tempNode->count = count; //tempNode의 카운트는 들어온 카운트가 됩니다

    while (ptr->link != NULL) //만약 마지막 노드가 아니면 옆으로 옮깁니다
    {
        ptr = ptr->link;
    }

    ptr->link = tempNode; //마지막 노드의 link에 tempNode를 연결해줍니다
    return 0;
}

int insertLast2(Alphabet *ptr, Alphabet **ptr2, Alphabet *addnode) //마지막에 추가해주는 함수 기존의 연결리스트에서
//하프만 트리만들떄 두개의 노드가 합쳐져 새로운 노드를 만들때 사용합니다

{
    Alphabet *tempNode = (Alphabet *)malloc(sizeof(Alphabet)); //tempNode를 할당해줍니다
    Alphabet *search = (*ptr2)->link;                          //search는 rootPointer의 link를 가르킵니다(값 바꾸기위해)
    tempNode->count = addnode->count;                          //tempNode의 카운트에 addNode의 카운트를 넣어주고
    tempNode->left = addnode->left;                            //tempNode의 left가 addNode의 left를 가르킵니다
    tempNode->right = addnode->right;                          //tempNode의right가 addNode의 right를 가르킵니다
    tempNode->link = NULL;                                     //tempNode의 link는 null로 설정해줍니다

    if ((*ptr2)->link == NULL) //만약 노드가 하나도 없다면
    {
        (*ptr2)->link = tempNode; //헤드노드가 tempNode가 됩니다
        return 0;
    }

    //*(ptr2)->link
    while (search->link != NULL) //연결리스트가 비어있지않다면
    {
        search = search->link; //마지막까지 이동해주고
    }
    search->link = tempNode; //마지막에 tempNode를 연결시켜줍니다
    return 0;
}

int searchFunc(Alphabet *ptr, char word) //문자가 이미 연결리스트에 있나 확인하는 함수입니다
{
    if (ptr->word == '$') //ptr->word가 '$'인 경우, 즉 처음인 경우
    {
        ptr->word = word; //ptr의 word를 word로 바꿔주고
        ptr->count = 1;   //ptr의 카운트를 1로 해줍니다
        return 0;
    }

    while (ptr->link != NULL) //ptr에 연결이 있다면
    {
        if (ptr->word == word) //만약이 ptr->word가 새로 들어온 word랑 같다면
        {
            ptr->count++; //카운트만 하나 증가시켜주고 리턴해줍니다
            return 0;
        }
        ptr = ptr->link; //if문에 해당 안되는 경우 즉 지금 노드랑 새로 들어온 노드의 문자랑 다른 경우 옆 노드로 이동합니다
    }

    if (ptr->word == word) //반복문 탈출후, 즉 마지막 노드랑 마지막으로 비교해주고 같을 경우 count를 하나 증가시켜줍니다
    {
        ptr->count++;
        return 0; //종료
    }
    return 1; //종료
}

//vertext가 있나 찾아보는 함수입니다, 중간에 값 찾기 위해 만들었는데 하프만 트리에서는 안쓰입니다

/*Alphabet *findVertex(Alphabet *ptr, char word)
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
}*/

Alphabet *findSmall(Alphabet *ptr, Alphabet **ptr2) //최소값을 반환해주는 함수입니다
{
    int small = 10000;                  //small을 10000으로 해주고
    Alphabet *tempNode = (*ptr2)->link; //tempNode는 rootNode포인터의 link를 가르킵니다
    Alphabet *smallNode;                //smallNode포인터 선언

    if ((*ptr2)->link == NULL) //만약 헤드가 없다면 NULL반환 (트리에서 노드가 없는 경우)
    {
        return NULL;
    }

    //반복하며 최소 찾기
    while (tempNode->link != NULL) //만약 NULL이 아니라면, 노드가 있다면
    {

        if (tempNode->count < small) //만약 노드의 count가 small보다 작다면
        {
            small = tempNode->count; //노드의 count를 small로 바꿔주고
            smallNode = tempNode;    //smallNode는 tempNode를 가르키고
        }
        tempNode = tempNode->link; //tempNode는 tempNode->link가 됩니다
    }

    //마지막
    if (tempNode->count < small) //마지막에 위에 과정을 한번더 진행해줍니다(반복문 탈출했을 경우)
    {
        small = (*ptr2)->link->count;
        smallNode = tempNode;
    }

    if (smallNode == (*ptr2)->link) //가장 작은노드가 맨앞에있을때
    {
        if ((*ptr2)->link->link == NULL) //노드가 하나일때
        {
            Alphabet *temp = (*ptr2)->link;     //temp는 맨앞을 가르키고
            temp->count = (*ptr2)->link->count; //temp의 카운트는 맨앞의 카운트와 같고
            temp->word = (*ptr2)->link->word;   //temp의 word도 같고
            temp->link = NULL;                  //temp->link는 NULL로 해줍니다
            (*ptr2)->link = NULL;               //처음이 NULL이되고
            return temp;                        //temp를 반환해줍니다
        }
        else
        {                                        //노드가 여러개일때
            (*ptr2)->link = (*ptr2)->link->link; //옆으로 이동합니다
        }
    }

    else if (smallNode != (*ptr2)->link) //만약 가장 작은 노드(frequency가..) 가 맨앞 노드가 아니면
    {
        Alphabet *prevNode = (*ptr2)->link; //prevNode는 맨앞을 가르키고
        while (prevNode->link != smallNode) //preVNode의 link가 smallNode를 가르키는게 아니라면 계속 prevNode를 옆으로 옮기며 비교하고
        //while(prevNode!=smallNode)
        {
            prevNode = prevNode->link;
        }                                 //반복문을 탈출했을경우, 즉 prevNode의 link가 smallNode를 가르키는 경우
        prevNode->link = smallNode->link; //prevNode의 link는 smallNode의 link를 가르킵니다
    }
    smallNode->link = NULL; //smallNode의 link를 NULL로 해주고

    return smallNode; //smallNode를 반환해줍니다
}

void information() //스택에 쌓인 내용을 모두 pop해주며 내용을 출력해주는 함수입니다
{
    for (int i = top - 1; i >= 0; i--) //top-1부터 i>=0일떄까지 i를 줄여가며
    {
        printf("%d", stack[i]); //stack의 내용을 출력해주고
    }
    printf("\n"); //다출력하면 개행해줍니다
}

/*void makeTable(Alphabet *ptr)
{
    if (ptr->left == NULL && ptr->right == NULL)
    {
        if (ptr->word >= 'A' && ptr->word <= 'z')
        {
            code[ptr->word] = "\0";
        }
    }

    else
    {
        if (ptr->left != NULL)
        {
            if (ptr->word >= 'A' && ptr->word <= 'z')
            {
                code[ptr->word] = "0";
            }
        }
        if (ptr->right != NULL)
        {
            if (ptr->word >= 'A' && ptr->word <= 'z')
            {
                code[ptr->word] = "1";
            }
        }
    }
}*/

/*void printTable(Alphabet *ptr)
{
    if (ptr->left == NULL && ptr->right == NULL)
    {
        printf("%c : %s\n", ptr->word, code[ptr->word]);
    }

    else
    {
        if (ptr->left != NULL)
        {
            printTable(ptr->left);
        }
        if (ptr->right != NULL)
        {
            printTable(ptr->right);
        }
    }
}*/

void showNum(Alphabet *ptr) // 알파벳에 숫자를 할당해주는 함수입니다
{
    ptr->count2 = top;             //count2는 top이 되고
    for (int i = 0; i <= top; i++) //i=0부터 i<=top이면 i를 하나씩 증가시켜주며
    {
        printf("%d", stack[i]);        //stack[i]를 출력해주고
        save[ptr->word][i] = stack[i]; //save[알파벳][i]에 그 스택값을 넣어줍니다
    }

    printf("\n"); //개행해줍니다
}

void inorderTraversal(Alphabet *ptr) //중위순회함수입니다
{
    if (!ptr) //ptr이 없다면
    {
        pop();  //pop해준다
        return; //종료
    }
    push(0);                                     //0을 push 해준다
    inorderTraversal(ptr->left);                 //ptr->left로 재귀호출해준다
    if (ptr->left == NULL && ptr->right == NULL) //리프노드일경우
    {
        printf("%c : ", ptr->word); //해당 노드의 word를 출력해주고
        showNum(ptr);               //showNum를 호출해서 스택에 쌓인 것들을 pop해준다
    }
    push(1);                      //1을 push해준다
    inorderTraversal(ptr->right); //ptr->right로 재귀호출해준다
    pop();                        //pop해줘서 다음 ptr로 가게해준다
}

int Encoding(char str[]) //Encoding하는 함수입니다
{
    int length = strlen(str);        //str의 길이를 length에 넣어주고
    int k = 0;                       //int k=0을 선언해줍니다
    for (int i = 0; i < length; i++) //i는 0부터 문자열의 길이만큼 반복하며 (즉 ABCDED..를 예로들면 한 문자씩 반복문을 진행합니다)
    {
        int j = 0; //j=0

        while (save[str[i]][j] == 0 || save[str[i]][j] == 1) //알파벳의 코드가 0이거나 1일 경우 (하프만트리에서 왼쪽0, 오른쪽 1로해줌)
        {                                                    //초기화를 -1로 해서 0이거나 1이면 값이 있다는 뜻!
            printf("%d", save[str[i]][j]);                   //값을 출력해주고
            code[k] = save[str[i]][j];                       //code[k]에 값을 저장해줍니다
            j++;                                             //j와 k를 증가시켜서 code[k]에 값이 잘 들어갈수 있도록 합니다
            k++;
        }
    }
}

char Decoding(char str[], Alphabet *ptr) //Decoding 해주는 함수입니다
{
    Alphabet *temp = ptr->link; //temp는 ptr->link를 가르켜주고
    int i = 0;                  //i=0
    int length = strlen(str);   //str의 길이를 length에 넣어줍니다

    while (str[i] != '\0') //만약 문자열의 끝이 아니라면
    {
        if (str[i] == '0') //만약 0이 나온다면
        {
            temp = temp->left; //왼쪽으로 템프를 보내주고
        }
        else if (str[i] == '1') //만약 1이 나온다면
        {
            temp = temp->right; //오른쪽으로 템프를 보내주고
        }
        if ((temp->left == NULL) && (temp->right == NULL)) //temp가 리프노드라면
        {
            printf("%c", temp->word); //노드의 word를 출력해주고
            temp = ptr->link;         //temp를 다시 맨위로 바꿔줍니다 (트리에서)
        }
        i++; //i를 증가시켜 다음을 확인합니다
    }
}

int freeTree(Alphabet *ptr) //tree의 메모리를 해제 해주는 함수
{
    //첫 노드가 제일 마지막에 왼쪽/오른쪽 돌고 마지막에 해제하도록 후위순회를 이용
    if (ptr != NULL)
    {                         //head가 null이 아니면
        freeTree(ptr->left);  //freeBST를 head->left를 이용해 다시 호출
        freeTree(ptr->right); //head->right가 head가 아닌 경우에는 freeBST를 head->right로 호출해준다
        free(ptr);            //head를 해제해준다.
        return 1;             //리턴
    }
    return 1; //리턴
}

int main() //메인함수입니다
{
    char str[200];                  //크기가 200인 문자열 str을 선언해줍니다
    memset(save, -1, sizeof(save)); //전역 변수 save의 모든 원소를 -1로 초기화시켜줍니다
    memset(code, -1, sizeof(code)); //전역 변수 code의 모든 원소를 -1로 초기화시켜줍니다
    int length = 0;                 //length 는 0으로 해주고
    char fv[1];                     //fv[1]을 선언해줍니다

    printf("Put the string to encode: "); //encode할 string을 입력받고
    scanf("%s", str);
    length = strlen(str); //입력 받은 문자열 길이 count에 저장
    //printf("%d\n", length);

    Alphabet *rootNodepoint = (Alphabet *)malloc(sizeof(Alphabet)); //rootNodepoint 동적할당
    Alphabet *rootNode = (Alphabet *)malloc(sizeof(Alphabet));      //rootNode 동적할당
    rootNodepoint->link = rootNode;                                 //rootNodepoint의 link는 rootNode를 가르킵니다

    rootNode->link = NULL; //rootNode의 link를 NULL로 해주고
    rootNode->count = 0;   //rootNode의 count를 0으로 해줍니다
    rootNode->word = '$';  //rootNode의 word 를 '$'로 초기화 해줍니다

    for (int i = 0; i < length; i++) //i는 0부터 입력받은 문자열의 길이만큼 반복하며
    {
        if (str[i] >= 'A' && str[i] <= 'z') //아스키코드 기준 A ~z의 사이의 값이 들ㅇ온다면
        {
            if (searchFunc(rootNode, str[i]) == 1) //search함수를 통해 기존의 연결리스트에 있나 확인해주고
            {
                insertLast(rootNode, str[i], 1); //만약 없다면 ,즉 새로운 문자가 들어왔다면 insertLast 함수를 호출해 연결리스트에 추가해줍니다
            }
        }
    }

    while (rootNodepoint->link != NULL) //만약 rootNodePoint의 link가 NULL이 아니라면
    {
        Alphabet *find1 = findSmall(rootNode, &rootNodepoint); //findSmall함수를 호출해서 find1 (최솟값)을 구하고
        Alphabet *find2 = findSmall(rootNode, &rootNodepoint); //findSmall함수를 호출해서 find2 (최솟값)을 구합니다
        if (find2 == NULL)                                     //만약 하나밖에 없어서 최솟값 2개를 구할 수 없는 경우에는
        {
            rootNodepoint->link = find1; //find1 즉 하나 남은걸 rootNodepoint가 가르키고 반복문을 탈출합니다
            break;
        }

        Alphabet *haffman = (Alphabet *)malloc(sizeof(Alphabet)); //hffman을 동적할당해주고
        haffman->link = NULL;                                     //haffman의 link는 NULL로 해줍니다
        haffman->left = find1;                                    //haffman의 left는 find1이 되고
        haffman->right = find2;                                   //haffman의 right는 find2이 되고
        haffman->count = find1->count + find2->count;             //카운트는 합쳐줍니다
        insertLast2(rootNode, &rootNodepoint, haffman);           //그리고 새로운 haffman을 insertLast2를 통해 연결리스트에 넣어줍니다
    }

    //printf("마지막 노드의 카운트: %d\n", rootNodepoint->link->count);
    inorderTraversal(rootNodepoint->link); //문자마다 코드 생성
    //makeTable(rootNodepoint->link);
    //printTable(rootNodepoint->link);
    //inorderTraversal(rootNodepoint->link);

    printf("encoding...\n\n");
    printf("Eecoded result: ");
    Encoding(str); //입력 받은 str을 Encoding함수를 호출해 encoding해줌
    printf("\n");
    printf("decoding...\n\n");
    printf("Decoded result: ");

    int t = 0;            //code배열에 인코딩된 문자가 정수형으로 있는데 이걸 temp형에 str로 바꿔줍니다
    while (code[t] != -1) //처음에 -1로 초기화해서 값이 없는 경우 즉0,1이 아니면 탈출합니다
    {
        if (code[t] == 1) //1이면 temp[t]에 '1'을 넣어주고
        {
            temp[t] = '1';
        }
        else if (code[t] == 0) //0이면 temp[t]에 '0'을 넣어줍니다
        {
            temp[t] = '0';
        }
        t++; //t를 증가시켜줘서 다음도 진행합니다
    }
    temp[t] = '\0'; //마지막에 문자열의 끝을 알리는 널을 추가합니다
    //printf("%s\n", temp); temp에 스트링 있나 확인용

    Decoding(temp, rootNodepoint); //temp를 Decoding함수를 호출해 Decoding해줍니다
    free(rootNodepoint->link);     //메모리 해제해주는 함수
    return 0;
}
