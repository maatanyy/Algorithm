#include <stdio.h>
#include <stdlib.h> //동적할당, malloc 사용하기 위해 추가
#include <time.h>

#define RED 1;	 //RED 1으로 정의
#define BLACK 0; //BLACk 0으로 정의

typedef struct node  //
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
	rootNode->right = NIL;
	rootNode->left = NIL;
	rootNode->color = BLACK;

	NIL = (Node *)malloc(sizeof(Node)); //NIL 동적할당해주고 color BLACK으로 선언, RBT의 마지막 리프노드
	NIL->color = BLACK;

	FILE *pFile = fopen("test2.txt", "r"); //read mode
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
		newNode->right = NIL;
		newNode->left = NIL;

		if (rootNode->key == -10) // 루트노드가 없는 경우 즉 처음인 경우
		{
			rootNode = newNode; // 처음 들어오는 걸 루트로 설정해줌 이 test.txt의 경우 526
			rootNode->key = newNode->key;
			//printf("--");
		}

		else if (rootNode->key != -10) // 루트노드가 있는 경우
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

	if (root->color == 1)
	{
		root->color = 0;
	}

	//삽입될 노드의 부모가 BLACK 일 경우는 문제가 되지 않으므로 삽입될 노드의 부모가 RED일 경우만 고려해줍니다

	//printf("Insepct");

	if (newNode->parent->color == 1) //삽입될 노드의 부모가 RED 노드일 경우 문제가 발생한다
	{
		Node *other = newNode->parent->parent->right; //부모의 부모의 오른쪽 자식을 other로 해줍니다
		Node *other2 = newNode->parent->parent->left; //부모의 부모의 왼쪽 자식을 other2로 해줍니다

		if ((grandparent->right == NIL) && (newNode == newNode->parent->left))
		{
			newNode->parent->color = 0;
			grandparent->color = 1;
			RightRotate(&root, grandparent);
		}

		else if ((grandparent->right == NIL) && (newNode == newNode->parent->right))
		{
			LeftRotate(&root, newNode->parent);
			newNode = newNode->left;
			InspectNode(&root, newNode);
		}

		else if ((newNode == newNode->parent->left) && ((other != NIL) && (other->color == 0)))
		//other가 할아버지 기준 오른쪽에 있고 새로운 노드가 부모의 왼쪽 자식인 경우, 강의자료 Case 2-1
		{
			newNode->parent->color = 0;
			grandparent->color = 1;
			RightRotate(&root, grandparent);
		}

		else if ((newNode = newNode->parent->right) && ((other != NIL) && (other->color == 0)))
		//other가 할아버지 기준 오른쪽에 있고 새로운 노드가 부모의 오른쪽 자식인 경우 강의자료 Case 2-2
		{
			LeftRotate(&root, newNode->parent);
			newNode = newNode->left;
			InspectNode(&root, newNode);
		}

		else if ((other->color == 1) && (newNode->parent == grandparent->left))
		{
			newNode->parent->color = 0;
			other->color = 0;
			grandparent->color = 1;
			InspectNode(&root, grandparent);
		}

		//printf("5");
		// other2 즉 사촌이 왼쪽인 경우

		else if ((grandparent->left == NIL) && (newNode == newNode->parent->right))
		{
			newNode->parent->color = 0;
			grandparent->color = 1;
			LeftRotate(&root, grandparent);
		}

		else if ((grandparent->left == NIL) && (newNode == newNode->parent->left))
		{
			RightRotate(&root, newNode->parent);
			newNode = newNode->right;
			InspectNode(&root, newNode);
		}

		else if ((newNode == newNode->parent->right) && ((other2 != NIL) && (other2->color == 0))) //Case 2-1
		{
			newNode->parent->color = 0;
			grandparent->color = 1;
			LeftRotate(&root, grandparent);
		}

		else if ((newNode == newNode->parent->left) && ((other2 != NIL) && (other2->color == 0))) // Case 2-2
		{
			RightRotate(&root, newNode->parent);
			newNode = newNode->right;
			InspectNode(&root, newNode);
		}
		else if ((other2->color == 1) && (newNode->parent == grandparent->right)) //other2의 color가 red
		{
			newNode->parent->color = 0;
			other2->color = 0;
			grandparent->color = 1;
			InspectNode(&root, grandparent);
		}
	}
}

void RightRotate(Node **rootNode, Node *newNode) // RightRotate 함수
{
	Node *root = (*rootNode);
	Node *childnode = newNode->left; //삽입된 노드의 왼쪽 자식을 childnode로 해줍니다
	Node *pparent = newNode->parent; //삽입된 노드의 parent를 pparent로 해줍니다

	if ((childnode->right != NULL) && (childnode != NIL))
	{
		childnode->right->parent = newNode;
	}

	newNode->left = childnode->right;
	newNode->parent = childnode;
	childnode->right = newNode;
	childnode->parent = pparent;

	if (pparent == NULL)
	{
		*rootNode = childnode;
	}
	else if (newNode == pparent->left)
	{
		pparent->left = childnode;
	}
	else
	{
		pparent->right = childnode;
	}
}

void LeftRotate(Node **rootNode, Node *newNode) //LeftRotate 함수
{
	Node *root = (*rootNode);
	Node *childnode = newNode->right;
	Node *pparent = newNode->parent;

	if ((childnode->left != NULL) && (childnode != NIL))
	{
		childnode->left->parent = newNode;
	}

	newNode->right = childnode->left;
	newNode->parent = childnode;
	childnode->left = newNode;
	childnode->parent = pparent;

	if (pparent == NULL)
	{
		*rootNode = childnode;
	}
	else if (newNode == pparent->left)
	{
		pparent->left = childnode;
	}
	else
	{
		pparent->right = childnode;
	}
}
