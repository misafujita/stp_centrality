#ifndef BINARYHEAP_H_DEFINE
#define BINARYHEAP_H_DEFINE

void min_inqueue(
	heap_t*,
	int    *heap_empty,
	double value,
	int    index);

void min_inqueue_overrap(
	heap_t*,
	int    heap_overrap,
	double value);

void min_dequeue(
	heap_t*,
	int *heap_empty);

#endif
