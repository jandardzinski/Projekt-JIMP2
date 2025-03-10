#include <stdio.h>
#include <stdlib.h>



typedef struct Graph
{
	int v_totalnumber;			// liczba wszystkich wierzcholkow grafu
	int* neighbours;			// liczba sasiadow danego wierzcholka
	int** neighbours_list;			// lista istniejacych krawedzi miedzy danymi wierzcholkami
} *graph_t;

graph_t c_graph(int v_totalnumber)			// funkcja do generowania grafu
{
	graph_t new_graph = (graph_t**)malloc(sizeof(new_graph));		
	new_graph->v_totalnumber = v_totalnumber;
	new_graph->neighbours = (int*)calloc(v_totalnumber, sizeof(int));
	if(!new_graph->neighbours)
	{
		printf("Nieudana alokacja pamieci dla tablicy sasiadow wierzcholkow.");
		return NULL;
	}

	new_graph->neighbours_list = (int**)malloc(v_totalnumber * sizeof(int));		
	if(!new_graph->neighbours_list)
	{
		printf("Nieudana alokacja pamieci dla listy sasiedztwa");
		return NULL;
	}

	for(int i = 0; i < v_totalnumber; i++)
	{
		new_graph->neighbours_list = NULL;
	}

	return new_graph;
}

void add_edge(graph_t new_graph, int v_first, int v_second)
{
	new_graph->neighbours[v_first]++;				//zwiekszamy liczbe sasiednich wierzcholkow dla pierwszego wierzcholka z ktorego tworzymy polaczenie
	new_graph->neighbours[v_second]++;				// -||-

	new_graph->neighbours_list[v_first] = (int*)realloc(new_graph->neighbours_list[v_first], new_graph->neighbours[v_first] * sizeof(int)); 	// alokacja pamieci dla listy
																			// polaczen dla kazdego 
																			// wierzcholka
	new_graph->neighbours_list[v_second] = (int*)realloc(new_graph->neighbours_list[v_second], new_graph->neighbours[v_second] * sizeof(int));

	new_graph->neighbours_list[v_first][new_graph->neighbours[v_first] - 1] = v_second;		// dodanie polaczenia miedzy wierzcholkami do listy
	new_graph->neighbours_list[v_second][new_graph->neighbours[v_second] - 1] = v_first;


}

void f_graph(graph_t new_graph)				// funkcja zwalniajaca pamiec grafu
{
	for(int i = 0; i < new_graph->v_totalnumber; i++)
	{
		free(new_graph->neighbours_list[i]);
	}
	free(new_graph->neighbours_list);
	free(new_graph->neighbours);
	free(new_graph);
}
