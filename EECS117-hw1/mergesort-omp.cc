/**
 *  \file mergesort.cc
 *
 *  \brief Implement your mergesort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>

#include "sort.hh"

static keytype* B;
void
mySort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
  //keytype* B = newKeys(N);
  assert(B!=NULL);
  pMergeSort(A, 0, N - 1, B, 0);
}

void pMergeSort(keytype* A, int start1, int end1, keytype* B, int start2)
{
  /*
  Todo: This function takes a part(start1, end1) of array A, keep
  splitting the partitions until the base case(size of the partition is 1)
  */
  assert(B != NULL);
  int l = end1 - start1 + 1;

  if (l == 1) {
    B[start2] = A[start1];
  }
  else{
    keytype* T;
    
    int mid1 = (start1 + end1) / 2;
    int l_mid = mid1 - start1 + 1;
    
    #pragma omp parallel 
    {
    std::cout << "able to do the parallel mergesort" << std::endl;
    pMergeSort(A, start1, mid1, T, 1);
    }
    pMergeSort(A, mid1 + 1, end1, T, l_mid + 1);
    pMerge(T, 1, l_mid, l_mid + 1, l, B, start2);
    
  }

  return;
}

void pMerge(keytype* A, int start1, int end1, int start2, int end2, keytype* T, int start3){
  /*
  Todo: This function merge the sorted parts (start1, end1) and (start2, end2) in array A,
  store the merged result in array T from the index start3
  */
  int l1 = end1 - start1 + 1;
  int l2 = end2 - start2 + 1;
 
  if(l1 < l2){
    swap(&l1, &l2);
    swap(&start1, &start2);
    swap(&end1, &end2);
  }
  if(l1 == 0)
    return;
  else{
    
    int mid1 = (start1 + end1) / 2;
    int mid2 = binarySearch(A[mid1], A, start2, end2);
    int mid3 = start3 + (mid1 - start1) + (mid2 - start2);
    T[mid3] = A[mid1];
    pMerge(A, start1, mid1 - 1, start2, mid2 - 1, T, start3);
    pMerge(A, mid1 + 1, end1, mid2, end2, T, mid3 + 1);
  }
  return;
}

void swap(int *x, int *y){
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

int binarySearch(keytype target, keytype* A, int start, int end)
{
  /*
  Todo: This function return s the position of the
  target(or the first element smaller than target)
   in range(start, end) in array A,
  */

  std::cout << "start: " << start << std::endl;
  std::cout << "end: " << end << std::endl;
  if (start < end) {
    int m = (start+end)/2;
    if (A[m] == target) 
      return m;
    if (A[m] > target)
      return binarySearch(target, A, start, m);
    return binarySearch(target, A, m+1, end);
  }

  return std::min(start, end);
}

/* eof */
