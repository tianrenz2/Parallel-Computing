/**
 *  \file mergesort.cc
 *
 *  \brief Implement your mergesort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "sort.hh"

void
mySort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
	int l = 0;
	int r = N-1;
	int m = (l+r) / 2;
	
	mergeSort(A, l, r);
}

void 
mergeSort(keytype* A, int l, int r)
{
	int m = (r+l)/2;
	if (l<r) {
		mergeSort(A, l, m);
		mergeSort(A, m+1, r);
		merge(A, l, m, r);
	}
}

void 
merge(keytype* A, int l, int m, int r) 
{
	int l_idx = m-l+1;
	int r_idx = r-m; 
	int L[l_idx];
	int R[r_idx];

	for (int i=0; i<l_idx; i++) {
		L[i] = A[i+l];
	}

	for (int i=0; i<r_idx; i++) {
		R[i] = A[i+m+1];
	}

	int x=0;
	int y=0;
	int z=l;

	while(x<l_idx && y<r_idx) {
		if (L[x]<=R[y]) {
			A[z] = L[x];
			x++;
		} else {
			A[z] = R[y];
			y++;
		}

		z++;
	}

	while(x<l_idx) {
		A[z] = L[x];
		z++;
		x++;
	}

	while(y<r_idx) {
		A[z] = R[y];
		z++;
		y++;
	}
	
}

/* eof */
