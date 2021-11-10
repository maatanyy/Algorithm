//2018038076 ����Ʈ�����а� 2�г� ��μ�
// Ʈ���� ����� ���� �˰��� ����
// binary search tree�� �����Ͽ��� search ����� iterative ����� ����Ͽ����ϴ�

#include <stdio.h>
#include <stdlib.h> //�����Ҵ�, malloc ����ϱ� ���� �߰�
#include <time.h>	//�ð������ϱ� ���� �߰�

typedef struct node //Node ����ü ����
{
	int key; //Ű ���� ������ left, right�� ����
	struct node *left;
	struct node *right;
} Node;

int searchIterative(Node *head, int key); //Ű�� Ʈ���� �ֳ� �������ִ� �Լ� ����

/*void preorderTraversal(Node *ptr) //������ȸ�Լ��� ���� Ʈ�� �۵����� Ȯ�����ִ� �Լ�
{
	if (ptr) //���� ptr�� �ִٸ� �� Node�� �ִٸ�
	{
		printf("[%d]   ", ptr->key);   //����� Ű�����
		preorderTraversal(ptr->left);  //Node�� left�� �ٽ� ����� ȣ��
		preorderTraversal(ptr->right); //Node�� right�� �ٽ� ����� ȣ��
	}
}*/

int main(void)
{
	int searchNum; //ã�� ���� ����

	Node *rootNode = (Node *)malloc(sizeof(Node)); //�����Ҵ����� rootNode ������ְ� Ű�� -10 (�����ʱⰪ���� ����, Ű���� �� ����̹Ƿ� �����ϱ�����)
	rootNode->key = -10;						   //ó�� Ű�� -10���� ����
	rootNode->right = NULL;						   //rootNode�� right NULL, left NULL�� ����
	rootNode->left = NULL;

	FILE *pFile = fopen("test.txt", "r"); //read mode
	int intTemp = -1;

	if (pFile == NULL) //������ ���� ��� ������ �������� �ʴ� �ٰ� �������
	{
		printf("File does not exist");
		return 0;
	}

	// ���� �б� ����
	while (1)
	{
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) //���� ������ ������ �ݺ��� Ż��, �ؽ�Ʈ���� �������� ���� -1�� �������� -1�� ������ ����
			break;

		// binary_search Ʈ������
		Node *tempNode = rootNode;					  //tempNode�� rootNode�� ����Ŵ
		Node *tempNode2 = rootNode;					  //tempNode2�� rootNode�� ����Ŵ
		Node *newNode = (Node *)malloc(sizeof(Node)); //newNode �����Ҵ����ְ� Ű ������ ������ �ʱ�ȭ �ϰ� right left�� NULL�� ����
		newNode->key = intTemp;						  //newNode�� key �� ���Ͽ��� ���� ��
		newNode->right = NULL;						  //newNode�� right, left NULL�� ��������
		newNode->left = NULL;

		if (rootNode->key == -10) // ��Ʈ��尡 ���� ��� �� ó���� ���
		{
			rootNode = newNode; // ó�� ������ �� ��Ʈ�� �������� �� test.txt�� ��� 526
		}

		else //��Ʈ��尡 �ִ� ���
		{
			while (tempNode != NULL) // tempNode�� NULL�� �ƴϸ� �������
			{
				tempNode2 = tempNode;			  //tempNode2 �� tempNode�� ����Ŵ (ó���� �Ѵ� ��Ʈ��带 ����Ű���� while���� �ݺ��ϸ� ���̹ٲ�)
				if (tempNode->key > newNode->key) //tempNode->key �� newNode�� key���� Ŭ���
				{
					tempNode = tempNode->left; //tempNode�� tempNode->left�� �ȴ�
				}

				else if (tempNode->key < newNode->key) //tempNode�� Ű�� newNode�� Ű���� �������
				{
					tempNode = tempNode->right; //tempNode�� tempNode->right�� �ȴ�
				}
			}

			//�ݺ����� Ż���Ͽ��� ��� �� tempNode�� ��������ϰ��
			if (tempNode2->key > newNode->key) //���� tempNode2�� key�� newNode�� key���� Ŭ ���
			{
				tempNode2->left = newNode; //tempNode2->left�� newNode�� �־��ش�
			}
			else if (tempNode2->key < newNode->key) //tempNode2�� Ű�� newNode�� Ű���� ���� ���
			{
				tempNode2->right = newNode; //tempNode2�� right�� newNode�� �־��ش�
			}
		}
		// Ű�� ���
		printf("%d ", intTemp);
	}
	//preorderTraversal(rootNode); //Ʈ�� ���� �۵����� Ȯ�ο� ������ȸ �Լ�
	//���� ���·� ��ȯ
	printf("\n");
	printf("�˻��� ���ϴ� Ű�� �Է����ּ���: "); // search ���ϴ� Ű �Է¹���
	scanf("%d", &searchNum);					 //searchNum �Է� ����
	searchIterative(rootNode, searchNum);		 //searchIterative �Լ��� Ʈ���� �ֳ� Ȯ��

	fclose(pFile); //close file
	return 0;
}

int searchIterative(Node *head, int key) // iterative ������� ��带 ã�� �Լ�
{
	Node *search = head; //Node ������ search �� head->left�� ���� Ŵ(root)

	while (search != NULL)
	{								//search �� NULL�ϋ����� �ݺ�
		if (key < search->key)		//���� key < search->key�̸�
			search = search->left;	//search�� search->left�� ��
		else if (key > search->key) //���� key > search->key�̸�
			search = search->right; //search�� search->right�� ��
		else if (key == search->key)
		{												//key�� search->key�� ������
			printf("ã���ô� Ű�� Ʈ���� �ֽ��ϴ�.\n"); //�ִٰ� �����ְ� ����
			return 0;
		}
	}
	//�� ���Ҵµ� ���ٸ� ���ٰ� �����ְ� ����
	printf("ã���ô� Ű�� Ʈ���� �����ϴ�.\n");
	return 1;
}
