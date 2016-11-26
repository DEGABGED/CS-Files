#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 0x7ff0000000000000

typedef struct Station {
	double dist;
	double price;
	int status; // shortest distance already found: 1
	int type; // 0: origin; 1: station; -1: destination
} Station;

typedef struct Edge {
	Station * adj_station;
	Station * cur_station;
	double dist_from_cur;
	//struct Edge * next; // arrays boi
} Edge;

typedef struct AdjList {
	int label; // place in index of adjlist
	Station * cur_station; // Pointer to actual Station data
	Edge * adj_list; // Array of edges
	//struct AdjList * next; // we usin arrays now boi
	int adj_list_size;
	int adj_list_max; // can be computed otw
} AdjList;

typedef struct PQ {
	// NOTE: everything about pq is 1-indexed!!!
	int size;
	int * heap; // AdjList 1=1 Station
	int * index; // index[Station.label] = ndx in heap
	double * key; // cost; or price * dist * mileage
} PQ;

// PQ algorithms in the book
void heapify(PQ * pq_ptr, int r) { // Adjust in brackets, not in code
	PQ pq = *pq_ptr;
	double k = pq.key[pq.heap[r-1]]; // key of root of heap
	int l = pq.heap[r-1]; // root of heap
	int i = r; // i starts at root
	int j = 2*i; // j starts at left subtree root
	while(j <= pq.size) { // 0-indexed
		if(j < pq.size && pq.key[pq.heap[j]-1] < pq.key[pq.heap[j-1]-1]) {
			j++; // j becomes lesser of 2 subtree roots
		}
		if(pq.key[pq.heap[j-1]-1] < k) { // if j < i
			pq.heap[i-1] = pq.heap[j-1]; // switch i and j in heap
			pq.index[pq.heap[j-1]-1] = i; // update position of j node
			i = j; // set i to be the node j it switched with
			j = 2*i; // set j to be left subtree root
		} else {
			break;
		}
	}
	pq.heap[i-1] = l; // set i to be the initial root of heap
	pq.index[l-1] = i; // update position of root of heap
}

int extract_min(PQ * pq_ptr) {
	PQ pq = *pq_ptr;
	if(pq.size == 0) return -1;
	int j = pq.heap[0];
	pq.heap[0] = pq.heap[pq.size - 1];
	pq.index[pq.heap[0]-1] = 1;
	pq.size--;
	heapify(&pq, 1);
}

void decrease_key(PQ * pq_ptr, int l, double newkey) {
	PQ pq = *pq_ptr;
	pq.key[l-1] = newkey;
	int i = pq.index[l-1];
	int j = i/2;
	while(i > 1 && pq.key[pq.heap[j-1]-1] > newkey) {
		pq.heap[i-1] = pq.heap[j-1];
		pq.index[pq.heap[j-1]-1] = i;
		i = j;
		j = i/2;
	}
	pq.heap[i-1] = l;
	pq.index[l-1] = i;
}

void printGraph(AdjList * G, int station_num) {
	int i,j;
	for(i=0; i<station_num+2; i++) {
		printf("Station %d: %lf away, %lf Php, %d of %d stations next\n",
				i,
				G[i].cur_station->dist,
				G[i].cur_station->price,
				G[i].adj_list_size,
				G[i].adj_list_max);
		for(j=0; j<G[i].adj_list_size; j++) {
			printf("\tStation %d is %lf from current\n",
					j+i+1,
					G[i].adj_list[j].dist_from_cur);
		}
	}
}

void createAdjList(AdjList * aj, double dist, double price,
		int type, int adj_list_max) {
	// Create the station
	aj->cur_station = (Station*) malloc(sizeof(Station));
	aj->cur_station->dist = dist;
	aj->cur_station->price = price;
	aj->cur_station->status = 0;
	aj->cur_station->type = type;

	// Create the adj_list, if not null
	if(adj_list_max > 0) {
		aj->adj_list = (Edge*) malloc(sizeof(Edge) * adj_list_max);
	} else {
		aj->adj_list = NULL;
	}
	aj->adj_list_size = 0;
	aj->adj_list_max = adj_list_max;
}

void createEdge(AdjList * aj, Station * adj_station) {
	int ndx = aj->adj_list_size;
	// Add the edge
	aj->adj_list[ndx].adj_station = adj_station;
	aj->adj_list[ndx].cur_station = aj->cur_station;
	aj->adj_list[ndx].dist_from_cur = adj_station->dist - aj->cur_station->dist;
	// Adjust the adj_list_size
	aj->adj_list_size++;
}

