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
		}

		else if (rootNode->key != -10) // ��Ʈ��尡 �ִ� ���
		{
			InsertNode(&root, newNode); //����Ʈ�� ó�� ����� ��ġ�� ã�� ����
			newNode->color = RED;		//������ ����� ���� RED�� ���ݴϴ�
			newNode->left = NIL;		//����� left, right�� NIL�� �������ݴϴ�
			newNode->right = NIL;
			InspectNode(&root, newNode); //RED_BLACK_TREE�� ���� �˻����ݴϴ�
										 //printf("--");
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

		if (grandparent->right == NIL)
		{
			//printf("1");
			RightRotate(&root, newNode);
			newNode->parent->color = BLACK;
			newNode->parent->right->color = RED;
		}

		else if ((newNode = newNode->parent->left) && ((other != NIL) && (other->color == 0))) // Case 2-2
		{
			//printf("2");
			RightRotate(&root, newNode);
			newNode->parent->color = BLACK;
			newNode->parent->left->color = RED;
		}

		else if ((newNode = newNode->parent->right) && ((other != NIL) && (other->color == 0))) //Case 2-1
		{
			//printf("3");
			LeftRotate(&root, newNode);
			InspectNode(&root, newNode->left);
		}

		else if (other->color == 1)
		{
			//printf("4");
			newNode->parent->color = 0;
			other->color = 0;
			grandparent->color = 1;
			InspectNode(&root, grandparent);
		}

		//printf("5");
		// other2 �� ������ ������ ���
		else if (grandparent->left == NIL)
		{
			LeftRotate(&root, newNode);
			newNode->parent->color = BLACK;
			newNode->parent->left->color = RED;
		}

		else if ((newNode = newNode->parent->left) && ((other2 != NIL) && (other2->color == 0))) // Case 2-2
		{

			//���� ���ľ���
			RightRotate(&root, newNode);
			//newNode->color = BLACK;
			//newNode->parent->parent->color = RED;
			InspectNode(&root, grandparent->right);
		}

		else if ((newNode = newNode->parent->right) && ((other2 != NIL) && (other2->color == 0))) //Case 2-1
		{
			LeftRotate(&root, newNode);
			InspectNode(&root, newNode->left);
		}

		else if (other2->color == 1) //other2�� color�� red
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
	Node *grandparent = newNode->parent->parent; //���Ե� ����� �θ��� �θ� grandparent�� �������ݴϴ�
	Node *parent = newNode->parent;				 //���Ե� ����� �θ� parent�� �������ݴϴ�

	if (parent->right != NULL) //���� �θ��� right�� ��尡 �ִٸ�
	{
		parent->right->parent = grandparent; //�θ��� right�� �θ� grandparent�� ����Ű�� �մϴ�
	}

	grandparent->left = parent->right;	  //grandparent�� left�� parent�� right�� ����Ű�� �մϴ�
	grandparent->parent = parent;		  //grandparent�� �θ� parent�� ����Ű�� �մϴ�
	parent->right = grandparent;		  //parent�� right�� grandparent�� ����Ű�� �մϴ�
	parent->parent = grandparent->parent; //parent�� parent�� grandparent�� parent�� ����Ű�� �մϴ�

	if (grandparent->parent == NULL) //���� grandparent�� parent�� NULL�� ��� �� �����ϰ��
	{
		*rootNode = parent; //rootNode�� parent�� �������ݴϴ�
	}
	else if (grandparent == grandparent->parent->left) //���� grandparent�� �� ���� ��� ���� ���ʿ� ��ġ�ϰ� �־��ٸ�
	{
		grandparent->parent->left = parent; //grandparent�� left�� parent�� ����Ű�� �մϴ�
	}
	else //���� grandparent�� �� ���� ��� ���� �����ʿ� ��ġ�ϰ� �־��ٸ�
	{
		grandparent->parent->right = parent; //grandparent�� right�� parent�� ����Ű�� �մϴ�
	}
}

void LeftRotate(Node **rootNode, Node *newNode) //LeftRotate �Լ�
{
	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //���Ե� ����� �θ��� �θ� grandparent�� �������ݴϴ�
	Node *parent = newNode->parent;

	if (parent->left != NULL)
	{
		parent->left->parent = grandparent;
	}

	grandparent->right = parent->left;
	grandparent->parent = parent;
	parent->left = grandparent;
	parent->parent = grandparent->parent;

	if (grandparent->parent == NULL)
	{
		*rootNode = parent;
	}
	else if (grandparent == grandparent->parent->left)
	{
		grandparent->parent->left = parent;
	}
	else
	{
		grandparent->parent->right = parent;
	}
}
