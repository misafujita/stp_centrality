#ifndef INPUT_H_DEFINE
#define INPUT_H_DEFINE

int  get_int(char buf[], char *read);

void get_array(char buf[], char *read, int low, int *array);

void get_array_dbl(char buf[], char *read, int low, double *array);

void get_edge(char buf[], char *read, int E, edge_t *edge);

void cal_degree(int N, int E, edge_t *elist, int *degree);

void mk_alist(int N, int E, edge_t *elist, node_t *alist);

void mk_trmnl_bnr(int N, int *trmnl, int *trmnl_bnr);

void get_graph(char buf[], char *read, int *N, int *E, int *T, edge_t **elist, node_t **alist, int **trmnl, int **trmnl_bnr);

void show_graph(int N, int E, int T, edge_t *elist, int *trmnl);

#endif
