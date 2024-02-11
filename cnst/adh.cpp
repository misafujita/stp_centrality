/*

adh.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "struct.h"
#include "emalloc.h"
#include "swap.h"
#include "dijkstra.h"
#include "kruskal.h"

struct dist{
	int    *id_tree; // tree index
	int    *id_node; // node index
	double *value;
};
typedef struct dist dist_t;

void quicksort_dist(dist_t *dist, int begin, int end){

    int    i = begin;
    int    j = end;
    double pivot;

    pivot = dist->value[ ( begin + end ) / 2 ];

    while(1){
	    while( dist->value[i] < pivot ){ ++i; }
	    while( dist->value[j] > pivot ){ --j; }
	    if( i >= j ){ break; }

	    swap_dbl(&dist->value[i], &dist->value[j]);
	    swap_int(&dist->id_tree[i], &dist->id_tree[j]);
	    swap_int(&dist->id_node[i], &dist->id_node[j]);

	    i++;
	    j--;
	}

    if( begin < i - 1 ){ quicksort_dist( dist, begin, i-1 ); }
    if( j + 1 < end ){ quicksort_dist( dist, j+1, end ); }

}

void sbst_int(int a, int b, int *u, int *v){

    if(a < b){
		*u = a;
		*v = b;
    }else{
		*u = b;
		*v = a;
    }

}

void adh(int N, int E, int T, edge_t *elist, node_t *alist, int *trmnl, frag_t *frag, int *parent, st_t *st){

    int      i, j, u, v, x, y;
    int    **sp;        // the shortest path
    double **sd;        // the shortest distance
    int     *group;     // the group of nodes
    dist_t  *dist;      // the shortest distance from nodes to trees
    double  *f;         // evaluation function value
    double   min_value; // minimum evaluation function value
    int      min_index; // node index where minimum evaluation function value
    int      num_tree;  // the number of trees

    heap_t *heap;
    int    *a_sp;
    double *a_sd;

    group = (int*)e_calloc(N+1, sizeof(int), "group");
    sp    = (int**)e_malloc(N+1, sizeof(int*), "sp");
    sd    = (double**)e_malloc(N+1, sizeof(double*), "sd");
    dist  = (dist_t*)e_malloc(N+1, sizeof(dist_t), "dist");
    f     = (double*)e_calloc(N+1, sizeof(double), "f");
    heap  = (heap_t*)e_malloc(N+1, sizeof(heap_t), "heap");
    a_sp  = (int*)e_malloc(N+1, sizeof(int), "prev");
    a_sd  = (double*)e_malloc(N+1, sizeof(double), "dist");

    for(i=0;i<=N;i++){
		dist[i].id_tree = (int*)e_malloc(T+1, sizeof(int), "dist[i].id_tree");
		dist[i].id_node = (int*)e_malloc(T+1, sizeof(int), "dist[i].id_node");
		dist[i].value   = (double*)e_malloc(T+1, sizeof(double), "dist[i].value");
		sp[i]           = (int*)e_calloc(N+1, sizeof(int), "sp[i]");
		sd[i]           = (double*)e_calloc(N+1, sizeof(double), "sd[i]");
		st->node[i]     = 0;
    }

    for(i=1;i<=N;i++){
		dijkstra(N, alist, heap, frag->a, frag->b, i, a_sd, a_sp);

		/* save the shortest path */
		for(j=1;j<=N;j++){
			sp[i][j] = a_sp[j];
			sd[i][j] = a_sd[j];
		}
    }

    /* divide group */
    for(i=1;i<=T;i++){ group[ trmnl[i] ] = i; }

    /* Average Distance Heuristic */
    num_tree = T;
    do{

    	/* initialization */
    	for(i=1;i<=N;i++){
    	    for(j=1;j<=T;j++){
				dist[i].id_tree[j] = j;
				dist[i].id_node[j] = 0;
				dist[i].value[j]   = INT_MAX;
    	    }
    	}

    	/* caluclate the shortest distance from all nodes to all trees */
    	for(i=1;i<=N;i++){
    	    for(j=1;j<=N;j++){
				if(group[j] == 0){ continue; }

				if(group[i] == group[j]){
					dist[i].value[ group[j] ]   = 0.0;
					dist[i].id_node[ group[j] ] = j;
				}else if(sd[i][j] < dist[i].value[ group[j] ]){
					dist[i].value[ group[j] ]   = sd[i][j];
					dist[i].id_node[ group[j] ] = j;
				}

    	    }
    	}

    	/* sort the shortest distance in ascending order */
    	for(i=1;i<=N;i++){
    	    quicksort_dist(&dist[i], 1, T);
    	}

    	/* calculate the evaluation function value */
    	min_index = 0;
    	min_value = INT_MAX;
    	for(i=1;i<=N;i++){
    	    f[i] = dist[i].value[1] + dist[i].value[2];

    	    for(j=2;j<num_tree;j++){
				if(dist[i].value[j+1] < f[i]){
					f[i] = ( (j-1)*f[i] + dist[i].value[j] ) / j;
				}
    	    }

    	    if(f[i] < min_value){
				min_value = f[i];
				min_index = i;
    	    }
    	}

    	/* combine two trees */
    	sbst_int(dist[ min_index ].id_tree[1], dist[ min_index ].id_tree[2], &u, &v);
    	for(i=1;i<=N;i++){
    	    if(group[i] == v){
				group[i] = u;
    	    }
    	}

    	group[ min_index ] = u;
    	for(i=1;i<=2;i++){
    	    if(min_index == dist[ min_index ].id_node[i]){ continue; }
			track_prev(sp[min_index], min_index, dist[ min_index ].id_node[i], st->node);
    	}

		num_tree--;

    }while(num_tree > 1);


    /*** make induced minimum spanning tree ***/
    c_kruskal(N, E, elist, parent, st);

    for(i=0;i<=N;i++){
    	free(dist[i].id_tree);
    	free(dist[i].id_node);
    	free(dist[i].value);
		free(sd[i]);
		free(sp[i]);
    }
    free(group);
    free(dist);
    free(sp);
    free(sd);
    free(f);
    free(heap);
    free(a_sp);
    free(a_sd);

}
