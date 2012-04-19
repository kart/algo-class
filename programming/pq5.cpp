/*
 * Copyright (c) [2012] [Karthik Krishnamurthy]
 * 
 * Input file:		http://spark-public.s3.amazonaws.com/algo1/programming_prob/HashInt.txt
 * 
 * Problem description: The file contains 100,000 integers all randomly chosen between 1 and 1,000,000 (there might be
 * 			some repetitions). Here are 9 "target sums", in increasing order: 231552,234756,596873,648219
 *			726312,981237,988331,1277361,1283379.
 *			Your task is to determine, for each of the 9 target sums x, whether or not x can be formed as
 *			the sum of two entries in the given array. Your answer should be in the form of a 9-bit string,
 *			with a 1 indicating "yes" for the corresponding target sum and 0 indicating "no".
 *
 * Note: This was the easiest of all the programming questions present in the entire coursework. It would have been
 * challenging if at least it was required to write your own hash function.
 */

#include <iostream>
#include <map>

using namespace std;

#define N_TARGET_SUMS	9	

map<int, bool> m;

int target_sums[] = {231552,234756,596873,648219,726312,981237,988331,1277361,1283379};

bool sum_exists(int N)
{
	for (map<int, bool>::iterator it = m.begin(); it != m.end(); it++)
		if (m.find(N - (*it).first) != m.end())
			return true;
	return false;
}

int main()
{
	int	n;

	while (cin >> n)
		m[n] = true;
	for (int i = 0; i < N_TARGET_SUMS; i++)
		if (sum_exists(target_sums[i]))
			cout << 1;
		else
			cout << 0;
	cout << endl;
	return 0;
}
