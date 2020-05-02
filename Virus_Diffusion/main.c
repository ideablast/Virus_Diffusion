#include"ALL.h"

Stack* top;
int main()
{
	//������ ��带 �������� ���̷����� ������ ��ǻ���� ������ �����

	srand((unsigned int)time(NULL));
	int** route = Make_Route();
	Graph** node = Make_Node(route);
	int* check_table = (int*)calloc(_msize(route) / sizeof(int*), sizeof(int));
	int min = 0, max = 0;

	top = Add_new_node();
	node = Input_Route(node, route);

	Print_Route_info_table(route);
	Print_Node_Link_state(node);
	DFS_Virus(node[0], check_table);
	//Simulation_virus(node[0], check_table, 0, &min, &max);
	
}