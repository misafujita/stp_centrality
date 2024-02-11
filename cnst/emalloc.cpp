/*

emalloc.c

*/

#include <stdio.h>
#include <stdlib.h>

void *e_malloc(int num, int size, const char* p){

    void *o;
    o = (void*)malloc(size * num);

    if(o == NULL){ fprintf(stderr, "e_malloc failed: %s.\n", p); exit(1); }

    return (void*)o;
}

void *e_calloc(int num, int size, const char* p){

    void *o;
    o = (void*)calloc(num, size);

    if(o == NULL){ fprintf(stderr, "e_calloc failed: %s.\n", p); exit(1); }

    return (void*)o;
}
