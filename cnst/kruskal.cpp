/*

kruskal.c

*/

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "emalloc.h"
#include "swap.h"

void quicksort_edge(edge_t *array, int begin, int end){

    int    i = begin;
    int    j = end;
    double pivot;

    pivot = array[ ( begin + end ) / 2 ].cost;

    while(1){

		while( array[i].cost < pivot ){ ++i; }
		while( array[j].cost > pivot ){ --j; }
		if( i >= j ){ break; }

		swap_int(&array[i].from, &array[j].from);
		swap_int(&array[i].to, &array[j].to);
		swap_dbl(&array[i].orig, &array[j].orig);
		swap_dbl(&array[i].cent, &array[j].cent);
		swap_dbl(&array[i].cost, &array[j].cost);

		i++;
		j--;

    }

    if( begin < i - 1 ){ quicksort_edge( array, begin, i-1 ); }
    if( j + 1 < end ){ quicksort_edge( array, j+1, end ); }

}

int root(int *par, int x){

    if(par[x] == x){
    	return x;
    }else{
    	return par[x] = root(par, par[x]);
    }

}

void unite(int *par, int x, int y){

    x = root(par, x);
    y = root(par, y);

    x < y ? par[y] = x : par[x] = y;

}

void kruskal(int N, int E, edge_t *elist, int *par, edge_t *mst, double *mst_cost){

    int i, j;

    *mst_cost = 0.0;
    for(i=1;i<=N;i++){ par[i] = i; }

    j = 1;
    for(i=1;i<=E;i++){

		if(root(par, elist[i].from) != root(par, elist[i].to)){
			unite(par, elist[i].from, elist[i].to);

			mst[j].from = elist[i].from;
			mst[j].to   = elist[i].to;
			mst[j].cost = elist[i].cost;
			*mst_cost  += mst[j].cost;

			j++;
		}

    }

}

void c_kruskal(int N, int E, edge_t *elist, int *par, st_t *st){

    int i, j;

    st->cost = 0.0;
    st->orig = 0.0;
    for(i=1;i<=N;i++){
		par[i] = i;
		st->elist[i].from = 0;
		st->elist[i].to   = 0;
		st->elist[i].cost = 0;
		st->elist[i].orig = 0;
    }

    st->E = 0;
    for(i=1;i<=E;i++){

		if(st->node[ elist[i].from ] == 0 || st->node[ elist[i].to ] == 0){ continue; }

		if(root(par, elist[i].from) != root(par, elist[i].to)){
			unite(par, elist[i].from, elist[i].to);
			st->cost += elist[i].cost;
			st->orig += elist[i].orig;

			st->E                  += 1;
			st->elist[ st->E ].from = elist[i].from;
			st->elist[ st->E ].to   = elist[i].to;
			st->elist[ st->E ].cost = elist[i].cost;
			st->elist[ st->E ].orig = elist[i].orig;
		}

    }

}

int num_cmp(int N, int *frag, int *par, int *node){

    int i;
    int num_cmp = 0;

    for(i=0;i<=N;i++){ frag[i] = 0; }

    for(i=1;i<=N;i++){
		if(node[i] == 1 && frag[ root(par, i) ] == 0){
			frag[ root(par, i) ] = 1;
			num_cmp++;
		}
    }

    return num_cmp;

}
