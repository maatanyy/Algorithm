#include <stdio.h>
#include <stdlib.h> //�����Ҵ�, malloc ����ϱ� ���� �߰�
#include <time.h>

// �ؾ��� ��
// Ʈ�� ��� ���� ����
// 1. choose binary or AVL
// 2. Ʈ�� �̿��Ͽ� ���ı���,
// 3. �˻� + ���� ����

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

void preorderTraversal(Node *ptr) //������ȸ�Լ��� ���� �� �ֳ� Ȯ��
{
	if (ptr) //���� ptr�� �ִٸ� �� Node�� �ִٸ�
	{
		printf("[%d]   ", ptr->key);   //����� Ű�����
		preorderTraversal(ptr->left);  //Node�� left�� �ٽ� ����� ȣ��
		preorderTraversal(ptr->right); //Node�� right�� �ٽ� ����� ȣ��
	}
}

int main(void)
{
	int searchNum;
	Node *rootNode = (Node *)malloc(sizeof(Node)); //�����Ҵ����� rootNode ������ְ� Ű�� -10 (�����ʱⰪ���� ����, Ű���� �� ����̹Ƿ� �����ϱ�����)
	rootNode->key = -10;
	rootNode->right = NULL;
	rootNode->left = NULL;

	clock_t timecheck; //timecheck��

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
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0)
			break;

		// binary_search Ʈ������
		Node *tempNode = rootNode;
		Node *tempNode2 = rootNode;
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
			while (tempNode != NULL) //������尡 �ƴϸ� �������
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
		// ������ Ʈ������ Ű �˻�
		//printf("%d ", intTemp);
	}

	//preorderTraversal(rootNode);  //Ʈ�� ���� �۵����� Ȯ�ο� ������ȸ �Լ�
	//���� ���·� ��ȯ
	printf("\n");
	printf("�˻��� ���ϴ� Ű�� �Է����ּ���: ");
	scanf("%d", &searchNum);

	fclose(pFile); //close file
	return 0;
}