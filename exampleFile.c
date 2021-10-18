#include <stdio.h>
#include <stdlib.h> //동적할당, malloc 사용하기 위해 추가
#include <time.h>

#define RED 1;	 //RED 1으로 정의
#define BLACK 0; //BLACk 0으로 정의

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
	int color;
} Node;

static Node *NIL; //Red Black Tree의 마지막에 리프노드는 NIL이라고 일반적인 리프노드와 다른 리프노드를 가르키는데 이때 사용하기위해 선언

void InsertNode(Node **, Node *);
void InspectNode(Node **, Node *);
void LeftRotate(Node **, Node *);
void RightRotate(Node **, Node *);

int main(void)
{
	Node *rootNode = (Node *)malloc(sizeof(Node)); //로트노드 동적할당 해주고 키 값 설정 및 링크 , 색 설정
	rootNode->key = -10;
	rootNode->right = NULL;
	rootNode->left = NULL;
	rootNode->color = BLACK;

	NIL = (Node *)malloc(sizeof(Node)); //NIL 동적할당해주고 color BLACK으로 선언, RBT의 마지막 리프노드
	NIL->color = BLACK;

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
		Node *root = rootNode;

		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0)
			break;

		// 트리생성
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
			InsertNode(&root, newNode); //이진트리 처럼 노드의 위치를 찾아 삽입
			newNode->color = RED;		//삽입한 노드의 색을 RED로 해줍니다
			newNode->left = NIL;		//노드의 left, right를 NIL로 설정해줍니다
			newNode->right = NIL;
			InspectNode(&root, newNode); //RED_BLACK_TREE를 깨나 검사해줍니다
		}
		// 생성된 트리에서 키 검색
		printf("%d ", intTemp);
	}

	//파일 형태로 반환

	fclose(pFile); //close file
	return 0;
}

void InsertNode(Node **rootNode, Node *newNode) //노드를 삽입하는 함수
{
	Node *root = (*rootNode);

	if (root->key < newNode->key)
	{
		if ((root->right == NULL) || (root->right == NIL))
		{
			root->right = newNode;
			newNode->parent = root;
		}
		else
		{
			InsertNode(&(root->right), newNode);
		}
	}

	else if (root->key > newNode->key)
	{
		if ((root->left == NULL) || (root->left == NIL))
		{
			root->left = newNode;
			newNode->parent = root;
		}
		else
		{
			InsertNode(&(root->left), newNode);
		}
	}
}

void InspectNode(Node **rootNode, Node *newNode) //노드를 검사하는 함수
{
	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //삽입된 노드의 부모의 부모를 grandparent로 설정해줍니다
	//삽입될 노드의 부모가 BLACK 일 경우는 문제가 되지 않으므로 삽입될 노드의 부모가 RED일 경우만 고려해줍니다

	if (newNode->parent->color == 1) //삽입될 노드의 부모가 RED 노드일 경우 문제가 발생한다
	{

		Node *other = newNode->parent->parent->right; //부모의 부모의 오른쪽 자식을 other로 해줍니다
		Node *other2 = newNode->parent->parent->left; //부모의 부모의 왼쪽 자식을 other2로 해줍니다

		//Root 기준 왼쪽으로 newNode가 들어오는 경우
		//Case 1: other 가 RED인 경우
		if (other->color == 1)				//만약 부모의 부모의 오른쪽 자식 색이 RED 일 경우
		{									//case1
			newNode->parent->color = BLACK; //삽입될 노드의 부모를 BLACK으로 바꿔줍니다
			other->color = BLACK;
			InspectNode(&root, newNode->parent->parent); // 위로 올라가며 문제가 있을 시 재귀적으로 다시 수정
		}

		if ()

			//Case 2-1
			else if ((newNode->parent->right == newNode) && (other->color == 0))
			{ //조부모 다른 자식이 검정이고 삽입노드가 부모노드의 오른쪽 자식인경우
				LeftRotate(&root, newNode);
			}

		//Case 2-2
		else if ((newNode->parent->left == newNode) && (other->color == 0))
		{ //조부모 다른 자식이 검정이고 삽입노드가 부모노드의 왼쪽 자식인경우
			RightRotate(&root, newNode);
		}

		//Root 기준 오른쪽으로 newNode가 들어오는 경우
		//Case 1: other2 가 RED인 경우
		if (other2->color == 1)				//만약 부모의 부모의 오른쪽 자식 색이 RED 일 경우
		{									//case1
			newNode->parent->color = BLACK; //삽입될 노드의 부모를 BLACK으로 바꿔줍니다
			other2->color = BLACK;
			InspectNode(&root, newNode->parent->parent); // 위로 올라가며 문제가 있을 시 재귀적으로 다시 수정
		}

		//Case 2-1
		else if ((newNode->parent->right == newNode) && (other2->color == 0))
		{ //조부모 다른 자식이 검정이고 삽입노드가 부모노드의 오른쪽 자식인경우
			RightRotate(&root, newNode);
		}

		//Case 2-2
		else if ((newNode->parent->left == newNode) && (other2->color == 0))
		{ //조부모 다른 자식이 검정이고 삽입노드가 부모노드의 왼쪽 자식인경우
			LeftRotate(&root, newNode);
		}
	}
}

void LeftRotate(Node **rootNode, Node *newNode) //LeftRotate 함수
{
	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //삽입된 노드의 부모의 부모를 grandparent로 설정해줍니다
	Node *parent = newNode->parent;
	parent->right = newNode->left;
	grandparent->left = newNode;
	newNode->left = parent;
	root = grandparent;
	InspectNode(&root, newNode->left);
	printf("☆");
}

void RightRotate(Node **rootNode, Node *newNode) //RightRotate 함수
{
	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //삽입된 노드의 부모의 부모를 grandparent로 설정해줍니다
	Node *parent = newNode->parent;
	grandparent->left = parent->right;
	parent->right = grandparent;
	grandparent = parent;
	root = grandparent;
	grandparent->color = BLACK;
	parent->color = BLACK;
	printf("★");
}