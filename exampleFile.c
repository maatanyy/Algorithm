#include <stdio.h>
#include <stdlib.h> //�����Ҵ�, malloc ����ϱ� ���� �߰�
#include <time.h>

#define RED 1;	 //RED 1���� ����
#define BLACK 0; //BLACk 0���� ����

typedef struct node //Node ����ü ����
{
	int key;			 //int�� key
	struct node *left;	 //node ������ left (�����ڽ�)
	struct node *right;	 //node ������ right (�������ڽ�)
	struct node *parent; //node ������ parent (�θ�)
	int color;
} Node;

static Node *NIL; //Red Black Tree�� �������� �������� NIL�̶�� �Ϲ����� �������� �ٸ� ������带 ����Ű�µ� �̶� ����ϱ����� ����

void InsertNode(Node **, Node *);  //��� �����ϴ� �Լ�
void InspectNode(Node **, Node *); //Ʈ�� �˻��ϴ� �Լ�
void LeftRotate(Node **, Node *);  //�������� ȸ���ϴ� �Լ�
void RightRotate(Node **, Node *); //���������� ȸ���ϴ� �Լ�

int main(void)
{
	Node *rootNode = (Node *)malloc(sizeof(Node)); //��Ʈ��� �����Ҵ� ���ְ� Ű �� ���� �� ��ũ , �� ����
	rootNode->key = -10;						   //��Ʈ��� �ʱ� Ű�� -10���� ���� (test������ ������� ����)
	rootNode->right = NIL;						   //��Ʈ�� ���� ������ �ڽ� NIL�� ����
	rootNode->left = NIL;
	rootNode->color = BLACK; //��Ʈ����� ���� BLACK���� ����

	NIL = (Node *)malloc(sizeof(Node)); //NIL �����Ҵ����ְ� color BLACK���� ����, RBT�� ������ �������
	NIL->color = BLACK;

	FILE *pFile = fopen("test2.txt", "r"); //read mode
	int intTemp = -1;

	if (pFile == NULL) //���Ͽ�������
	{
		printf("File does not exist"); //���
		return 0;
	}

	// ���� �б� ����
	while (1)
	{
		Node *root = rootNode; //root  = rootNode����Ŵ

		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) //���� ������ ������ ���� txt���� �������� -1�̶� -1�� �����
			break;

		// Ʈ������
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->key = intTemp;
		newNode->right = NIL;
		newNode->left = NIL;

		if (rootNode->key == -10) // ��Ʈ��尡 ���� ��� �� ó���� ���(������ �ʱ� ��ƮŰ�� -10���� �������־���)
		{
			rootNode = newNode;			  // ó�� ������ �� ��Ʈ�� �������� �� test.txt�� ��� 526
			rootNode->key = newNode->key; //rootNode�� key�� newNode�� Ű����
		}

		else if (rootNode->key != -10) // ��Ʈ��尡 �ִ� ��� (ó���� �����Ѱ��)
		{
			InsertNode(&root, newNode); //����Ʈ��ó�� ����� ��ġ�� ã�� ����
			newNode->color = RED;		//������ ����� ���� RED�� ���ݴϴ�
			newNode->left = NIL;		//����� left, right�� NIL�� �������ݴϴ�
			newNode->right = NIL;
			InspectNode(&root, newNode); //RED_BLACK_TREE�� ���� �˻����ݴϴ�
		}
		printf("%d ", intTemp); //Ű ���
								// ������ Ʈ������ Ű �˻�
	}

	//���� ���·� ��ȯ
	fclose(pFile); //close file
	return 0;
}

