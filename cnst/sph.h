#ifndef SPH_H_DEFINE
#define SPH_H_DEFINE

void sph(
	int      N,
	int      E,
	int      T,
	edge_t *elist,
	node_t *alist,
	int     *trmnl,
	frag_t *frag,
	int    *parent,
	st_t   *st);

#endif
