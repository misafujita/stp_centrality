/*

swap.c

*/

#include <stdio.h>
#include <stdlib.h>

void swap_int(int *a, int *b){

    int temp;

    temp = *a;
    *a   = *b;
    *b   = temp;

}

void swap_dbl(double *a, double *b){

    double temp;

    temp = *a;
    *a   = *b;
    *b   = temp;

}

void quicksort_int(int *array, int begin, int end){

    int    i = begin;
    int    j = end;
    double pivot;

    pivot = array[ ( begin + end ) / 2 ];

    while(1){

		while( array[i] < pivot ){ ++i; }
		while( array[j] > pivot ){ --j; }
		if( i >= j ){ break; }

		swap_int(&array[i], &array[j]);

		i++;
		j--;

    }

    if( begin < i - 1 ){ quicksort_int( array, begin, i-1 ); }
    if( j + 1 < end ){ quicksort_int( array, j+1, end ); }

}

void quicksort_int_dbl(int *array1, double *array2, int begin, int end){

    int    i = begin;
    int    j = end;
    double pivot;

    pivot = array2[ ( begin + end ) / 2 ];

    while(1){

		while( array2[i] < pivot ){ ++i; }
		while( array2[j] > pivot ){ --j; }
		if( i >= j ){ break; }

		swap_int(&array1[i], &array1[j]);
		swap_dbl(&array2[i], &array2[j]);

		i++;
		j--;

    }

    if( begin < i - 1 ){ quicksort_int_dbl( array1, array2, begin, i-1 ); }
    if( j + 1 < end ){ quicksort_int_dbl( array1, array2, j+1, end ); }

}
