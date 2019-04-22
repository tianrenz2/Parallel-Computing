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

	int l = 0;
	int r = N-1;
	int m = (l+r) / 2;
// INPUT: ARRAY, START INDEX, RIGHT INDEX	
	mergeSort(A, l, r);
}

void 
mergeSort(keytype* A, int l, int r)
{
// splits into two arrays and mergesorts them; no need to fix
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
// to implement: 
// 1. splitting array B in half
// 2. splitting array C according to v from B
// 3. merge the two arrays (B[l:m] and C[l:k], B[m:r] and C[k:r])
// 4. implement parallelism
	// given an array, split into two arrays using m as the dividing factor
	/* for parallel merge */
	int v = (m-l+1)/2;
	int k = binSearch(/*start of C*/ m, /*end of C*/ r, /*target*/ A[v]);
	/* end parallel merge section */

// POPULATING THE LEFT AND RIGHT ARRAYS
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

// MERGING THE TWO ARRAYS IN PLACE
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
