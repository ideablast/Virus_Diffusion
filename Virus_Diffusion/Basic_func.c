#include"ALL.h"

#ifdef ACTUAL
extern Stack* top;

Stack* Add_new_node()
{
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	temp->G_link = NULL;
	temp->S_link = NULL;

	return temp;
}

void Push_Link(Graph* node)
{
	Stack* temp = Add_new_node();
	temp->G_link = node;

	temp->S_link = top->S_link;
	top->S_link = temp;
}

Graph* Pop_Link()
{
	Stack* S_temp = top->S_link;
	Graph* G_temp = top->S_link->G_link;

	top->S_link = S_temp->S_link;
	free(S_temp);

	return  G_temp;
}

int IS_Empty()
{
	return top->S_link == NULL;
}
int** Make_Route()
{
	int size = rand() % (SIZE_END - SIZE_START + 1) + SIZE_START;
	//int size = 5;
	int i, j;
	int** route;
	//int ary[5][5] = { {0,1,1,0,1},{0,0,0,0,1},{1,1,0,0,1},{0,0,1,0,1},{0,1,0,0,0} };

	route = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
		route[i] = (int*)calloc(size , sizeof(int));
	
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i != j)
			{
				route[i][j] = rand() % 2;
				//route[i][j] = ary[i][j];
			}
				
		}
	}
	return route;
}

Graph** Make_Node(int** route)
{
	int i, j;
	int size = _msize(route) / sizeof(int*);
	Graph** node;

	node = (Graph**)malloc(size * sizeof(Graph*));
	for (i = 0; i < size; i++)
	{
		node[i] = (Graph*)malloc(sizeof(Graph));
		node[i]->ch = 'A' + i;
		node[i]->link = (Graph**)malloc(size * sizeof(Graph*));//0:왼쪽, 1:오른쪽.....
		for (j = 0; j < size; j++)
			node[i]->link[j] = NULL;
		
	}

	return node;
}

Graph** Input_Route(Graph** node, int** route)
{
	int i, j;
	int size = _msize(route) / sizeof(int*);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (route[i][j] == 1)
				node[i]->link[j] = node[j];
		}
	}
	return node;
}

void Print_Node_Link_state(Graph** node)
{
	int i, j;
	int size = _msize(node)/sizeof(Graph*);

	for (i = 0; i < size; i++)
	{
		printf("%c: ", node[i]->ch);
		for (j = 0; j < size; j++)
		{
			if (node[i]->link[j])
				printf("%c", node[i]->link[j]->ch);
		}
		puts("");
	}
}

void Print_Route_info_table(int** route)
{
	int i, j;
	int size = _msize(route) / sizeof(int*);

	printf("  ");
	for (i = 0; i < size; i++)
		printf("%c ", 'A' + i);
	puts("");
	for (i = 0; i < size; i++)
	{
		printf("%c ", 'A' + i);
		for (j = 0; j < size; j++)
				printf("%d ", route[i][j]);
		puts("");
	}
}

void DFS_Virus(Graph* node, int* check_table)
{
	Graph* search = node;
	int size = _msize(node->link) / sizeof(Graph*);
	int cnt = 0;
	int i;

	while (1)
	{
		if (search)
		{
			for (i = 0; i < size; i++)
			{
				if (check_table[i] == 1)
					cnt++;
			}
			if (cnt == size)
				break;
			else
				cnt = 0;

			if (check_table[search->ch - 'A'] == 1)
			{
				if (IS_Empty() == FALSE)
					search = Pop_Link();

				for (i = 0; i < size; i++)
				{
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
					{
						search = search->link[i];
						break;
					}
				}

				if (i == size)
					break;
			}
			else
			{
				check_table[search->ch - 'A'] = 1;
				if (Link_Count(search) > 1)
				{
					Push_Link(search);
				}
				else if (Link_Count(search) == 0)
				{
					if (IS_Empty() == FALSE)
						search = Pop_Link();
					else
						break;
				}
				for (i = 0; i < size; i++)
				{
					//for문만 돌고 if에서 break가 안걸리는 경우 예외 처리
					//갈 수 있는 링크는 이미 모두 방문한 경우
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
					{
						search = search->link[i];
						break;
					}
				}
			}
		}
	}

	cnt = 0;
	for (i = 0; i < size; i++)
	{
		if (check_table[i] == 1)
			cnt++;
	}
	printf("감염된 컴퓨터: %d대", cnt);
	
}

