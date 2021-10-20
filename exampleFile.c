#include <stdio.h>
#include <stdlib.h> //�����Ҵ�, malloc ����ϱ� ���� �߰�
#include <time.h>

#define RED 1;	 //RED 1���� ����
#define BLACK 0; //BLACk 0���� ����

typedef struct node  //
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
	rootNode->right = NIL;
	rootNode->left = NIL;
	rootNode->color = BLACK;

	NIL = (Node *)malloc(sizeof(Node)); //NIL �����Ҵ����ְ� color BLACK���� ����, RBT�� ������ �������
	NIL->color = BLACK;

	FILE *pFile = fopen("test2.txt", "r"); //read mode
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
		newNode->right = NIL;
		newNode->left = NIL;

		if (rootNode->key == -10) // ��Ʈ��尡 ���� ��� �� ó���� ���
		{
			rootNode = newNode; // ó�� ������ �� ��Ʈ�� �������� �� test.txt�� ��� 526
			rootNode->key = newNode->key;
			//printf("--");
		}

		else if (rootNode->key != -10) // ��Ʈ��尡 �ִ� ���
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

	if (root->color == 1)
	{
		root->color = 0;
	}

	//���Ե� ����� �θ� BLACK �� ���� ������ ���� �����Ƿ� ���Ե� ����� �θ� RED�� ��츸 ������ݴϴ�

	//printf("Insepct");

	if (newNode->parent->color == 1) //���Ե� ����� �θ� RED ����� ��� ������ �߻��Ѵ�
	{
		Node *other = newNode->parent->parent->right; //�θ��� �θ��� ������ �ڽ��� other�� ���ݴϴ�
		Node *other2 = newNode->parent->parent->left; //�θ��� �θ��� ���� �ڽ��� other2�� ���ݴϴ�

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
		//other�� �Ҿƹ��� ���� �����ʿ� �ְ� ���ο� ��尡 �θ��� ���� �ڽ��� ���, �����ڷ� Case 2-1
		{
			newNode->parent->color = 0;
			grandparent->color = 1;
			RightRotate(&root, grandparent);
		}

		else if ((newNode = newNode->parent->right) && ((other != NIL) && (other->color == 0)))
		//other�� �Ҿƹ��� ���� �����ʿ� �ְ� ���ο� ��尡 �θ��� ������ �ڽ��� ��� �����ڷ� Case 2-2
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
		// other2 �� ������ ������ ���

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
		else if ((other2->color == 1) && (newNode->parent == grandparent->right)) //other2�� color�� red
		{
			newNode->parent->color = 0;
			other2->color = 0;
			grandparent->color = 1;
			InspectNode(&root, grandparent);
		}
	}
}

void RightRotate(Node **rootNode, Node *newNode) // RightRotate �Լ�
{
	Node *root = (*rootNode);
	Node *childnode = newNode->left; //���Ե� ����� ���� �ڽ��� childnode�� ���ݴϴ�
	Node *pparent = newNode->parent; //���Ե� ����� parent�� pparent�� ���ݴϴ�

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

void LeftRotate(Node **rootNode, Node *newNode) //LeftRotate �Լ�
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
