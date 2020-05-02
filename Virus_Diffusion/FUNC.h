#pragma once

#ifndef __FUNC_H__
#define __FUNC_H__

/*DFS*/
int** Make_Route();
Graph** Make_Node(int** route);
Graph** Input_Route(Graph** node, int** route);
void Print_Node_Link_state(Graph** node);
void Print_Route_info_table(int** route);
void Simulation_virus(Graph* node, int* check_table, int idx, int* min, int* max);
int Link_Count(Graph* node);
void DFS_Virus(Graph* node, int* check_table);


/*STACK*/
Stack* Add_new_node();
void Push_Link(Graph* node);
Graph* Pop_Link();
int IS_Empty();

#endif
