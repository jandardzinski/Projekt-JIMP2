#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
	int nr;
	int edge;
	struct Node **next;		
} *node_t;

node_t* c_graph(int n)			//funkcja alokujaca pamiec dla calego grafu 
{
    node_t* new_graph = malloc(n * sizeof(node_t));         //alokacja pamieci dla samego grafu

    for (int i = 0; i < n; i++) 
    {
        node_t new_node = malloc(sizeof(*new_node));		//alokacja pamieci dla struktury kazdego poszczegolnego wierzcholka
        new_node->nr = i;					// przypisanie dla danego wierzcholka danego numeru
        new_node->edge = 0;					// ustawiawy ilosc krawedzi wychodzacych z wierzcholka startowo na "0"
        new_node->next = NULL;					// nexta ustawiamy na NULL
        new_graph[i] = new_node;				// i dla kazdego elementu grafu przypisujemy po kolei dany wierzcholek	
    }

    return new_graph;						
}	

void add_edge(node_t* graph, int* index, node_t node, int n)  //funkcja dodajaca krawedzie miedzy wierzcholkami (graph to wiadomo, int* index - tablica przechowujaca numery wierzcholkow 
{
        node->edge = n;					//ilosc polaczen (krawedzi)  dla danego wybranego losowo wierzcholka 
        node->next = malloc(sizeof(node_t) * n);		//w kazdym wierzcholku alokujemy pamiec dla odpowiedniej ilosci wierzcholkow  z ktorymi on sie laczy
        for(int i = 0; i < n; i++)
                 node->next[i] = graph[index[i]];		// wypelniamy kazdy element listy danego wierzcholka numerami losowo wybranych wierzcholkow

}

void f_graph(node_t* graph, int n) 			//funkcja zwalniajaca pamiec grafu
{
    for (int i = 0; i < n; i++) 			
    {
        free(graph[i]->next);
        free(graph[i]);
    }
    free(graph);
}

int compare(const void *a, const void *b)	//funkcja pomocniczna compare do sortowania w macierzy sasiedztwa
{
	return (*(int*)a - *(int*)b);
}

void p_graph(node_t *graph, int n, FILE *out) 			// funkcja do wypisania listy sasiedztwa
{
    for (int i = 0; i < n; i++) 
    {
        fprintf(out, "\nWierzcholek %d:", graph[i]->nr);        // wypisanie "Wierzcholek ... : "
        for (int j = 0; j < graph[i]->edge; j++) 
	{
        	fprintf(out, " %d", graph[i]->next[j]->nr);     //wypisanie numerow wierzcholkow z ktorymi dany wierzcholek sie laczy
        }
    }
    fprintf(out, "\n\n");					//wszystko to idzie do pliku
}


void matrix(node_t* graph, int n)			// funkcja tworzaca macierz sasiedztwa
{
	FILE *out = fopen("wynik", "w");		// tak samo to tez idzie do pliku wynikowego

	for(int i = 0; i < n; i++)
	{
		int *index = malloc(graph[i]->edge * sizeof(int));  // tworzymy tablice numerow wierzcholkow do ktorych wychodza krawedzie dla konkretnego wierzcholka

		for(int j = 0; j < graph[i]->edge; j++)					// wypelniamy  losowo wybranymi numerami wierzcholkow tablice index
			index[j] = graph[i]->next[j]->nr;

		qsort(index, graph[i]->edge, sizeof(int), compare);			// sortujemy ta tablice 

		int counter = 0;				
		fprintf(out," | ");						//wypisanie macierzy do pliku

		for(int j = 0; j < n; j++)					// no i teraz uzupelnienie tej macierzy	
		{								//dajemy counter = 0 i zwiekszamy go w momencie wypisania danego polaczenia do macierzy
										
				if(j == index[counter])				// w momencie gdy numer wierzcholka docelowego podczas petli bedzie taki sam jak ten na odpowiednim
										// miejscu w tablicy index wypisujemy "1" i zwiekszamy counter i tak dla kazdego wierzcholka od 1 do n
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

int main(int argc, char **argv) 				// no i tu main juz
{
    srand(time(NULL));						// ustawiamy seeda na NULL, aby za kazdym razem kiedy odpalamy program dostac inne losowe wartosci				
    int n = argc > 1 ? atoi(argv[1]) : 10;			// ilosc wierzcholkow w grafie podawana z poziomu konsoli
    node_t *graph = c_graph(n);					// tworzy sie graf na podstawie tej ilosci ( alokacja pamieci)

    int *index; 						

    for (int i = 0; i < n; i++) 
    {
        int r = 1 + rand() % 5;  				// r - losowa ilosc krawedzi wychodzacych z danego wierzcholka mozna zwiekszyc ale tu przydaloby sie zabezpieczyc 

        index = malloc(r * sizeof(int)); 			// alokacja pamieci dla tablicy indeksow  o ilosci r 
        int counter = 0;

        while (counter < r) 						
	{
            int r_n = rand() % n;				// r_n - losowo wybrany numer wierzcholka ktory bedzie wierzcholkiem docelowym

            int exists = 0;
            if (r_n == i) 					// gdy wylosuje sie taki sam numer jak wierzcholek poczatkowy, pomijamy	
		   continue;  

            for (int j = 0; j < counter; j++) 			
	    {
                if (index[j] == r_n) 
		{
                    exists = 1;
                    break;
                }
            }

            if (!exists) 			//jezeli nie istnieje (wartosc exists = 0) to dla danego elementu tablicy index przypisujemy wylosowany numer wierzcholka docelowego
	    {  
                index[counter++] = r_n; 
            }
        }

        add_edge(graph, index, graph[i], r); 		// no  i tu uzycie wszystkich funkcji 
        free(index);  
    }

   // p_graph(graph, n);
	
    matrix(graph, n);

    f_graph(graph, n); 
    return 0;
}


