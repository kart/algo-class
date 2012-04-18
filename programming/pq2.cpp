/*
 * Copyright (c) [2012] [Karthik Krishnamurthy]
 * 
 * Input file: http://spark-public.s3.amazonaws.com/algo1/programming_prob/QuickSort.txt
 *
 * Problem description: The file contains 10,000 integers between 1 and 10,000 (including both) in some random order (no integer 
 * 			is repeated). Your task is to compute the total number of comparisons used to sort the given input file
 *			by QuickSort. Two things to keep in mind:
 *			1. You should not count comparisons one-by-one. Rather, when there is a recursive call on a subarray of
 *			   length m, you should simply add m−1 to your running total of comparisons. (This is because the pivot
 *			   element will be compared to each of the other m−1 elements in the subarray in this recursive call).
 *			2. You will explore 3 different methods for choosing the pivot.
 *			   (a) Use the first element of the array as the pivot element
 *			   (b) Use the last element of the array as the pivot element
 *			   (c) Use the median of the 1st, middle and last elements as the pivot element.
 *
 * Build command: g++ -O3 -o pq2 pq2.cpp
 */

#include <iostream>
#include <cassert>
#include <string.h>

using namespace std;

#define MAX 100000

int array[MAX], comparisons = 0;
int copy_array[MAX];

#define SWAP(ARRAY, I, J)				\
{							\
	int		temp;				\
							\
	temp = ARRAY[I];				\
	ARRAY[I] = ARRAY[J];				\
	ARRAY[J] = temp;				\
}

int		find_median(int array[], int start, int mid_idx, int end)
{
	int			a = array[start], b = array[mid_idx], c = array[end];

	if (a < b)
	{
		if (b < c)
			return mid_idx;
		if (c > a)
			return end;
		return start;
	} else
	{
		if (c < b)
			return mid_idx;
		if (c < a)
			return end;
		return start;
	}
}

/* Method 1 : First element is the pivot */
void	preprocess1(int array[], int start, int end)
{
	return;
}

/* Method 2 : Last element is the pivot. So, swap it with the first */
void	preprocess2(int array[], int start, int end)
{
	SWAP(array, start, end);
}

/* Method 3 : Median of 1st, middle and last elements is the pivot. So, swap it with the first */
void	preprocess3(int array[], int start, int end)
{
	int			n = end - start + 1, mid_idx, median_idx;

	assert(n > 1);
	if (n > 2)
	{
		mid_idx = start + (n % 2 == 0 ? n / 2 - 1 : n / 2);
		median_idx = find_median(array, start, mid_idx, end);
		SWAP(array, start, median_idx);
	} else if (array[start] > array[end])
			SWAP(array, start, end);
	return;
}

int partition(int array[], int start, int end)
{
	int		pivot;
	int		i, j;

	pivot = array[start];
	i = j = start;
	while (j < end)
	{
		j++;
		assert(i < j);
		if (array[j] > pivot)
			continue;
		assert(i + 1 <= j);
		assert((array[i + 1] > array[j]) || (i + 1 == j));
		SWAP(array, i + 1, j);
		i++;
	}
	assert(array[i] <= pivot);
	SWAP(array, i, start);
	assert(pivot == array[i]);
	return i;
}

void qsort(int array[], int start, int end, void (*preprocess)(int *, int, int))
{
	int		pivot_idx;

	if (start >= end)
		return;
	(*preprocess)(array, start, end);
	comparisons += (end - start + 1) - 1;
	pivot_idx = partition(array, start, end);
	qsort(array, start, pivot_idx - 1, preprocess);
	qsort(array, pivot_idx + 1, end, preprocess);
}

void test_method(void (*preprocess)(int *, int, int), int end, const char *method)
{
	comparisons = 0;
	memcpy(copy_array, array, MAX * sizeof(int));
	qsort(copy_array, 0, end, preprocess);
	cout << method << comparisons << " comparisons." << endl;
}

int main()
{
	int			val, end = 0;

	while (cin >> val)
		array[end++] = val;
	end--;
	test_method(&preprocess1, end, "First element as pivot : ");
	test_method(&preprocess2, end, "Last element as pivot  : ");
	test_method(&preprocess3, end, "Median of 3 as pivot   : ");
	return 0;
}
