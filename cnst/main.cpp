/*

cnst.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "emalloc.h"
#include "mersenne.h"
#include "swap.h"
#include "input.h"
#include "kruskal.h"
#include "dnh.h"
#include "sph.h"
#include "adh.h"

#define MAX 999999

void show_help(){

    fprintf(stderr, "[--cnst]: the name of the construction method\n");
    fprintf(stderr, "[--cent]: the name of the network centrality\n");
    fprintf(stderr, "    [-a]: the balancing parameter between the original cost and the network centrality\n");
    exit(1);

}

void get_option(int argc, char *argv[], option_t *option){

    int i = 0;
    while(i < argc){
    	if(!strcmp(argv[i],"--cnst") && i+1 <argc){ strcpy(option->cnst, argv[i+1]); }
    	if(!strcmp(argv[i],"--cent") && i+1 <argc){ strcpy(option->cent, argv[i+1]); }
    	if(!strcmp(argv[i],"-a") && i+1 <argc){     option->alpha = atof(argv[i+1]); }
    	if(!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")){ show_help(); }
		i++;
    }

}

void show_option(option_t option){

    fprintf(stderr, "cnst  = %s\n", option.cnst);
    fprintf(stderr, "cent  = %s\n", option.cent);
    fprintf(stderr, "alpha = %f\n\n", option.alpha);

}

void get_array_dbl_fp(char buf[], char *read, int low, double *array, FILE *fp, const char *fn){

    fp = fopen(fn, "r");

    int i = 1;
    while(i <= low){

		if(fgets(buf, 256, fp) == NULL){ fprintf(stderr, "get_array_dbl_fp failed\n"); exit(1); }

    	read = strtok(buf, " \t");
		array[i] = atof(read);

		i++;

    }

    fclose(fp);

}

void print_array_dbl(int low, double *array){

    int i = 1;
    while(i <= low){
		fprintf(stderr, "%f\n", array[i]);
		i++;
    }

}

void quicksort_rnd(edge_t *elist, double *array, int begin, int end){

    int    i = begin;
    int    j = end;
    double pivot;

    pivot = array[ ( begin + end ) / 2 ];

    while(1){

		while( array[i] < pivot ){ ++i; }
		while( array[j] > pivot ){ --j; }
		if( i >= j ){ break; }

		swap_int(&elist[i].from, &elist[j].from);
		swap_int(&elist[i].to, &elist[j].to);
		swap_dbl(&elist[i].orig, &elist[j].orig);
		swap_dbl(&elist[i].cost, &elist[j].cost);
		swap_dbl(&array[i], &array[j]);

		i++;
		j--;

    }

    if( begin < i - 1 ){ quicksort_rnd( elist, array, begin, i-1 ); }
    if( j + 1 < end ){ quicksort_rnd( elist, array, j+1, end ); }

}

void trns_cent(int N, int E, edge_t *elist, double *vcent, double *ecent){

    int i = 1;

    while(i <= E){
		ecent[i] = (vcent[ elist[i].from ] + vcent[ elist[i].to ]) / 2.0;
		i++;
    }

}

void trns_cost(int E, edge_t *elist, double alpha){

    int i = 1;
    double max_orig = 0;
    double max_cent = 0;

    i = 1;
    while(i <= E){
    	if(max_orig < elist[i].orig){ max_orig = elist[i].orig; }
    	if(max_cent < elist[i].cent){ max_cent = elist[i].cent; }
    	i++;
    }

    i = 1;
    while(i <= E){
		elist[i].cost = (elist[i].orig / max_orig) * alpha + (elist[i].cent / max_cent) * (1.0 - alpha);
		i++;
    }

}

void rnd_edge(int E, edge_t *elist){

    int     i;
    double *array;

    array = (double*)e_malloc(E+1, sizeof(double), "array");

    i = 1;
    while(i <= E){
		array[i] = genrand_real1();
		i++;
    }

    quicksort_rnd(elist, array, 1, E);

    free(array);

}


int main(int argc, char *argv[]){

    int   i;
    char  buf[256] = "\0";
    char *read;
    FILE *fp;
    char  fn[1024] = "\0";
    option_t option;

    int     N;
    int     E;
    int     T;
    edge_t *elist;
    node_t *alist;
    int    *trmnl;
    int    *trmnl_bnr;

    double *vcent;
    double *ecent;

    char    cnst[8];
    frag_t  frag;
    st_t    st;
    int    *parent;


    /*** INPUT ***/
    get_option(argc, argv, &option);

    get_graph(buf, read, &N, &E, &T, &elist, &alist, &trmnl, &trmnl_bnr);

    ecent = (double*)e_malloc(E+1, sizeof(double), "ecent");
    sprintf(fn, "%s.dat", option.cent);

    if(!strncmp(option.cent, "v", 1)){

		vcent = (double*)e_malloc(N+1, sizeof(double), "vcent");
    	get_array_dbl_fp(buf, read, N, vcent, fp, fn);
		trns_cent(N, E, elist, vcent, ecent);

    }else if(!strncmp(option.cent, "e", 1)){

    	get_array_dbl_fp(buf, read, E, ecent, fp, fn);

    }else{

    	fprintf(stderr, "error: %s centrality is not implemented\n", option.cent);

    }

    i = 1;
    while(i <= E){
		if(ecent[i] > 0){
			elist[i].cent = 1 / ecent[i];
		}else{
			elist[i].cent = 1.0;
		}
		i++;
    }

    trns_cost(E, elist, option.alpha);

    mk_alist(N, E, elist, alist);


    /*** PRE-PROCESSING ***/
    init_genrand( getpid() );

    st.node  = (int*)e_malloc(N+1, sizeof(int), "cur.node");
    st.elist = (edge_t*)e_malloc(N+1, sizeof(edge_t), "cur.elist");
    frag.a   = (int*)e_malloc(N+1, sizeof(int), "frag.a");
    frag.b   = (int*)e_malloc(N+1, sizeof(int), "frag.b");

    rnd_edge(E, elist);
    quicksort_edge(elist, 1, E);


    /*** HEURISTOCS ***/
    parent = (int*)e_malloc(N+1, sizeof(int), "parent");

    if(!strcmp(option.cnst, "sph")){
    	sph(N, E, T, elist, alist, trmnl, &frag, parent, &st);
    }else if(!strcmp(option.cnst, "dnh")){
    	dnh(N, E, T, elist, alist, trmnl, &frag, parent, &st);
    }else if(!strcmp(option.cnst, "adh")){
    	adh(N, E, T, elist, alist, trmnl, &frag, parent, &st);
    }else{
    	fprintf(stderr, "error: %s method is not implemented\n", cnst);
    	exit(1);
    }

    fprintf(stdout, "%f\n", st.orig);


    return 0;

}