/*
void DFS_Virus(Graph* node, int* check_table)
{
	Graph* search = node;
	int size = _msize(node->link) / sizeof(Graph*);
	int cnt = 0;
	int i;

	while (1)
	{
		if (search)
		{
			for (i = 0; i < size; i++)
			{
				if (check_table[i] == 1)
					cnt++;
			}
			if (cnt == size)
				break;
			else
				cnt = 0;

			if (check_table[search->ch - 'A'] == 1 && IS_Empty() == FALSE)
				search = Pop_Link();

			check_table[search->ch - 'A'] = 1;
			printf("%c", search->ch);

			if (Link_Count(search) > 1)
			{
				Push_Link(search);
				for (i = 0; i < size; i++)
				{
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
					{
						search = search->link[i];
						break;
					}
				}
			}
			else if (Link_Count(search) == 1)
			{
				for (i = 0; i < size; i++)
				{
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
					{
						search = search->link[i];
						break;
					}
				}
			}
			else
			{
				if (IS_Empty() == FALSE)
				{
					search = Pop_Link();
					for (i = 0; i < size; i++)
					{
						if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
						{
							search = search->link[i];
							break;
						}
					}
				}
				else
					break;
			}


		}
	}
}

			check_table[search->ch - 'A'] = 1;
			printf("%c", search->ch);
			if (Link_Count(search) > 1)
			{
				Push_Link(search);
				for (i = 0; i < size; i++)
				{
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
					{
						search = search->link[i];
						break;
					}
				}
			}
			else if (Link_Count(search) == 0)
			{
				if (IS_Empty() == FALSE)
				{
					search = Pop_Link();
					for (i = 0; i < size; i++)
					{
						if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
						{
							search = search->link[i];
							break;
						}

					}
				}
				else
					break;
			}
			else if(Link_Count(search) == 1)
			{
				for (i = 0; i < size; i++)
				{
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
					{
						search = search->link[i];
						break;
					}
				}
			}*/
#endif

void Simulation_virus(Graph* node, int* check_table, int idx, int* min, int* max)
{
	int alpha = 0;
	int i;
	int cnt = 0;
	int size = _msize(node->link) / sizeof(Graph*);
	Graph* search = node;

	while (1)
	{
		if (search)
		{
			for (i = 0; i < size; i++)
			{
				if (check_table[i] == 1)
					cnt++;
			}
			if (cnt == size)
				break;
			else
				cnt = 0;

			if (check_table[search->ch - 'A'] != 1)
			{
				check_table[search->ch - 'A'] = 1;
				printf("%c", search->ch);
				for (i = 0; i < size; i++)
				{
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
						cnt++;
				}

				if (cnt >= 2)
				{
					Push_Link(search);
					cnt = 0;
				}

				for (i = 0; i < size; i++)
				{
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
					{
						search = search->link[i];
						break;
					}
				}
			}
			else
			{
				search = Pop_Link();
				for (i = 0; i < size; i++)
				{
					if (search->link[i] && check_table[search->link[i]->ch - 'A'] != 1)
					{
						search = search->link[i];
						break;
					}
				}

			}


		}
	}


}
int Link_Count(Graph* node)
{
	int i;
	int cnt = 0;
	int size = _msize(node->link) / sizeof(Graph*);

	for (i = 0; i < size; i++)
	{
		if (node->link[i])
			cnt++;
	}
	return cnt;
}
/*

		if (check_table[node->ch - 'A'] != 1)
			check_table[node->ch - 'A'] = 1;
		else
		{	return;
		}


		for (alpha = 0; alpha < size; alpha++)
		{
			idx++;
			Simulation_virus(node->link[alpha], check_table, idx, min, max);
			*min = 0;
			*max = 0;

			for (i = idx; i < size; i++)
				check_table[idx] = 0;
			for (i = 0; i < size; i++)
			{
				if (check_table[i] == 1)
					cnt++;
			}
			if (*max == 0 && *min == 0)
			{
				*max = cnt;
				*min = cnt;
			}
			else
			{
				if (cnt > *max)
					*max = cnt;
				if (cnt < *min)
					*min = cnt;
			}


		}


*/