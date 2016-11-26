#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Station {
	double dist;
	double price;
} Station;

typedef struct Edge {
	Station * adj_station;
	Station * cur_station;
	double dist_from_cur;
	struct Edge * next;
} Edge;

typedef struct AdjList {
	Station * cur_station;
	Edge * adj_list;
	struct AdjList * next;
} AdjList;

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
}

int main() {
	FILE * fin;
	FILE * fout;
	fin = fopen("input.txt", "r");
	fout = fopen("201508086.txt", "w");
	int case_num, station_num, i;
	double total_dist, fuel_cap, mileage,
		   max_dist, initial_cost, s_dist, s_price;
	AdjList * G = NULL;
	while(1) {
		G = NULL;
		if(fscanf(fin, "%d\n", &case_num) == EOF) break;
		fscanf(fin, "%lf\n%lf %lf %lf %d\n",
				&total_dist, &fuel_cap, &mileage,
				&initial_cost, &station_num);
		max_dist = fuel_cap * mileage;
		min_dist = max_dist / 0.5 // Must expend half its tank before stopping

		// Insert the origin node
		G = (AdjList*) malloc(sizeof(AdjList));
		G->cur_station = (Station*) malloc(sizeof(Station));
		G->cur_station->dist = 0; // Not necessary
		G->cur_station->price = initial_cost; // Not necessary
		G->adj_list = NULL;
		G->next = NULL;

		// Insert the succeeding stations
		for(i=0; i<station_num; i++) {
			fscanf(fin, "%lf %lf", &s_dist, &s_price);
			G = insert(G, s_dist, s_price, max_dist, min_dist);
		}

		// Insert the destination
		G = insert(G, total_dist, 0, max_dist, 0); // Can and will stop at dest

		// Check if correct (delete after)
		AdjList * ptr = G;
		Edge * ptr2 = NULL;
		printf("Case %d: %lf away, %lfL, %lfkm/L, %lfPhp, %d stations\n",
				case_num, total_dist, fuel_cap, mileage,
				initial_cost, station_num);
		for(;ptr != NULL;ptr = ptr->next) {
			printf("Station %lf away: %lf Php\n",
					ptr->cur_station->dist,
					ptr->cur_station->price);
			for(ptr2 = ptr->adj_list; ptr2!=NULL; ptr2 = ptr2->next) {
				printf("\tStation %lf away is %lf from current\n",
						ptr2->adj_station->dist,
						ptr2->dist_from_cur);
			}
		}

		// Actual Dijkstra's
	}

	// Ending
	fclose(fin);
	fclose(fout);
}
