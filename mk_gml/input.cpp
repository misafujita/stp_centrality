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

void get_edge(char buf[], char *read, int E, edge_t *edge){

    int i = 1;
    while(i <= E){

	if(fgets(buf, 256, stdin) == NULL){ fprintf(stderr, "get_edge failed\n"); exit(1); }

    	read = strtok(buf, " \t");
	edge[i].from = atoi(read);

    	read = strtok(NULL, " \t");
	edge[i].to = atoi(read);

    	read = strtok(NULL, " \t");
	edge[i].cost = atof(read);

	i++;

    }

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
	       int *N, int *E, int *T, edge_t **elist, int **trmnl, int **trmnl_bnr){

    int i;

    *N = get_int(buf, read);
    *E = get_int(buf, read);

    *elist = (edge_t*)e_malloc(*E+1, sizeof(edge_t), "elist");
    get_edge(buf, read, *E, *elist);

    *T = get_int(buf, read);

    *trmnl = (int*)e_malloc(*T+1, sizeof(int), "trmnl");
    get_array(buf, read, *T, *trmnl);

    *trmnl_bnr = (int*)e_malloc(*N+1, sizeof(int), "trmnl_bnr");
    mk_trmnl_bnr(*N, *T, *trmnl, *trmnl_bnr);

}

void print_graph(int N, int E, int T, edge_t *elist, int *trmnl){

    int i;

    fprintf(stderr, "- - - - - - - - - - - - - - - - - - - -\n");

    fprintf(stderr, "%d\n", N);
    fprintf(stderr, "%d\n", E);

    i = 1;
    while(i <= E){
	fprintf(stderr, "%d %d %d\n", elist[i].from, elist[i].to, (int)elist[i].cost);
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
