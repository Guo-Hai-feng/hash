#include"hash.h"
//����key������������λHashͰ��λ��,Hashָ���ǹ�ϣͰ���±�
int HashNode(int key, int TableSize)
{
	return (key % TableSize);
}
HashTable* InitHashNode(int TableSize)
{
	int i = 0;
	HashTable* hTable = NULL;
	if (TableSize <= 0)
	{
		//�����ϣ��Ĵ�СΪ�㣬Ĭ�Ͽ���16
		TableSize = DEFAULT_SIZE;
	}

	//������ϣ��ṹ���ָ��
	hTable = (HashTable*)malloc(sizeof(HashTable));
	if (hTable == NULL)
	{
		printf("HsahTable malloc error.\n");
		return NULL;
	}

	//��ϣ��Ĵ�С
	hTable->TableSize = TableSize;


	//ΪHashtͰ����ռ䣬��Ϊһ��ָ������
	hTable->TheLists = (List*)malloc(sizeof(List) * TableSize);
	if (hTable->TheLists == NULL)
	{
		printf("HashTable malloc error.\n");
		free(hTable);
		return NULL;
	}

	//Ϊ��ϣͰ��Ӧ��ָ�������ʼ������ڵ�
	for (int i = 0; i < TableSize; i++)
	{
		hTable->TheLists[i] = (List)malloc(sizeof(ListNode));
		if (hTable->TheLists[i] == NULL)
		{
			printf("HashTable malloc error.\n");
			free(hTable->TheLists);
			free(hTable);
			return NULL;
		}
		else
		{
			memset(hTable->TheLists[i], 0, sizeof(ListNode));
		}
	}
	return hTable;
}

Element FindNode(HashTable* HashTable, int key)
{
	int i = 0;
	List L = NULL;
	Element e = NULL;

	//��ϣͰ���±�λ��
	i = HashNode(key, HashTable->TableSize);

	//�ҵ���Ӧ�Ĺ�ϣͰ
	L = HashTable->TheLists[i];

	//������ϣͰ
	e = L->next;
	while (e != NULL && e->key != key)
	{
		e = e->next;
	}
	return e;
}

//�ӹ�ϣ���в�������
void InsertNode(HashTable* HashTable, int key, void* value)
{
	Element e = NULL, tmp = NULL;

	//��ʱ�ڵ�
	List L = NULL;

	e = FindNode(HashTable, key);

	if (e == NULL)
	{
		tmp = (Element)malloc(sizeof(ListNode));
		if (tmp == NULL)
		{
			printf("malloc error.\n");
			return;
		}
		L = HashTable->TheLists[HashNode(key, HashTable->TableSize)];
		tmp->data = value;
		tmp->key = key;

		//ͷ�巨
		tmp->next = L->next;
		L->next = tmp;
	}
	else
	{
		printf("the key already exits\n");

	}
}

//��ϣ��ɾ��Ԫ��
void DestoryNode(HashTable* HashTable)
{
	int i = 0;
	List L = NULL;
	Element cur = NULL, next = NULL;
	for (int i = 0; i < HashTable->TableSize; i++)
	{
		L = HashTable->TheLists[i];
		cur = L->next;
		while (cur && cur->next != NULL)
		{
			next = cur->next;
			free(cur);
			cur = next;
		}
		free(L);
	}
	free(HashTable->TheLists);
	free(HashTable);
}


void DeleteNode(HashTable* HashTable, int key)
{
	Element e = NULL, Last = NULL;
	List L = NULL;
	int i = HashNode(key, HashTable->TableSize);
	L = HashTable->TheLists[i];
	Last = L;
	e = L->next;
	while (e != NULL && e->key != key)
	{
		Last = e;
		e = e->next;
	}
	if (e)//�����ֵ�Դ���
	{
		Last->next = e->next;
		free(e);
	}
}

//��ϣ������ȡԪ��
void* RetrieveNode(Element e)
{
	//����ڵ���ڵĻ��ͷ��ؽڵ������
	return e ? e->data : NULL;
}
