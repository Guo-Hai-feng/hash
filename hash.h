#define _CRT_SECURE_NO_WARNINGS
#define DEFAULT_SIZE 16
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct _ListNode
{
	struct _ListNode* next;
	int key;
	void* data;
}ListNode;

typedef ListNode* List;
typedef ListNode* Element;

typedef struct _HashTable
{
	int TableSize;
	List* TheLists; //List* TheLists ���� TheLists Ϊָ�� List ��ָ�룬��ζ��������ָ��һ���������顣
}HashTable;

int HashNode(int key, int TableSize);
HashTable* InitHashNode(int TableSize);
Element FindNode(HashTable* HashTable, int key);
void InsertNode(HashTable* HashTable, int key, void* value);
void DestoryNode(HashTable* HashTable);
void DeleteNode(HashTable* HashTable, int key);

//ע������ת��
void* RetrieveNode(Element e);



//��ϣ���˳��洢
//��ά����
#define MAXSIZE 3

typedef struct
{
	int key;
	void* data;
}POINT;

typedef struct
{
	POINT arr[MAXSIZE];//����̬��չ�ڴ�
}HashBucket, * Bucket;//��ϣͰ

typedef struct _HashArrTable
{
	int TableSize;
	Bucket* list;
}HashArrTable;


int HashArr(int key, int TableSize);
HashArrTable* InitArr(int TableSize);
int FindArr(HashArrTable* hash, int key);
void InsertArr(HashArrTable* hash, int key, void* data);
void DestoryArr(HashArrTable* hash);

void DeleteArr(HashArrTable* hash, int key);

