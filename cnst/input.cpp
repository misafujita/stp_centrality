/*

input.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "struct.h"

int get_int(char buf[], char *read){

    fgets(buf, 256, stdin);
    read = buf;

    if(!strcmp(buf, "\0")){ fprintf(stderr, "get_int failed\n"); exit(1); }

    return atoi(read);

}

void get_array(char buf[], char *read, int low, int *array){

    int i = 1;
    while(i <= low){

		if(fgets(buf, 256, stdin) == NULL){ fprintf(stderr, "get_array failed\n"); exit(1); }

    	read = strtok(buf, " \t");
		array[i] = atoi(read);

		i++;

    }

}

void get_array_dbl(char buf[], char *read, int low, double *array){

    int i = 1;
    while(i <= low){

		if(fgets(buf, 256, stdin) == NULL){ fprintf(stderr, "get_array_dbl failed\n"); exit(1); }

    	read = strtok(buf, " \t");
		array[i] = atof(read);

		i++;

    }

}

void get_edge(char buf[], char *read, int E, edge_t *edge){

    int i = 1;
    while(i <= E){

		if(fgets(buf, 256, stdin) == NULL){ fprintf(stderr, "get_edge failed\n"); exit(1); }

    	read = strtok(buf, " \t");
		edge[i].from = atoi(read);

    	read = strtok(NULL, " \t");
		edge[i].to = atoi(read);

    	read = strtok(NULL, " \t");
		edge[i].orig = atof(read);


		i++;

    }

}

void cal_degree(int N, int E, edge_t *elist, int *degree){

    int i = 1;
    while(i <= N){
		degree[i] = 0;
		i++;
    }

    i = 1;
    while(i <= E){
		degree[ elist[i].from ] += 1;
		degree[ elist[i].to   ] += 1;
		i++;
    }

}

void mk_alist(int N, int E, edge_t *elist, node_t *alist){

    int  i;
    int *degree;

    degree = (int*)e_malloc(N+1, sizeof(int), "degree");
    cal_degree(N, E, elist, degree);

    i = 1;
    while(i <= N){
		alist[i].degree = degree[i];
		alist[i].to     = (int*)e_malloc(degree[i]+1, sizeof(int), "alist[i].to");
		alist[i].cost   = (double*)e_malloc(degree[i]+1, sizeof(double), "alist[i].cost");
		alist[i].empty  = 1;
		i++;
    }

    i = 1;
    while(i <= E){
    	alist[ elist[i].from ].to[ alist[elist[i].from].empty ] = elist[i].to;
    	alist[ elist[i].from ].cost[ alist[elist[i].from].empty ] = elist[i].cost;
    	alist[ elist[i].from ].empty += 1;

    	alist[ elist[i].to ].to[ alist[elist[i].to].empty ] = elist[i].from;
    	alist[ elist[i].to ].cost[ alist[elist[i].to].empty ] = elist[i].cost;
    	alist[ elist[i].to ].empty += 1;

		i++;
    }

    free(degree);

}

void mk_trmnl_bnr(int N, int T, int *trmnl, int *trmnl_bnr){

    int i = 1;
    while(i <= N){
		trmnl_bnr[i] = 0;
		i++;
    }

    i = 1;
    while(i <= T){
		trmnl_bnr[ trmnl[i] ] = 1;
		i++;
    }

}

void get_graph(char buf[], char *read,
			   int *N, int *E, int *T, edge_t **elist, node_t **alist, int **trmnl, int **trmnl_bnr){

    int i;

    *N = get_int(buf, read);
    *E = get_int(buf, read);

    *elist = (edge_t*)e_malloc(*E+1, sizeof(edge_t), "elist");
    get_edge(buf, read, *E, *elist);

    *alist = (node_t*)e_malloc(*N+1, sizeof(node_t), "alist");
    mk_alist(*N, *E, *elist, *alist);

    *T = get_int(buf, read);

    *trmnl = (int*)e_malloc(*T+1, sizeof(int), "trmnl");
    get_array(buf, read, *T, *trmnl);

    *trmnl_bnr = (int*)e_malloc(*N+1, sizeof(int), "trmnl_bnr");
    mk_trmnl_bnr(*N, *T, *trmnl, *trmnl_bnr);

}

void show_graph(int N, int E, int T, edge_t *elist, int *trmnl){

    int i;

    fprintf(stderr, "- - - - - - - - - - - - - - - - - - - -\n");

    fprintf(stderr, "%d\n", N);
    fprintf(stderr, "%d\n", E);

    i = 1;
    while(i <= E){
		fprintf(stderr, "%d\t%d\t%f\t%f\t%f\n",
				elist[i].from, elist[i].to, elist[i].orig, elist[i].cent, elist[i].cost);
		i++;
    }

    fprintf(stderr, "%d\n", T);

    i = 1;
    while(i <= T){
		fprintf(stderr, "%d\n", trmnl[i]);
		i++;
    }

    fprintf(stderr, "- - - - - - - - - - - - - - - - - - - -\n");

}
