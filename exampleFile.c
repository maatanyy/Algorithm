#include <stdio.h>
#include <stdlib.h> //동적할당, malloc 사용하기 위해 추가
#include <time.h>

#define RED 1;	 //RED 1으로 정의
#define BLACK 0; //BLACk 0으로 정의

typedef struct node //Node 구조체 정의
{
	int key;			 //int형 key
	struct node *left;	 //node 포인터 left (왼쪽자식)
	struct node *right;	 //node 포인터 right (오른쪽자식)
	struct node *parent; //node 포인터 parent (부모)
	int color;
} Node;

static Node *NIL; //Red Black Tree의 마지막에 리프노드는 NIL이라고 일반적인 리프노드와 다른 리프노드를 가르키는데 이때 사용하기위해 선언

void InsertNode(Node **, Node *);  //노드 삽입하는 함수
void InspectNode(Node **, Node *); //트리 검사하는 함수
void LeftRotate(Node **, Node *);  //왼쪽으로 회전하는 함수
void RightRotate(Node **, Node *); //오른쪽으로 회전하는 함수

int main(void)
{
	Node *rootNode = (Node *)malloc(sizeof(Node)); //루트노드 동적할당 해주고 키 값 설정 및 링크 , 색 설정
	rootNode->key = -10;						   //루트노드 초기 키는 -10으로 설정 (test파일은 양수부터 시작)
	rootNode->right = NIL;						   //루트의 왼쪽 오른쪽 자식 NIL로 설정
	rootNode->left = NIL;
	rootNode->color = BLACK; //루트노드의 색은 BLACK으로 설정

	NIL = (Node *)malloc(sizeof(Node)); //NIL 동적할당해주고 color BLACK으로 선언, RBT의 마지막 리프노드
	NIL->color = BLACK;

	FILE *pFile = fopen("test2.txt", "r"); //read mode
	int intTemp = -1;

	if (pFile == NULL) //파일오류나면
	{
		printf("File does not exist"); //출력
		return 0;
	}

	// 파일 읽기 성공
	while (1)
	{
		Node *root = rootNode; //root  = rootNode가르킴

		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) //만약 읽은게 음수면 종료 txt파일 마지막이 -1이라 -1에 종료됨
			break;

		// 트리생성
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->key = intTemp;
		newNode->right = NIL;
		newNode->left = NIL;

		if (rootNode->key == -10) // 루트노드가 없는 경우 즉 처음인 경우(위에서 초기 루트키를 -10으로 설정해주었음)
		{
			rootNode = newNode;			  // 처음 들어오는 걸 루트로 설정해줌 이 test.txt의 경우 526
			rootNode->key = newNode->key; //rootNode의 key는 newNode의 키가됨
		}

		else if (rootNode->key != -10) // 루트노드가 있는 경우 (처음을 제외한경우)
		{
			InsertNode(&root, newNode); //이진트리처럼 노드의 위치를 찾아 삽입
			newNode->color = RED;		//삽입한 노드의 색을 RED로 해줍니다
			newNode->left = NIL;		//노드의 left, right를 NIL로 설정해줍니다
			newNode->right = NIL;
			InspectNode(&root, newNode); //RED_BLACK_TREE를 깨나 검사해줍니다
		}
		printf("%d ", intTemp); //키 출력
								// 생성된 트리에서 키 검색
	}

	//파일 형태로 반환
	fclose(pFile); //close file
	return 0;
}

