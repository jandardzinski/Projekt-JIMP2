#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
	int nr;
	int edge;
struct Node **next;		
} *node_t;

node_t* c_graph(int n)	//tablica wierzcholkow		// funkcja do generowania grafu
{

	node_t* new_graph = malloc(n * sizeof(node_t));		

	for(int i = 0; i < n; i++)
	{
		node_t new_node = malloc(sizeof(*new_node));
		new_node->nr = i;
		new_graph[i] = new_node;
	}

	return new_graph;
}

void add_edge(node_t* graph, int* index, node_t node, int n)
{
	node->edge = n;
	node->next = malloc(sizeof(node_t) * n);
	
	for(int i = 0; i < n; i++)
		 node->next[i] = graph[index[i]];

}
void f_graph(node_t* graph, int n)				// funkcja zwalniajaca pamiec grafu
{
	for(int i = 0; i < n; i++)
	{
		free(graph[i]->next);
		free(graph[i]);
	}
	free(graph);
}

void p_graph(node_t *graph, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("\nWierzcholek %d:", graph[i]->nr);
		for(int j = 0; j < graph[i]->edge; j++)
		{
			printf(" %d", graph[i]->next[j]->nr);
		}
	}

	printf("\n\n");
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	int n = argc > 1 ? atoi(argv[1]) : 10;
	node_t *graph = c_graph(n);

	int index[5]; 
	
	for(int i = 0; i < n; i++)
	{
		int r = 1 + rand() % 5;
		int r_n;

		for(int j = 0; j < r; j++)
		{
			r_n = rand() % n;
			while(r_n == i)
				r_n = rand() % n;
			
			index[j] = r_n;
		}
		add_edge(graph, index, graph[i], r);
	}

	
	p_graph(graph, n);

}
