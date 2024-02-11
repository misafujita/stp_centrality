/*

mk_gml.c

Last-modified:JST<2024-02-12 00:38:42>

*/

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "emalloc.h"
#include "input.h"

int main(void){

    int   i;
    char  buf[256] = "\0";
    char *read;

    int     N;         // the number of nodes
    int     E;         // the number of edges
    int     T;         // the number of terminals
    edge_t *elist;     // the edge list
    int    *trmnl;     // the terminal list
    int    *trmnl_bnr; // the terminal list (in binary form)

    /*** INPUT ***/
    get_graph(buf, read, &N, &E, &T, &elist, &trmnl, &trmnl_bnr);
    // print_graph(N, E, T, elist, trmnl);


    /*** OUTPUT ***/
    fprintf(stdout, "graph\n[\n");

    /* node information */
    i = 1;
    while(i <= N){
    	fprintf(stdout, "  node\n  [\n");
    	fprintf(stdout, "    id %d\n", i);
    	fprintf(stdout, "    trmnl %d\n", trmnl_bnr[i]);
    	fprintf(stdout, "  ]\n");
	i++;
    }

    /* edge information */
    i = 1;
    while(i <= E){
    	fprintf(stdout, "  edge\n  [\n");
    	fprintf(stdout, "    source %d\n", elist[i].from);
    	fprintf(stdout, "    target %d\n", elist[i].to);
    	fprintf(stdout, "    weight %f\n", elist[i].cost);
    	fprintf(stdout, "  ]\n");
    	i++;
    }

    fprintf(stdout, "]\n");

    return 0;

}
