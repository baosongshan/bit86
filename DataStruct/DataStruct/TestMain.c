#include"SeqList.h"

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
		case 16:
			SeqListClear(&mylist);
			break;
		}
		system("pause");
		system("cls");
	}

	SeqListDestroy(&mylist);

	return 0;
}