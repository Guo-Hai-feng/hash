#include"hash.h"
//根据key计算索引，定位Hash桶的位置,Hash指的是哈希桶的下标
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
		//如果哈希表的大小为零，默认开辟16
		TableSize = DEFAULT_SIZE;
	}

	//创建哈希表结构体的指针
	hTable = (HashTable*)malloc(sizeof(HashTable));
	if (hTable == NULL)
	{
		printf("HsahTable malloc error.\n");
		return NULL;
	}

	//哈希表的大小
	hTable->TableSize = TableSize;


	//为Hasht桶分配空间，其为一个指针数组
	hTable->TheLists = (List*)malloc(sizeof(List) * TableSize);
	if (hTable->TheLists == NULL)
	{
		printf("HashTable malloc error.\n");
		free(hTable);
		return NULL;
	}

	//为哈希桶对应的指针数组初始化链表节点
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

	//哈希桶的下标位置
	i = HashNode(key, HashTable->TableSize);

	//找到对应的哈希桶
	L = HashTable->TheLists[i];

	//遍历哈希桶
	e = L->next;
	while (e != NULL && e->key != key)
	{
		e = e->next;
	}
	return e;
}

//从哈希表中插入数据
void InsertNode(HashTable* HashTable, int key, void* value)
{
	Element e = NULL, tmp = NULL;

	//临时节点
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

		//头插法
		tmp->next = L->next;
		L->next = tmp;
	}
	else
	{
		printf("the key already exits\n");

	}
}

//哈希表删除元素
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
	if (e)//如果键值对存在
	{
		Last->next = e->next;
		free(e);
	}
}

//哈希表中提取元素
void* RetrieveNode(Element e)
{
	//如果节点存在的话就返回节点的数据
	return e ? e->data : NULL;
}