void InsertNode(Node **rootNode, Node *newNode) //��带 �����ϴ� �Լ�, �⺻������ ����Ʈ�� ���԰� �����ϴ�
{
	Node *root = (*rootNode); //root = rootNode

	if (root->key < newNode->key) //���� ���ε��� Ű�� ��Ʈ�� Ű���� Ŭ ���
	{
		if ((root->right == NULL) || (root->right == NIL)) //1. ��Ʈ�� right�� ����ְų� NIL�� ���
		{
			root->right = newNode;	//root�� ������ �ڽĿ� newNode�� ��������ְ�
			newNode->parent = root; //newNode�� �θ� root�� �������ݴϴ�
		}
		else //2. ���� right�� ������� ���� ��� (�� �̹� ���� �ִ� ���)
		{
			InsertNode(&(root->right), newNode); //root->right �� newNode�� InsertNode �Լ��� �ٽ� ȣ���մϴ�
		}
	}

	else if (root->key > newNode->key) //���� ���ε��� Ű�� ��Ʈ�� Ű���� ���� ���
	{
		if ((root->left == NULL) || (root->left == NIL)) //1. ��Ʈ�� left�� ����ְų� NIL�� ���
		{
			root->left = newNode;	//root�� ���� �ڽĿ� newNode�� ��������ְ�
			newNode->parent = root; //newNode�� �θ� root�� �������ݴϴ�
		}
		else //2. ���� left�� ������� ���� ��� (�� �̹� ���� �ִ� ���)
		{
			InsertNode(&(root->left), newNode); //root->left�� newNode�� InsertNode �Լ��� �ٽ� ȣ���մϴ�
		}
	}
}

