#include"ALL.h"

Stack* top;
int main()
{
	//선택한 노드를 기준으로 바이러스에 감염된 컴퓨터의 갯수를 출력함

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