void InsertNode(Node **rootNode, Node *newNode) //노드를 삽입하는 함수, 기본적으로 이진트리 삽입과 같습니다
{
	Node *root = (*rootNode); //root = rootNode

	if (root->key < newNode->key) //만약 새로들어온 키가 루트의 키보다 클 경우
	{
		if ((root->right == NULL) || (root->right == NIL)) //1. 루트의 right가 비어있거나 NIL일 경우
		{
			root->right = newNode;	//root의 오른쪽 자식에 newNode를 연결시켜주고
			newNode->parent = root; //newNode의 부모를 root로 설정해줍니다
		}
		else //2. 만약 right가 비어있지 않을 경우 (즉 이미 값이 있는 경우)
		{
			InsertNode(&(root->right), newNode); //root->right 와 newNode로 InsertNode 함수를 다시 호출합니다
		}
	}

	else if (root->key > newNode->key) //만약 새로들어온 키가 루트의 키보다 작을 경우
	{
		if ((root->left == NULL) || (root->left == NIL)) //1. 루트의 left가 비어있거나 NIL일 경우
		{
			root->left = newNode;	//root의 왼쪽 자식에 newNode를 연결시켜주고
			newNode->parent = root; //newNode의 부모를 root로 설정해줍니다
		}
		else //2. 만약 left가 비어있지 않을 경우 (즉 이미 값이 있는 경우)
		{
			InsertNode(&(root->left), newNode); //root->left와 newNode로 InsertNode 함수를 다시 호출합니다
		}
	}
}