void InspectNode(Node **rootNode, Node *newNode) //��带 �˻��ϴ� �Լ�
{

	Node *root = (*rootNode);
	Node *grandparent = newNode->parent->parent; //���Ե� ����� �θ��� �θ� grandparent�� �������ݴϴ�, ���ǻ� �Ҿƹ����� �θ��ڽ��ϴ�

	if (root->color == 1) //���� ��Ʈ ����� ���� �������̶��
	{
		root->color = 0; //��Ʈ ����� ���� ���������� �ٲ��ݴϴ� (��Ʈ�� ���� �׻� �������̰� �ٲ㵵 RBT�� ��Ģ�� ������ ����)
	}

	//���Ե� ����� �θ� BLACK �� ���� ������ ���� �����Ƿ� ���Ե� ����� �θ� RED�� ��츸 ������ݴϴ�
	//printf("Insepct");
	if (newNode->parent->color == 1) //���Ե� ����� �θ� RED ����� ��� ������ �߻��Ѵ�
	{
		Node *other = newNode->parent->parent->right; //�Ҿƹ����� ������ �ڽ��� other�� ���ݴϴ�
		Node *other2 = newNode->parent->parent->left; //�Ҿƹ����� ���� �ڽ��� other2�� ���ݴϴ�

		//�� 10���� Case�� �����Ͽ��� 1~5��°�� other, 6~10�� other2�� case�Դϴ�

		if ((grandparent->right == NIL) && (newNode == newNode->parent->left)) //���� other�� NIL�̰� ���ο� ��尡 �θ��� ���� �ڽ��̶��
		{
			//printf("1");
			newNode->parent->color = 0;		 //���ο� ����� �θ��� ���� �������� �ٲٰ�
			grandparent->color = 1;			 //�Ҿƹ��� ����� ���� ���������� �ٲߴϴ�
			RightRotate(&root, grandparent); //�Ҿƹ��� ��带 �������� ������ȸ�����ݴϴ�
		}

		else if ((grandparent->right == NIL) && (newNode == newNode->parent->right)) //���� other�� NIL �̰� ���ο� ��尡 �θ��� ������ �ڽ��̶��
		{
			//printf("2");
			LeftRotate(&root, newNode->parent); //���ο� ����� �θ� �������� ����ȸ�����ְ�
			newNode = newNode->left;			//newNode�� newNode->left�� �������ݴϴ�
			InspectNode(&root, newNode);		//�׸��� �ٲ� newNode�� �ٽ� RBT�� ��Ģ�� ������ Ȯ�����ݴϴ�
		}

		else if ((newNode == newNode->parent->left) && ((other != NIL) && (other->color == 0)))
		//Other�� �������̰� ���� �ְ� ���ο� ��尡 �θ��� ���� �ڽ��� ���
		{
			//printf("3");
			newNode->parent->color = 0;		 //�θ��� ���� ���������� �ٲ��ְ�
			grandparent->color = 1;			 //�Ҿƹ����� ���� ���������� �ٲ��ݴϴ�
			RightRotate(&root, grandparent); //�Ҿƹ����� �������� ������ ȸ�����ݴϴ�
		}

		else if ((newNode = newNode->parent->right) && ((other != NIL) && (other->color == 0)))
		//Other�� �������̰� ���� �ְ� ���ο� ��尡 �θ��� ������ �ڽ��� ���
		{
			//printf("4");
			LeftRotate(&root, newNode->parent); //���ο� ����� �θ� �������� ����ȸ�����ְ�
			newNode = newNode->left;			//newNode->left�� newNode�� �������ݴϴ�
			InspectNode(&root, newNode);		//�ٲ� newNode�� RBT�� ��Ģ�� ���� �ٽ� Ȯ�����ݴϴ�
		}

		else if ((other->color == 1) && (newNode->parent == grandparent->left))
		//���� �Ҿƹ��� ������ �ڽ��� �������̰� ���ο� ����� �θ� �Ҿƹ����� �����ڽ��ϰ��
		{
			//printf("5");
			newNode->parent->color = 0;		 //���ο����� �θ��� ���� �������� ���ְ�
			other->color = 0;				 //other�� ���� �����������ְ�
			grandparent->color = 1;			 //�Ҿƹ����� ���� ���������� ���ݴϴ�
			InspectNode(&root, grandparent); //�Ҿƹ����� �������� RBT�� ���� �ٽ� Ȯ�����ݴϴ�
		}

		// other2 �� ������ ������ ���
		else if ((grandparent->left == NIL) && (newNode == newNode->parent->right)) //�Ҿƹ����� ������ NIL�̰� ���ο��尡 �θ��� ������ �ڽ��� ���
		{
			//printf("6");
			newNode->parent->color = 0;		//���ο� ����� �θ��� ���� �������� ���ݴϴ�
			grandparent->color = 1;			//�Ҿƹ����� ���� �������� ���ݴϴ�
			LeftRotate(&root, grandparent); //�Ҿƹ����� �������� ���� ȸ�����ݴϴ�
		}

		else if ((grandparent->left == NIL) && (newNode == newNode->parent->left)) //�Ҿƹ����� ������ NIL�̰� newNode�� newNode�� �θ��� ���� �ϰ��
		{
			//printf("7");
			RightRotate(&root, newNode->parent); //���ο� ����� �θ� �������� ������ ȸ�����ݴϴ�
			newNode = newNode->right;			 //newNode �� newNode->right�� �������ְ�
			InspectNode(&root, newNode);		 //newNode�� �������� �ٽ� RBT�� ���� �˻����ݴϴ�
		}

		else if ((newNode == newNode->parent->right) && ((other2 != NIL) && (other2->color == 0))) //���ο� ��尡 �θ��� ������ �ڽ��̰� other2�� NIL�� �ƴϰ� �������̸�
		{
			//printf("8");
			newNode->parent->color = 0;		//���ο� ����� �θ��� ���� �������� ���ְ�
			grandparent->color = 1;			//�Ҿƹ����� ���� �������� ���ְ�
			LeftRotate(&root, grandparent); //�Ҿƹ����� �������� ����ȸ�� ���ݴϴ�
		}

		else if ((newNode == newNode->parent->left) && ((other2 != NIL) && (other2->color == 0))) // ���ο� ��尡 �θ��� ���� �ڽ��̰� other2�� NIL�� �ƴϰ� �������̸�
		{
			//printf("9");
			RightRotate(&root, newNode->parent); //���ο� ����� �θ� �������� ������ ȸ�����ְ�
			newNode = newNode->right;			 //newNode�� newNode->right�� �ٲ��ݴϴ�
			InspectNode(&root, newNode);		 //�ٲ� newNode�� �������� RBT ��Ģ�� ���� �ٽ� �˻����ݴϴ�
		}
		else if ((other2->color == 1) && (newNode->parent == grandparent->right)) //other2�� color�� red �̰� ���ο� ����� �θ� �Ҿƹ����� ������ �ڽ��̶��
		{
			//printf("10");
			newNode->parent->color = 0;		 //���ο� ����� �θ��� ���� �������� �ٲߴϴ�
			other2->color = 0;				 //other2�� ���� �������� �ٲߴϴ�
			grandparent->color = 1;			 //grandparent�� ���� �������� �ٲߴϴ�
			InspectNode(&root, grandparent); //grandparent�� �������� RBT�� ���� �ٽ� �˻����ݴϴ�
		}
	}
}

