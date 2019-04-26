/**
 *  \file mergesort.cc
 *
 *  \brief Implement your mergesort in this file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
// #include <omp.h>
#include <iostream>
#include <math.h>
#include "sort.hh"
using namespace std;
// static keytype* B;
void
mySort (int N, keytype* A)
{
  /* Lucky you, you get to start from scratch */
  keytype *B = newKeys(N);

  // keytype C1[8] = {3, 8, 74 , 2, 9, 5,3};
  pMergeSort(A, 0, N - 1, B, 0);
  // sMerge(B, 0, C1, 0, 3, 4, 7);

  for (int i = 0; i < N; i++) {
    /* code */
    A[i] = B[i];
    // cout<<B[i]<<", ";
  }
  // std::copy(numbers, numbers + 5, values);

}

void pMergeSort(keytype* A, int start1, int end1, keytype* B, int start2)
{
  /*
  Todo: This function takes a part(start1, end1) of array A, keep
  splitting the partitions until the base case(size of the partition is 1)
  */
  assert(B != NULL);
  int l = end1 - start1 + 1;
  // std::cout << start1 <<"," << end1 <<";" << start2 <<std::endl;
  // cout << start1 << "-" << end1 << ":" << start2 << endl;

  if (l <= 1) {
    B[start2] = A[start1];
    return;
  }else{
    keytype* T = newKeys(l);

    int mid1 = (start1 + end1) / 2;
    int l_mid = mid1 - start1;

    pMergeSort(A, start1, mid1, T, 0);
    pMergeSort(A, mid1 + 1, end1, T, l_mid + 1);

    if(l < 1000)
      pMerge(T, 0, l_mid, l_mid + 1, l - 1, B, start2);
    else{
      sMerge(B, start2, T, 0, l_mid, l_mid + 1, l - 1);
    }

  }

  return;
}

void pMerge(keytype* T, int start1, int end1, int start2, int end2, keytype* A, int start3){
  /*
  Todo: This function merge the sorted parts (start1, end1) and (start2, end2) in array A,
  store the merged result in array T from the index start3
  */
  int l1 = end1 - start1 + 1;
  int l2 = end2 - start2 + 1;
  // int temp_l, tem_s, temp_e;
  if(l1 < l2){
    swap(&l1, &l2);
    swap(&start1, &start2);
    swap(&end1, &end2);
  }

  assert(l1 >= l2);
  if(l1 <= 0){
    return;
  }else{
    int mid1 = floor((start1 + end1) / 2);
    int mid2 = binarySearch(T[mid1], T, start2, end2);
    int mid3 = start3 + (mid1 - start1) + (mid2 - start2);
    A[mid3] = T[mid1];
    #pragma omp parallel{
      pMerge(T, start1, mid1 - 1, start2, mid2 - 1, A, start3);
    }
    #pragma omp parallel{
      pMerge(T, mid1 + 1, end1, mid2, end2, A, mid3 + 1);
    }

  }
  return;
}

void swap(int *x, int *y){
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void sMerge(keytype *A, int a_start, keytype *B, int l_start, int l_end, int r_start, int r_end){
  int i = l_start;
  int j = r_start;
  int m = a_start;
  while (i <= l_end && j <= r_end) {
      if(B[i] > B[j]){
        A[m] = B[j];
        j ++;
      }else{
        A[m] = B[i];
        i++;
      }
      m++;
  }

  while(i <= l_end){
    A[m] = B[i];
    i++;
    m++;
  }

  while(j <= r_end){
    A[m] = B[j];
    j++;
    m++;
  }
}

int binarySearch(keytype target, keytype* A, int start, int end)
{
  /*
  Todo: This function return s the position of the
  target(or the first element smaller than target)
   in range(start, end) in array A,
  */
  int low = start;
  int high = std::max(low, end + 1);
  // cout<<"to find "<< target <<", "<<low <<"-"<<high <<endl;

  while(low < high){
    int mid = (low + high) / 2;
    // cout<<"mid "<< mid <<",target "<< A[] <<endl;
    if(target <= A[mid]) {
      high = mid;
      // cout<<"high dec "<< high <<endl;
    }else{
      low = mid + 1;
    }
  }
  return high;
}

/* eof */