void InspectNode(Node **rootNode, Node *newNode) //노드를 검사하는 함수
{

	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //삽입된 노드의 부모의 부모를 grandparent로 설정해줍니다, 편의상 할아버지로 부르겠습니다

	if (root->color == 1) //만약 루트 노드의 색이 빨간색이라면
	{
		root->color = 0; //루트 노드의 색을 검정색으로 바꿔줍니다 (루트의 색은 항상 검정색이고 바꿔도 RBT의 규칙이 깨지지 않음)
	}

	//삽입될 노드의 부모가 BLACK 일 경우는 문제가 되지 않으므로 삽입될 노드의 부모가 RED일 경우만 고려해줍니다
	//printf("Insepct");
	if (newNode->parent->color == 1) //삽입될 노드의 부모가 RED 노드일 경우 문제가 발생한다
	{
		Node *other = newNode->parent->parent->right; //할아버지의 오른쪽 자식을 other로 해줍니다
		Node *other2 = newNode->parent->parent->left; //할아버지의 왼쪽 자식을 other2로 해줍니다

		//총 10가지 Case로 구분하였고 1~5번째는 other, 6~10은 other2의 case입니다

		if ((grandparent->right == NIL) && (newNode == newNode->parent->left)) //만약 other가 NIL이고 새로운 노드가 부모의 왼쪽 자식이라면
		{
			//printf("1");
			newNode->parent->color = 0;		 //새로운 노드의 부모의 색을 검정으로 바꾸고
			grandparent->color = 1;			 //할아버지 노드의 색을 빨간색으로 바꿉니다
			RightRotate(&root, grandparent); //할아버지 노드를 기준으로 오른쪽회전해줍니다
		}

		else if ((grandparent->right == NIL) && (newNode == newNode->parent->right)) //만약 other가 NIL 이고 새로운 노드가 부모의 오른쪽 자식이라면
		{
			//printf("2");
			LeftRotate(&root, newNode->parent); //새로운 노드의 부모를 기준으로 왼쪽회전해주고
			newNode = newNode->left;			//newNode를 newNode->left로 설정해줍니다
			InspectNode(&root, newNode);		//그리고 바뀐 newNode로 다시 RBT의 규칙이 깨졌나 확인해줍니다
		}

		else if ((newNode == newNode->parent->left) && ((other != NIL) && (other->color == 0)))
		//Other가 검정색이고 값이 있고 새로운 노드가 부모의 왼쪽 자식인 경우
		{
			//printf("3");
			newNode->parent->color = 0;		 //부모의 색을 검정색으로 바꿔주고
			grandparent->color = 1;			 //할아버지의 색을 빨간색으로 바꿔줍니다
			RightRotate(&root, grandparent); //할아버지를 기준으로 오른쪽 회전해줍니다
		}

		else if ((newNode = newNode->parent->right) && ((other != NIL) && (other->color == 0)))
		//Other가 검정색이고 값이 있고 새로운 노드가 부모의 오른쪽 자식인 경우
		{
			//printf("4");
			LeftRotate(&root, newNode->parent); //새로운 노드의 부모를 기준으로 왼쪽회전해주고
			newNode = newNode->left;			//newNode->left를 newNode로 설정해줍니다
			InspectNode(&root, newNode);		//바뀐 newNode로 RBT의 규칙을 깨나 다시 확인해줍니다
		}

		else if ((other->color == 1) && (newNode->parent == grandparent->left))
		//만약 할아버지 오른쪽 자식이 빨간색이고 새로운 노드의 부모가 할아버지의 왼쪽자식일경우
		{
			//printf("5");
			newNode->parent->color = 0;		 //새로운노드의 부모의 색을 검정으로 해주고
			other->color = 0;				 //other의 색을 검정으로해주고
			grandparent->color = 1;			 //할아버지의 색을 빨간색으로 해줍니다
			InspectNode(&root, grandparent); //할아버지를 기준으로 RBT를 깨나 다시 확인해줍니다
		}

		// other2 즉 사촌이 왼쪽인 경우
		else if ((grandparent->left == NIL) && (newNode == newNode->parent->right)) //할아버지의 왼쪽이 NIL이고 새로운노드가 부모의 오른쪽 자식일 경우
		{
			//printf("6");
			newNode->parent->color = 0;		//새로운 노드의 부모의 색을 검정으로 해줍니다
			grandparent->color = 1;			//할아버지의 색을 빨강으로 해줍니다
			LeftRotate(&root, grandparent); //할아버지를 기준으로 왼쪽 회전해줍니다
		}

		else if ((grandparent->left == NIL) && (newNode == newNode->parent->left)) //할아버지의 왼쪽이 NIL이고 newNode가 newNode의 부모의 왼쪽 일경우
		{
			//printf("7");
			RightRotate(&root, newNode->parent); //새로운 노드의 부모를 기준으로 오른쪽 회전해줍니다
			newNode = newNode->right;			 //newNode 를 newNode->right로 설정해주고
			InspectNode(&root, newNode);		 //newNode를 기준으로 다시 RBT를 깨나 검사해줍니다
		}

		else if ((newNode == newNode->parent->right) && ((other2 != NIL) && (other2->color == 0))) //새로운 노드가 부모의 오른쪽 자식이고 other2가 NIL이 아니고 검정색이면
		{
			//printf("8");
			newNode->parent->color = 0;		//새로운 노드의 부모의 색을 검정으로 해주고
			grandparent->color = 1;			//할아버지의 색을 빨강으로 해주고
			LeftRotate(&root, grandparent); //할아버지를 기준으로 왼쪽회전 해줍니다
		}

		else if ((newNode == newNode->parent->left) && ((other2 != NIL) && (other2->color == 0))) // 새로운 노드가 부모의 왼쪽 자식이고 other2가 NIL이 아니고 검정색이면
		{
			//printf("9");
			RightRotate(&root, newNode->parent); //새로운 노드의 부모를 기준으로 오른쪽 회전해주고
			newNode = newNode->right;			 //newNode를 newNode->right로 바꿔줍니다
			InspectNode(&root, newNode);		 //바뀐 newNode를 기준으로 RBT 규칙을 깨나 다시 검사해줍니다
		}
		else if ((other2->color == 1) && (newNode->parent == grandparent->right)) //other2의 color가 red 이고 새로운 노드의 부모가 할아버지의 오른쪽 자식이라면
		{
			//printf("10");
			newNode->parent->color = 0;		 //새로운 노드의 부모의 색을 검정으로 바꿉니다
			other2->color = 0;				 //other2의 색을 검정으로 바꿉니다
			grandparent->color = 1;			 //grandparent의 색을 빨강으로 바꿉니다
			InspectNode(&root, grandparent); //grandparent를 기준으로 RBT를 깨나 다시 검사해줍니다
		}
	}
}