void RightRotate(Node **rootNode, Node *newNode) // RightRotate �Լ�
{
	//���⼭ newNode�� ȸ�� �߽��� ����Դϴ� (ȸ���� ���� �ö� ���)

	Node *root = (*rootNode);		 //root = rootNode
	Node *childnode = newNode->left; //ȸ�� �߽��� ����� ���� �ڽ��� childnode�� ���ݴϴ�
	Node *pparent = newNode->parent; //ȸ�� �߽��� ����� parent�� pparent�� ���ݴϴ�

	if ((childnode->right != NULL) && (childnode != NIL)) //���� ���Ե� ����� �����ڽ��� ������ �ڽĿ� ���� �ְ� ���Ե� ����� ���� �ڽ��� NIL�� �ƴ϶��
	{
		childnode->right->parent = newNode; //���� �ڽ��� ������ �ڽ��� �θ� ���ο� ���� ���ݴϴ�
	}

	newNode->left = childnode->right; //ȸ�� �߽��� ����� ���ʿ� �ڽ��� ������ ��带 �̾��ְ�
	newNode->parent = childnode;	  //ȸ�� �߽� ����� �θ� �ڽĳ�尡 �ǰ�
	childnode->right = newNode;		  //�ڽ��� ������ ��尡 ȸ�� �߽ɳ�带 ����Ű��
	childnode->parent = pparent;	  //�ڽ��� �θ� ȸ���߽ɳ���� �θ� ����ŵ�ϴ�

	if (pparent == NULL) //���� ȸ���߽ɳ���� �θ� NULL�� ��� �� ȸ����尡 root�������
	{
		*rootNode = childnode; //childnode�� rootNode�� ���ݴϴ�
	}
	else if (newNode == pparent->left) //���� ȸ�� �߽ɳ�尡 �θ��� ���� �ڽ��̾��� ���
	{
		pparent->left = childnode; //�θ��� ���� �ڽ��� ȸ���߽ɳ���� �ڽ��� ����Ű�� �մϴ�
	}
	else //���� ȸ�� �߽ɳ�尡 �θ��� ������ �ڽ��̾��� ���
	{
		pparent->right = childnode; //�θ��� ������ �ڽ��� ȸ���߽ɳ���� �ڽ��� ����Ű�� �մϴ�
	}
}

void LeftRotate(Node **rootNode, Node *newNode) //LeftRotate �Լ�
{
	//���⼭ newNode�� ȸ�� �߽��� ����Դϴ� (ȸ���� ���� �ö� ���)

	Node *root = (*rootNode);		  //root = rootNode
	Node *childnode = newNode->right; //���Ե� ����� ������ �ڽ��� childnode�� ���ݴϴ�
	Node *pparent = newNode->parent;  //���Ե� ����� parent�� pparent�� ���ݴϴ�

	if ((childnode->left != NULL) && (childnode != NIL)) //���� ���Ե� ����� �����ڽ��� ���� �ڽĿ� ���� �ְ� ���Ե� ����� ���� �ڽ��� NIL�� �ƴ϶��
	{
		childnode->left->parent = newNode; //���� �ڽ��� ���� �ڽ��� �θ� ���ο� ���� ���ݴϴ�
	}

	newNode->right = childnode->left; //ȸ�� �߽��� ����� ���ʿ� �ڽ��� ���� ��带 �̾��ְ�
	newNode->parent = childnode;	  //ȸ�� �߽� ����� �θ� �ڽĳ�尡 �ǰ�
	childnode->left = newNode;		  //�ڽ��� ���� ��尡 ȸ�� �߽ɳ�带 ����Ű��
	childnode->parent = pparent;	  //�ڽ��� �θ� ȸ���߽ɳ���� �θ� ����ŵ�ϴ�

	if (pparent == NULL) //���� ȸ���߽ɳ���� �θ� NULL�� ��� �� ȸ����尡 root�������
	{
		*rootNode = childnode; //childnode�� rootNode�� ���ݴϴ�
	}
	else if (newNode == pparent->left) //���� ȸ�� �߽ɳ�尡 �θ��� ���� �ڽ��̾��� ���
	{
		pparent->left = childnode; //�θ��� ���� �ڽ��� ȸ���߽ɳ���� �ڽ��� ����Ű�� �մϴ�
	}
	else //���� ȸ�� �߽ɳ�尡 �θ��� ������ �ڽ��̾��� ���
	{
		pparent->right = childnode; //�θ��� ������ �ڽ��� ȸ���߽ɳ���� �ڽ��� ����Ű�� �մϴ�
	}
}