/*
AdjList * insert(AdjList * AL, double dist, double price,
		double edge_low, double edge_high) {
	// AL won't be null
	// Create a new Station
	Station * s = (Station*) malloc(sizeof(Station));
	s->dist = dist;
	s->price = price;

	// Create new edges for the previous nodes
	AdjList * ptr = AL;
	AdjList * b_ptr = NULL;
	Edge * e = NULL;
	while(ptr != NULL) {
		// Add edge to current station
		e = ptr->adj_list;
		ptr->adj_list = (Edge*) malloc(sizeof(Edge));
		ptr->adj_list->adj_station = s;
		ptr->adj_list->cur_station = ptr->cur_station;
		ptr->adj_list->dist_from_cur = s->dist - ptr->cur_station->dist;
		ptr->adj_list->next = e;
		// go to next station; keep track of previous for insertion
		b_ptr = ptr;
		ptr = ptr->next;
	}

	// Create new entry for the station
	AdjList * out = (AdjList*) malloc(sizeof(AdjList));
	out->cur_station = s;
	out->adj_list = NULL;
	b_ptr->next = out;
	return AL;
}*/

int main() {
	FILE * fin;
	FILE * fout;
	fin = fopen("input.txt", "r");
	fout = fopen("201508086.txt", "w");
	int case_num, station_num, i, j, flag;
	double total_dist, fuel_cap, mileage, min_dist,
		   max_dist, initial_cost, s_dist, s_price;
	AdjList * G = NULL;
	PQ pq;
	while(1) {
		// Get initial values
		G = NULL;
		flag = 1;
		if(fscanf(fin, "%d\n", &case_num) == EOF) break;
		fscanf(fin, "%lf\n%lf %lf %lf %d\n",
				&total_dist, &fuel_cap, &mileage,
				&initial_cost, &station_num);
		max_dist = fuel_cap * mileage;
		min_dist = max_dist / 0.5; // Must expend half its tank before stopping

		// Set the structures
		G = (AdjList*) malloc(sizeof(AdjList) * (station_num + 2));
		pq.heap = (int*) malloc(sizeof(int) * (station_num + 2));
		pq.key = (double*) malloc(sizeof(double) * (station_num + 2));
		pq.index = (int*) malloc(sizeof(int) * (station_num + 2));
		pq.size = station_num + 2;
		
		// Insert the origin
		createAdjList(G, 0, initial_cost, 0, station_num + 1);
		G[0].label = 0;
		pq.heap[0] = 1;
		pq.index[0] = 1;
		pq.key[0] = 0;

		// Insert the succeeding stations
		for(i=1; i<=station_num; i++) {
			fscanf(fin, "%lf %lf", &s_dist, &s_price);
			//G = insert(G, s_dist, s_price, max_dist, min_dist);
			createAdjList(G+i, s_dist, s_price, 1, station_num + 1 - i);
			G[i].label = i;
			pq.heap[i] = i+1;
			pq.index[i] = i+1;
			pq.key[i] = INF;

			// Add the stuff to the rest of the G
			for(j=0; j<i; j++) {
				// G+j: previous stations, G[i]: new station
				createEdge(G+j, G[i].cur_station);
			}
		}

		// Insert the destination
		createAdjList(G+station_num+1, total_dist, 0, -1, 0);
		G[station_num+1].label = station_num+1;
		pq.heap[station_num+1] = station_num+2;
		pq.index[station_num+1] = station_num+2;
		pq.key[station_num+1] = INF;

		// Add the destination to the rest of the adj_lists
		for(i=0; i<=station_num; i++) {
			createEdge(G+i, G[station_num+1].cur_station);
		}

		// Check if correct (delete after)
		printf("Case %d: %lf away, %lfL, %lfkm/L, %lfPhp, %d stations\n",
				case_num, total_dist, fuel_cap, mileage,
				initial_cost, station_num);
		printGraph(G, station_num);

		// Actual Dijkstra's
		while(flag != 0) {
			// call extract_min
			break; // for now
		}

		// Free G
		for(i=0; i<station_num+2; i++) {
			free(G[i].cur_station);
			free(G[i].adj_list);
		}
		free(G);
	}

	// check correctness of macro
	double x = INF;
	printf("inf: %lf\n", x);

	// Ending
	fclose(fin);
	fclose(fout);
}