void RightRotate(Node **rootNode, Node *newNode) // RightRotate 함수
{
	//여기서 newNode는 회전 중심의 노드입니다 (회전후 위로 올라갈 노드)

	Node *root = (*rootNode);		 //root = rootNode
	Node *childnode = newNode->left; //회전 중심의 노드의 왼쪽 자식을 childnode로 해줍니다
	Node *pparent = newNode->parent; //회전 중심의 노드의 parent를 pparent로 해줍니다

	if ((childnode->right != NULL) && (childnode != NIL)) //만약 삽입된 노드의 왼쪽자식의 오른쪽 자식에 값이 있고 삽입된 노드의 왼쪽 자식이 NIL이 아니라면
	{
		childnode->right->parent = newNode; //왼쪽 자식의 오른쪽 자식의 부모를 새로운 노드로 해줍니다
	}

	newNode->left = childnode->right; //회전 중심의 노드의 왼쪽에 자식의 오른쪽 노드를 이어주고
	newNode->parent = childnode;	  //회전 중심 노드의 부모가 자식노드가 되고
	childnode->right = newNode;		  //자식의 오른쪽 노드가 회전 중심노드를 가리키고
	childnode->parent = pparent;	  //자식의 부모가 회전중심노드의 부모를 가르킵니다

	if (pparent == NULL) //만약 회전중심노드의 부모가 NULL일 경우 즉 회전노드가 root였던경우
	{
		*rootNode = childnode; //childnode를 rootNode로 해줍니다
	}
	else if (newNode == pparent->left) //만약 회전 중심노드가 부모의 왼쪽 자식이었을 경우
	{
		pparent->left = childnode; //부모의 왼쪽 자식이 회전중심노드의 자식을 가리키게 합니다
	}
	else //만약 회전 중심노드가 부모의 오른쪽 자식이었을 경우
	{
		pparent->right = childnode; //부모의 오른쪽 자식이 회전중심노드의 자식을 가리키게 합니다
	}
}

void LeftRotate(Node **rootNode, Node *newNode) //LeftRotate 함수
{
	//여기서 newNode는 회전 중심의 노드입니다 (회전후 위로 올라갈 노드)

	Node *root = (*rootNode);		  //root = rootNode
	Node *childnode = newNode->right; //삽입된 노드의 오른쪽 자식을 childnode로 해줍니다
	Node *pparent = newNode->parent;  //삽입된 노드의 parent를 pparent로 해줍니다

	if ((childnode->left != NULL) && (childnode != NIL)) //만약 삽입된 노드의 왼쪽자식의 왼쪽 자식에 값이 있고 삽입된 노드의 왼쪽 자식이 NIL이 아니라면
	{
		childnode->left->parent = newNode; //왼쪽 자식의 왼쪽 자식의 부모를 새로운 노드로 해줍니다
	}

	newNode->right = childnode->left; //회전 중심의 노드의 오쪽에 자식의 왼쪽 노드를 이어주고
	newNode->parent = childnode;	  //회전 중심 노드의 부모가 자식노드가 되고
	childnode->left = newNode;		  //자식의 왼쪽 노드가 회전 중심노드를 가리키고
	childnode->parent = pparent;	  //자식의 부모가 회전중심노드의 부모를 가르킵니다

	if (pparent == NULL) //만약 회전중심노드의 부모가 NULL일 경우 즉 회전노드가 root였던경우
	{
		*rootNode = childnode; //childnode를 rootNode로 해줍니다
	}
	else if (newNode == pparent->left) //만약 회전 중심노드가 부모의 왼쪽 자식이었을 경우
	{
		pparent->left = childnode; //부모의 왼쪽 자식이 회전중심노드의 자식을 가리키게 합니다
	}
	else //만약 회전 중심노드가 부모의 오른쪽 자식이었을 경우
	{
		pparent->right = childnode; //부모의 오른쪽 자식이 회전중심노드의 자식을 가리키게 합니다
	}
}
