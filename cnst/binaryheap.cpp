/*

binaryheap.c

*/

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "swap.h"

void min_inqueue(heap_t *heap, int *heap_empty, double value, int index){

    int t;
    int heap_new;

    heap[ *heap_empty ].value = value;
    heap[ *heap_empty ].index = index;

    heap_new     = *heap_empty;
    *heap_empty += 1;

    t = 1;
    while(t <= *heap_empty){

		if(heap[ heap_new ].value < heap[ (int)heap_new/2 ].value){

			swap_dbl(&heap[ heap_new ].value, &heap[ (int)heap_new/2 ].value);
			swap_int(&heap[ heap_new ].index, &heap[ (int)heap_new/2 ].index);

			heap_new = (int)heap_new/2;

			if(heap_new == 1){ break; }

		}

		t++;

    }

}

void min_inqueue_overrap(heap_t *heap, int heap_overrap, double value){

    int t;
    int heap_new;

    heap[ heap_overrap ].value = value;

    heap_new = heap_overrap;

    t = 1;
    while(t <= heap_overrap){

		if(heap[ heap_new ].value < heap[ (int)heap_new/2 ].value){

			swap_dbl(&heap[ heap_new ].value, &heap[ (int)heap_new/2 ].value);
			swap_int(&heap[ heap_new ].index, &heap[ (int)heap_new/2 ].index);

			heap_new = (int)heap_new/2;

			if(heap_new == 1){ break; }

		}

		t++;

    }

}

void min_dequeue(heap_t *heap, int *heap_empty){

    int t;
    int heap_new;
    int heap_child;

    *heap_empty -= 1;
    heap[ 1 ].value = heap[ *heap_empty ].value;
    heap[ 1 ].index = heap[ *heap_empty ].index;
    heap[ *heap_empty ].value = 0;
    heap[ *heap_empty ].index = 0;

    heap_new = 1;

    t = 1;
    while(t <= *heap_empty){

		if(heap_new*2 >= *heap_empty){ break; }

		if( (heap_new*2)+1 >= *heap_empty){
			heap_child = heap_new*2;
		}else if(heap[ heap_new*2 ].value < heap[ (heap_new*2)+1 ].value){
			heap_child = heap_new*2;
		}else{
			heap_child = (heap_new*2)+1;
		}

		if(heap[ heap_new ].value > heap[ heap_child ].value){

			swap_dbl(&heap[ heap_new ].value, &heap[ heap_child ].value);
			swap_int(&heap[ heap_new ].index, &heap[ heap_child ].index);

			heap_new = heap_child;

		}

		t++;

    }

}
