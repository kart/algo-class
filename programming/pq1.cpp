/*
 * Copyright (c) [2012] [Karthik Krishnamurthy]
 * 
 * Input file: http://spark-public.s3.amazonaws.com/algo1/programming_prob/IntegerArray.txt
 *
 * Problem description: The file contains 100,000 integers between 1 and 100,000 (including both) in some random order (no integer 
 * 			is repeated. Your task is to find the number of inversions in the given input. The ith row of the file
 *			is the ith entry of your unsorted array.
 *
 * Build command: g++ -O3 -o pq1 pq1.cpp
 */

#include <iostream>
#include <vector>

using namespace std;

long long inversions;

vector<int> merge_lists(vector<int> subarray1, vector<int> subarray2)
{
	vector<int>		result;
	unsigned int	i, j;

	i = j = 0;
	while (true)
	{
		if (i == subarray1.size() || j == subarray2.size())
			break;
		if (subarray1[i] < subarray2[j])
			result.push_back(subarray1[i++]);
		else
		{
			result.push_back(subarray2[j++]);
			inversions += (subarray1.size() - i);
		}
	}
	while (i < subarray1.size())
		result.push_back(subarray1[i++]);
	while (j < subarray2.size())
		result.push_back(subarray2[j++]);
	return result;
}

vector<int> merge_sort(vector<int> array)
{
	vector<int> left, right;
	int			mid;

	if (array.size() == 1)
		return array;
	mid = array.size() / 2;
	for (int i = 0; i < mid; i++)
		left.push_back(array[i]);
	for (int i = mid; i < (int)array.size(); i++)
		right.push_back(array[i]);
	return merge_lists(merge_sort(left), merge_sort(right));
}

int main()
{
	int			val;
	vector<int>		array, sorted_array;

	while (cin >> val)
		array.push_back(val);
	sorted_array = merge_sort(array);
	cout << "Total number of inversions = " << inversions << endl;
	return 0;
}
