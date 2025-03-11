#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Node {
    int nr;
    int edge;
    struct Node **next;
} *node_t;

node_t* c_graph(int n) 
{
    node_t* new_graph = malloc(n * sizeof(node_t));

    for (int i = 0; i < n; i++) 
    {
        node_t new_node = malloc(sizeof(*new_node));
        new_node->nr = i;
        new_node->edge = 0;
        new_node->next = NULL;
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

void f_graph(node_t* graph, int n) 
{
    for (int i = 0; i < n; i++) 
    {
        free(graph[i]->next);
        free(graph[i]);
    }
    free(graph);
}

int compare(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

void p_graph(node_t *graph, int n, FILE *out) 
{
    for (int i = 0; i < n; i++) 
    {
        fprintf(out, "\nWierzcholek %d:", graph[i]->nr);
        for (int j = 0; j < graph[i]->edge; j++) 
	{
        	fprintf(out, " %d", graph[i]->next[j]->nr);
        }
    }
    fprintf(out, "\n\n");
}


void matrix(node_t* graph, int n)
{
	FILE *out = fopen("wynik", "w");

	for(int i = 0; i < n; i++)
	{
		int *index = malloc(graph[i]->edge * sizeof(int));

		for(int j = 0; j < graph[i]->edge; j++)
			index[j] = graph[i]->next[j]->nr;

		qsort(index, graph[i]->edge, sizeof(int), compare);

		int counter = 0;
		fprintf(out," | ");

		for(int j = 0; j < n; j++)
		{
				
				if(j == index[counter])
				{
					fprintf(out, "1 ");
					counter++;
				}

				else 
					fprintf(out, "0 ");
		}

		fprintf(out, "|\n");
		free(index);
	}
	
	fprintf(out, "\n");
	p_graph(graph, n, out);



}

int main(int argc, char **argv) 
{
    srand(time(NULL));
    int n = argc > 1 ? atoi(argv[1]) : 10;
    node_t *graph = c_graph(n);

    int *index; 

    for (int i = 0; i < n; i++) 
    {
        int r = 1 + rand() % 5;  

        index = malloc(r * sizeof(int)); 
        int counter = 0;

        while (counter < r) 
	{
            int r_n = rand() % n;

            int exists = 0;
            if (r_n == i) 
		   continue;  

            for (int j = 0; j < counter; j++) 
	    {
                if (index[j] == r_n) 
		{
                    exists = 1;
                    break;
                }
            }

            if (!exists) 
	    {  
                index[counter++] = r_n; 
            }
        }

        add_edge(graph, index, graph[i], r); 
        free(index);  
    }

   // p_graph(graph, n);
	
    matrix(graph, n);

    f_graph(graph, n); 
    return 0;
}


