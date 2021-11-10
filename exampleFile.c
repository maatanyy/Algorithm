//2018038076 소프트웨어학과 2학년 노민성
// 트리를 사용한 정렬 알고리즘 구현
// binary search tree로 구현하였고 search 방식은 iterative 방식을 사용하였습니다

#include <stdio.h>
#include <stdlib.h> //동적할당, malloc 사용하기 위해 추가
#include <time.h>	//시간측정하기 위해 추가

typedef struct node //Node 구조체 정의
{
	int key; //키 값과 포인터 left, right를 가짐
	struct node *left;
	struct node *right;
} Node;

int searchIterative(Node *head, int key); //키가 트리에 있나 조사해주는 함수 선언

/*void preorderTraversal(Node *ptr) //전위순회함수를 통해 트리 작동여부 확인해주는 함수
{
	if (ptr) //만약 ptr이 있다면 즉 Node가 있다면
	{
		printf("[%d]   ", ptr->key);   //노드의 키를찍고
		preorderTraversal(ptr->left);  //Node의 left로 다시 재귀적 호출
		preorderTraversal(ptr->right); //Node의 right로 다시 재귀적 호출
	}
}*/

int main(void)
{
	int searchNum; //찾을 변수 선언

	Node *rootNode = (Node *)malloc(sizeof(Node)); //동적할당으로 rootNode 만들어주고 키에 -10 (음수초기값으로 설정, 키값이 다 양수이므로 구분하기위해)
	rootNode->key = -10;						   //처음 키값 -10으로 설정
	rootNode->right = NULL;						   //rootNode의 right NULL, left NULL로 선언
	rootNode->left = NULL;

	FILE *pFile = fopen("test.txt", "r"); //read mode
	int intTemp = -1;

	if (pFile == NULL) //파일이 없을 경우 파일이 존재하지 않는 다고 출력해줌
	{
		printf("File does not exist");
		return 0;
	}

	// 파일 읽기 성공
	while (1)
	{
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) //만약 음수가 들어오면 반복문 탈출, 텍스트파일 마지막에 값이 -1로 마지막에 -1을 만나면 멈춤
			break;

		// binary_search 트리생성
		Node *tempNode = rootNode;					  //tempNode는 rootNode를 가르킴
		Node *tempNode2 = rootNode;					  //tempNode2는 rootNode를 가르킴
		Node *newNode = (Node *)malloc(sizeof(Node)); //newNode 동적할당해주고 키 들어오는 값으로 초기화 하고 right left는 NULL로 해줌
		newNode->key = intTemp;						  //newNode의 key 는 파일에서 읽은 값
		newNode->right = NULL;						  //newNode의 right, left NULL로 설정해줌
		newNode->left = NULL;

		if (rootNode->key == -10) // 루트노드가 없는 경우 즉 처음인 경우
		{
			rootNode = newNode; // 처음 들어오는 걸 루트로 설정해줌 이 test.txt의 경우 526
		}

		else //루트노드가 있는 경우
		{
			while (tempNode != NULL) // tempNode가 NULL이 아니면 계속진행
			{
				tempNode2 = tempNode;			  //tempNode2 는 tempNode를 가르킴 (처음엔 둘다 루트노드를 가르키지만 while문을 반복하며 값이바뀜)
				if (tempNode->key > newNode->key) //tempNode->key 가 newNode의 key보다 클경우
				{
					tempNode = tempNode->left; //tempNode는 tempNode->left가 된다
				}

				else if (tempNode->key < newNode->key) //tempNode의 키가 newNode의 키보다 작을경우
				{
					tempNode = tempNode->right; //tempNode는 tempNode->right가 된다
				}
			}

			//반복문을 탈출하였을 경우 즉 tempNode가 리프노드일경우
			if (tempNode2->key > newNode->key) //만약 tempNode2의 key가 newNode의 key보다 클 경우
			{
				tempNode2->left = newNode; //tempNode2->left에 newNode를 넣어준다
			}
			else if (tempNode2->key < newNode->key) //tempNode2의 키가 newNode의 키보다 작을 경우
			{
				tempNode2->right = newNode; //tempNode2의 right에 newNode를 넣어준다
			}
		}
		// 키값 출력
		printf("%d ", intTemp);
	}
	//preorderTraversal(rootNode); //트리 정상 작동여부 확인용 전위순회 함수
	//파일 형태로 반환
	printf("\n");
	printf("검색을 원하는 키를 입력해주세요: "); // search 원하는 키 입력받음
	scanf("%d", &searchNum);					 //searchNum 입력 받음
	searchIterative(rootNode, searchNum);		 //searchIterative 함수로 트리에 있나 확인

	fclose(pFile); //close file
	return 0;
}

int searchIterative(Node *head, int key) // iterative 방식으로 노드를 찾는 함수
{
	Node *search = head; //Node 포인터 search 는 head->left를 가르 킴(root)

	while (search != NULL)
	{								//search 가 NULL일떄까지 반복
		if (key < search->key)		//만약 key < search->key이면
			search = search->left;	//search는 search->left가 됨
		else if (key > search->key) //만약 key > search->key이면
			search = search->right; //search는 search->right가 됨
		else if (key == search->key)
		{												//key랑 search->key랑 같으면
			printf("찾으시는 키가 트리에 있습니다.\n"); //있다고 말해주고 종료
			return 0;
		}
	}
	//다 돌았는데 없다면 없다고 말해주고 종료
	printf("찾으시는 키가 트리에 없습니다.\n");
	return 1;
}
