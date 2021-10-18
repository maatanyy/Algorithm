#include <stdio.h>
#include <stdlib.h> //�����Ҵ�, malloc ����ϱ� ���� �߰�
#include <time.h>

#define RED 1;	 //RED 1���� ����
#define BLACK 0; //BLACk 0���� ����

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
	struct node *parent;
	int color;
} Node;

static Node *NIL; //Red Black Tree�� �������� �������� NIL�̶�� �Ϲ����� �������� �ٸ� ������带 ����Ű�µ� �̶� ����ϱ����� ����

void InsertNode(Node **, Node *);
void InspectNode(Node **, Node *);
void LeftRotate(Node **, Node *);
void RightRotate(Node **, Node *);

int main(void)
{
	Node *rootNode = (Node *)malloc(sizeof(Node)); //��Ʈ��� �����Ҵ� ���ְ� Ű �� ���� �� ��ũ , �� ����
	rootNode->key = -10;
	rootNode->right = NULL;
	rootNode->left = NULL;
	rootNode->color = BLACK;

	NIL = (Node *)malloc(sizeof(Node)); //NIL �����Ҵ����ְ� color BLACK���� ����, RBT�� ������ �������
	NIL->color = BLACK;

	FILE *pFile = fopen("test.txt", "r"); //read mode
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}

	// ���� �б� ����
	while (1)
	{
		Node *root = rootNode;

		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0)
			break;

		// Ʈ������
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->key = intTemp;
		newNode->right = NULL;
		newNode->left = NULL;

		if (rootNode->key == -10) // ��Ʈ��尡 ���� ��� �� ó���� ���
		{
			rootNode = newNode; // ó�� ������ �� ��Ʈ�� �������� �� test.txt�� ��� 526
		}

		else //��Ʈ��尡 �ִ� ���
		{
			InsertNode(&root, newNode); //����Ʈ�� ó�� ����� ��ġ�� ã�� ����
			newNode->color = RED;		//������ ����� ���� RED�� ���ݴϴ�
			newNode->left = NIL;		//����� left, right�� NIL�� �������ݴϴ�
			newNode->right = NIL;
			InspectNode(&root, newNode); //RED_BLACK_TREE�� ���� �˻����ݴϴ�
		}
		// ������ Ʈ������ Ű �˻�
		printf("%d ", intTemp);
	}

	//���� ���·� ��ȯ

	fclose(pFile); //close file
	return 0;
}

void InsertNode(Node **rootNode, Node *newNode) //��带 �����ϴ� �Լ�
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

void InspectNode(Node **rootNode, Node *newNode) //��带 �˻��ϴ� �Լ�
{
	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //���Ե� ����� �θ��� �θ� grandparent�� �������ݴϴ�
	//���Ե� ����� �θ� BLACK �� ���� ������ ���� �����Ƿ� ���Ե� ����� �θ� RED�� ��츸 ������ݴϴ�

	if (newNode->parent->color == 1) //���Ե� ����� �θ� RED ����� ��� ������ �߻��Ѵ�
	{

		Node *other = newNode->parent->parent->right; //�θ��� �θ��� ������ �ڽ��� other�� ���ݴϴ�
		Node *other2 = newNode->parent->parent->left; //�θ��� �θ��� ���� �ڽ��� other2�� ���ݴϴ�

		//Root ���� �������� newNode�� ������ ���
		//Case 1: other �� RED�� ���
		if (other->color == 1)				//���� �θ��� �θ��� ������ �ڽ� ���� RED �� ���
		{									//case1
			newNode->parent->color = BLACK; //���Ե� ����� �θ� BLACK���� �ٲ��ݴϴ�
			other->color = BLACK;
			InspectNode(&root, newNode->parent->parent); // ���� �ö󰡸� ������ ���� �� ��������� �ٽ� ����
		}

		if ()

			//Case 2-1
			else if ((newNode->parent->right == newNode) && (other->color == 0))
			{ //���θ� �ٸ� �ڽ��� �����̰� ���Գ�尡 �θ����� ������ �ڽ��ΰ��
				LeftRotate(&root, newNode);
			}

		//Case 2-2
		else if ((newNode->parent->left == newNode) && (other->color == 0))
		{ //���θ� �ٸ� �ڽ��� �����̰� ���Գ�尡 �θ����� ���� �ڽ��ΰ��
			RightRotate(&root, newNode);
		}

		//Root ���� ���������� newNode�� ������ ���
		//Case 1: other2 �� RED�� ���
		if (other2->color == 1)				//���� �θ��� �θ��� ������ �ڽ� ���� RED �� ���
		{									//case1
			newNode->parent->color = BLACK; //���Ե� ����� �θ� BLACK���� �ٲ��ݴϴ�
			other2->color = BLACK;
			InspectNode(&root, newNode->parent->parent); // ���� �ö󰡸� ������ ���� �� ��������� �ٽ� ����
		}

		//Case 2-1
		else if ((newNode->parent->right == newNode) && (other2->color == 0))
		{ //���θ� �ٸ� �ڽ��� �����̰� ���Գ�尡 �θ����� ������ �ڽ��ΰ��
			RightRotate(&root, newNode);
		}

		//Case 2-2
		else if ((newNode->parent->left == newNode) && (other2->color == 0))
		{ //���θ� �ٸ� �ڽ��� �����̰� ���Գ�尡 �θ����� ���� �ڽ��ΰ��
			LeftRotate(&root, newNode);
		}
	}
}

void LeftRotate(Node **rootNode, Node *newNode) //LeftRotate �Լ�
{
	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //���Ե� ����� �θ��� �θ� grandparent�� �������ݴϴ�
	Node *parent = newNode->parent;
	parent->right = newNode->left;
	grandparent->left = newNode;
	newNode->left = parent;
	root = grandparent;
	InspectNode(&root, newNode->left);
	printf("��");
}

void RightRotate(Node **rootNode, Node *newNode) //RightRotate �Լ�
{
	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //���Ե� ����� �θ��� �θ� grandparent�� �������ݴϴ�
	Node *parent = newNode->parent;
	grandparent->left = parent->right;
	parent->right = grandparent;
	grandparent = parent;
	root = grandparent;
	grandparent->color = BLACK;
	parent->color = BLACK;
	printf("��");
}