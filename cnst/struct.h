#ifndef STRUCT_H_DEFINE
#define STRUCT_H_DEFINE

/* edge list */
struct edge{
	int    from;
	int    to;
	double orig;
	double cent;
	double cost;
}; typedef struct edge edge_t;

/* adjacency list */
struct node{
	int     degree;
	int    *to;
	double *cost;
	int     empty;
}; typedef struct node node_t;

/* tree */
struct st{
	int    *node;
	double  cost;
	double  orig;
	edge_t *elist;
	int     E;
}; typedef struct st st_t;

/* heap */
struct heap{
	double value;
	int    index;
}; typedef struct heap heap_t;

/* frag */
struct frag{
	int *a;
	int *b;
}; typedef struct frag frag_t;

/* option */
struct option{
	char   cnst[16];
	char   cent[16];
	double alpha;
}; typedef struct option option_t;

#endif
