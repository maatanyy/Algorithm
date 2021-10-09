#include <stdio.h>
#include <stdlib.h> //동적할당, malloc 사용하기 위해 추가
#include <time.h>

// 해야할 일
// 트리 노드 형식 구현
// 1. choose binary or AVL
// 2. 트리 이용하여 정렬구현,
// 3. 검색 + 삽입 구현

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

void preorderTraversal(Node *ptr) //전위순회함수를 통해 값 있나 확인
{
	if (ptr) //만약 ptr이 있다면 즉 Node가 있다면
	{
		printf("[%d]   ", ptr->key);   //노드의 키를찍고
		preorderTraversal(ptr->left);  //Node의 left로 다시 재귀적 호출
		preorderTraversal(ptr->right); //Node의 right로 다시 재귀적 호출
	}
}

int main(void)
{
	int searchNum;
	Node *rootNode = (Node *)malloc(sizeof(Node)); //동적할당으로 rootNode 만들어주고 키에 -10 (음수초기값으로 설정, 키값이 다 양수이므로 구분하기위해)
	rootNode->key = -10;
	rootNode->right = NULL;
	rootNode->left = NULL;

	clock_t timecheck; //timecheck용

	FILE *pFile = fopen("test.txt", "r"); //read mode
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}

	// 파일 읽기 성공
	while (1)
	{
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0)
			break;

		// binary_search 트리생성
		Node *tempNode = rootNode;
		Node *tempNode2 = rootNode;
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->key = intTemp;
		newNode->right = NULL;
		newNode->left = NULL;

		if (rootNode->key == -10) // 루트노드가 없는 경우 즉 처음인 경우
		{
			rootNode = newNode; // 처음 들어오는 걸 루트로 설정해줌 이 test.txt의 경우 526
		}

		else //루트노드가 있는 경우
		{
			while (tempNode != NULL) //리프노드가 아니면 계속진행
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
		// 생성된 트리에서 키 검색
		//printf("%d ", intTemp);
	}

	//preorderTraversal(rootNode);  //트리 정상 작동여부 확인용 전위순회 함수
	//파일 형태로 반환
	printf("\n");
	printf("검색을 원하는 키를 입력해주세요: ");
	scanf("%d", &searchNum);

	fclose(pFile); //close file
	return 0;
}