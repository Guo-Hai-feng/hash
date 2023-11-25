#include"hash.h"

int HashArr(int key, int TableSize)
{
	return key % TableSize;
}

HashArrTable* InitArr(int TableSize)
{
	HashArrTable* hash = (HashArrTable*)malloc(sizeof(HashArrTable));
	if (hash == NULL)
	{
		printf("hash malloc error.\n");
		return NULL;
	}
	if (TableSize == 0)
	{
		TableSize = MAXSIZE;
	}
	hash->TableSize = TableSize;
	//给哈希表分配内存，同时数组已就绪
	hash->list = (Bucket*)malloc(hash->TableSize * sizeof(Bucket));
	for (int i = 0; i < hash->TableSize; i++)
	{
		hash->list[i] = (Bucket)malloc(sizeof(HashBucket));
	}

	//初始化
	for (int i = 0; i < hash->TableSize; i++)
	{
		for (int j = 0; j < MAXSIZE; j++)
		{
			hash->list[i]->arr[j].data = NULL;
			hash->list[i]->arr[j].key = 0;
		}
	}
	return hash;
}

int FindArr(HashArrTable* hash, int key)
{
	int i = HashArr(key, hash->TableSize);
	Bucket L;
	L = hash->list[i];
	i = 0;
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (L->arr[i].key == key)
		{
			//表示找到了
			return i;
		}
	}
	//表示没找到
	return -1;

}

void InsertArr(HashArrTable* hash, int key, void* data)
{
	int j = HashArr(key, hash->TableSize);
	Bucket L = hash->list[j];
	int e = FindArr(hash, key);
	if (e < 0)
	{
		for (int i = 0; i < MAXSIZE; i++)
		{
			if (L->arr[i].key == 0)
			{
				hash->list[j]->arr[i].data = data;
				hash->list[j]->arr[i].key = key;
				break;
			}
		}
	}
	else
	{
		printf("the key already exits\n");
	}
}

void DestoryArr(HashArrTable* hash)
{
	int i = 0;
	Bucket L = NULL;
	for (int i = 0; i < hash->TableSize; i++)
	{
		free(hash->list[i]);
	}
	free(hash->list);
	free(hash);
}

void DeleteArr(HashArrTable* hash, int key)
{
	int i = HashArr(key, hash->TableSize);
	Bucket L = hash->list[i];
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (L->arr[i].key == key)
		{
			L->arr[i].data = NULL;
			L->arr[i].key = 0;
		}
	}
}


//int main()
//{
//	char* elems[] = { "楚子航","李嘉图","谢怜" };
//	int i = 0;
//	HashArrTable*hash= NULL;
//	hash = InitArr(5);
//	InsertArr(hash, 1, elems[0]);
//	InsertArr(hash, 2, elems[1]);
//	InsertArr(hash, 3, elems[2]);
//	DeleteArr(hash, 2);
//	for (i = 1; i < 5; i++)
//	{
//		int e = FindArr(hash, i);
//		//printf("%d\n", e);
//		int j = HashArr(i, 5);
//		Bucket L = hash->list[j];
//		if (!e)
//		{
//			printf("%s\n", (const char*)L->arr[e].data);
//		}
//		else
//		{
//			printf("Not Found!\n");
//		}
//	}
//	DestoryArr(hash);
//	return 0;
//}





