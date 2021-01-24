//#include"SeqList.h"
//#include"List.h"
//#include"Stack.h"
#include"Queue.h"

void main()
{
	SeqQueue Q;
	SeqQueueInit(&Q, 0);
	SeqQueueEn(&Q, 1);
	SeqQueueEn(&Q, 3);
	SeqQueueEn(&Q, 5);
	SeqQueueEn(&Q, 4);
	SeqQueueEn(&Q, 2);
	SeqQueueEn(&Q, 6);
	SeqQueueEn(&Q, 7);
	SeqQueueEn(&Q, 8);

	SeqQueueEn(&Q, 20);

	SeqQueueDe(&Q);
	SeqQueueEn(&Q, 20);
	SeqQueueDe(&Q);
	SeqQueueEn(&Q, 30);
	SeqQueueShow(&Q);

}

/*
void main()
{
	SeqQueue Q;
	SeqQueueInit(&Q, 0);
	SeqQueueEn(&Q, 1);
	SeqQueueEn(&Q, 3);
	SeqQueueEn(&Q, 5);
	SeqQueueEn(&Q, 4);
	SeqQueueEn(&Q, 2);
	SeqQueueShow(&Q);
	printf("====================\n");
	SeqQueueDe(&Q);
	SeqQueueShow(&Q);

	int val = SeqQueueBack(&Q);
	printf("back val = %d\n", val);
	val = SeqQueueFront(&Q);
	printf("front val = %d\n", val);

	SeqQueueEn(&Q, 100);
	val = SeqQueueBack(&Q);
	printf("back val = %d\n", val);
	val = SeqQueueFront(&Q);
	printf("front val = %d\n", val);


}

/*
void main()
{
	LinkQueue Q;
	LinkQueueInit(&Q);
	LinkQueueEn(&Q, 1);
	LinkQueueEn(&Q, 2);
	LinkQueueEn(&Q, 3);
	LinkQueueEn(&Q, 4);
	LinkQueueEn(&Q, 15);
	LinkQueueEn(&Q, 6);
	LinkQueueShow(&Q);
	printf("==============\n");
	
	QueueElemType val = LinkQueueFront(&Q);
	LinkQueueDe(&Q);
	printf("%d ����.\n", val);

	LinkQueueDestroy(&Q);
}

/*
void main()
{
	LinkStack st;
	LinkStackInit(&st);
	LinkStackPush(&st, 1);
	LinkStackPush(&st, 2);
	LinkStackPush(&st, 4);
	LinkStackPush(&st, 3);
	LinkStackPush(&st, 5);
	LinkStackShow(&st);
	printf("============\n");

	StackElemType val = LinkStackTop(&st);
	LinkStackPop(&st);
	//LinkStackShow(&st);
	printf("%d ��ջ.\n", val);

	LinkStackDestroy(&st);
}

/*
void main()
{
	SeqStack st;
	SeqStackInit(&st, 0);
	SeqStackPush(&st,1);
	SeqStackPush(&st,2);
	SeqStackPush(&st,3);
	SeqStackPush(&st,4);
	SeqStackPush(&st,5);
	SeqStackShow(&st);
	printf("============\n");

	while(!IsEmpty(&st))
	{
		StackElemType val = SeqStackTop(&st);
		SeqStackPop(&st);
		printf("%d ��ջ.\n", val);
	}
	printf("��ջ���.\n");

	SeqStackDestroy(&st);
}

/*
void main()
{
	SeqStack st;
	SeqStackInit(&st, 0);
	SeqStackPush(&st,1);
	SeqStackPush(&st,2);
	SeqStackPush(&st,3);
	SeqStackPush(&st,4);
	SeqStackPush(&st,5);
	SeqStackShow(&st);
	printf("============\n");
	SeqStackPush(&st,10);
	SeqStackShow(&st);
	printf("============\n");
	SeqStackPop(&st);
	SeqStackShow(&st);
	printf("============\n");
	SeqStackPop(&st);
	SeqStackShow(&st);
	printf("============\n");
	SeqStackPop(&st);
	SeqStackShow(&st);
	

}

/*
int main()
{
	
	DCList mylist;
	DCListInit(&mylist);

	ElemType item, key;
	int pos;

	DCListNode *p;

	int select = 1;
	while(select)
	{
		printf("********************************************\n");
		printf("* [1] push_back        [2] push_front      *\n");
		printf("* [3] show_list        [0] quit_system     *\n");
		printf("* [4] pop_back         [5] pop_front       *\n");
		printf("* [6] length           [*7] capacity       *\n");
		printf("* [8] insert_val       [*9] insert_pos     *\n");
		printf("* [10] delete_val      [*11] delete_pos    *\n");
		printf("* [12] find            [13] sort           *\n");
		printf("* [14] reverse         [15] remove_all     *\n");
		printf("* [16] clear           [*17] destroy       *\n");
		printf("* [*18] find_binary                        *\n");
		printf("********************************************\n");
		printf("��ѡ��:>");
		scanf("%d", &select);
		switch(select)
		{
		case 1:
			printf("������Ҫ���������(��-1����):>");
			while(scanf("%d", &item), item!=-1)  //���ű��ʽ
				DCListPushBack(&mylist, item);
			break;
		case 2:
			printf("������Ҫ���������(��-1����):>");
			while(scanf("%d", &item), item!=-1)  //���ű��ʽ
				DCListPushFront(&mylist, item); 
			break;
		case 3:
			DCListShow(&mylist);
			break;
		case 4:
			DCListPopBack(&mylist);
			break;
		case 5:
			DCListPopFront(&mylist);
			break;
		case 6:
			printf("��Ϊ:>%d\n", DCListLength(&mylist));
			break;
		case 7:
			//printf("�������Ϊ:>%d\n", SeqListCapacity(&mylist));
			break;
		case 8:
			printf("������Ҫ�����ֵ:>");
			scanf("%d", &item);
			DCListInsertByVal(&mylist, item);
			break;
		case 9:
			printf("������Ҫ�����λ��:>");
			scanf("%d", &pos);
			printf("������Ҫ�����ֵ:>");
			scanf("%d", &item);
			//SeqListInsertByPos(&mylist, pos, item);
			break;
		case 10:
			printf("������Ҫɾ����ֵ:>");
			scanf("%d", &key);
			DCListDeleteByVal(&mylist, key);
			break;
		case 11:
			printf("������Ҫɾ����λ��:>");
			scanf("%d", &pos);
			//SeqListDeleteByPos(&mylist, pos);
			break;
		case 12:
			printf("������Ҫ���ҵ�ֵ:>");
			scanf("%d", &key);
			p = DCListFind(&mylist, key);
			if(p == NULL)
				printf("Ҫ���ҵ�ֵ%d������.\n", key);
			else
				printf("Ҫ���ҵ�ֵ%d����.\n",key);
			break;
		case 13:
			//SListSort(&mylist);
			break;
		case 14:
			DCListReverse(&mylist);
			break;
		case 15:
			printf("������Ҫɾ����ֵ:>");
			scanf("%d", &key);
			//SListRemoveAll(&mylist, key);
			break;
		case 16:
			DCListClear(&mylist);
			break;
		case 18:
			printf("������Ҫ���ҵ�ֵ:>");
			scanf("%d", &key);
			//pos = SeqListFindByBinary(&mylist, key);
			if(pos == -1)
				printf("Ҫ���ҵ�ֵ%d������.\n", key);
			else
				printf("Ҫ���ҵ�ֵ%d���±�Ϊ%d��λ��.\n",key, pos);
			break;
		}
		system("pause");
		system("cls");
	}

	DCListDestroy(&mylist);

	return 0;
}


/*
int main()
{
	SeqList mylist;
	SeqListInit(&mylist);

	ElemType item, key;
	int pos;

	int select = 1;
	while(select)
	{
		printf("********************************************\n");
		printf("* [1] push_back        [2] push_front      *\n");
		printf("* [3] show_list        [0] quit_system     *\n");
		printf("* [4] pop_back         [5] pop_front       *\n");
		printf("* [6] length           [7] capacity        *\n");
		printf("* [8] insert_val       [9] insert_pos      *\n");
		printf("* [10] delete_val      [11] delete_pos     *\n");
		printf("* [12] find            [13] sort           *\n");
		printf("* [14] reverse         [15] remove_all     *\n");
		printf("* [16] clear           [*17] destroy       *\n");
		printf("* [18] find_binary                         *\n");
		printf("********************************************\n");
		printf("��ѡ��:>");
		scanf("%d", &select);
		switch(select)
		{
		case 1:
			printf("������Ҫ���������(��-1����):>");
			while(scanf("%d", &item), item!=-1)  //���ű��ʽ
				SeqListPushBack(&mylist, item);
			break;
		case 2:
			printf("������Ҫ���������(��-1����):>");
			while(scanf("%d", &item), item!=-1)  //���ű��ʽ
				SeqListPushFront(&mylist, item);
			break;
		case 3:
			SeqListShow(&mylist);
			break;
		case 4:
			SeqListPopBack(&mylist);
			break;
		case 5:
			SeqListPopFront(&mylist);
			break;
		case 6:
			printf("��Ϊ:>%d\n", SeqListLength(&mylist));
			break;
		case 7:
			printf("�������Ϊ:>%d\n", SeqListCapacity(&mylist));
			break;
		case 8:
			printf("������Ҫ�����ֵ:>");
			scanf("%d", &item);
			SeqListInsertByVal(&mylist, item);
			break;
		case 9:
			printf("������Ҫ�����λ��:>");
			scanf("%d", &pos);
			printf("������Ҫ�����ֵ:>");
			scanf("%d", &item);
			SeqListInsertByPos(&mylist, pos, item);
			break;
		case 10:
			printf("������Ҫɾ����ֵ:>");
			scanf("%d", &key);
			SeqListDeleteByVal(&mylist, key);
			break;
		case 11:
			printf("������Ҫɾ����λ��:>");
			scanf("%d", &pos);
			SeqListDeleteByPos(&mylist, pos);
			break;
		case 12:
			printf("������Ҫ���ҵ�ֵ:>");
			scanf("%d", &key);
			pos = SeqListFind(&mylist, key);
			if(pos == -1)
				printf("Ҫ���ҵ�ֵ%d������.\n", key);
			else
				printf("Ҫ���ҵ�ֵ%d���±�Ϊ%d��λ��.\n",key, pos);
			break;
		case 13:
			SeqListSort(&mylist);
			break;
		case 14:
			SeqListReverse(&mylist);
			break;
		case 15:
			printf("������Ҫɾ����ֵ:>");
			scanf("%d", &key);
			SeqListRemoveAll(&mylist, key);
			break;
		case 16:
			SeqListClear(&mylist);
			break;
		case 18:
			printf("������Ҫ���ҵ�ֵ:>");
			scanf("%d", &key);
			pos = SeqListFindByBinary(&mylist, key);
			if(pos == -1)
				printf("Ҫ���ҵ�ֵ%d������.\n", key);
			else
				printf("Ҫ���ҵ�ֵ%d���±�Ϊ%d��λ��.\n",key, pos);
			break;
		}
		system("pause");
		system("cls");
	}

	SeqListDestroy(&mylist);

	return 0;
}
*/