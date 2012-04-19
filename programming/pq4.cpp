/*
 * Copyright (c) [2012] [Karthik Krishnamurthy]
 * 
 * Input file:		http://spark-public.s3.amazonaws.com/algo1/programming_prob/SCC.txt
 * Zipped Version:	http://spark-public.s3.amazonaws.com/algo1/programming_prob/SCC.zip
 *
 * Problem description: The file contains the edges of a directed graph. Vertices are labeled as positive integers from
 * 			1 to 875714. Every row indicates an edge, the vertex label in first column is the tail and the
 *			vertex label in second column is the head (recall the graph is directed, and the edges are directed
 * 			from the first column vertex to the second column vertex).
 *			Your task is to code up the algorithm from the video lectures for computing strongly connected
 *			components (SCCs), and to run this algorithm on the given graph and print the sizes of 5 largest
 *			SCCs in the graph.
 */
#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>

using namespace std;

typedef struct node
{
	vector<int>	forwlist;
	vector<int>	backlist;
} Node;

#define MAX_VERTICES	875715
#define MAX_SCCS_REQ	5

int		f_times[MAX_VERTICES], t;
bool		seen[MAX_VERTICES];
Node		graph[MAX_VERTICES];

void dfs_reverse(int u)
{
	seen[u] = true;

	vector<int> list = graph[u].backlist;
	for (int i = 0; i < list.size(); i++)	
		if (!seen[list[i]])
			dfs_reverse(list[i]);
	t++;
	f_times[t] = u;
}

int dfs_forward(int u)
{
	int		sz = 1;

	seen[u] = false;
	vector<int> list = graph[u].forwlist;
	for (int i = 0; i < list.size(); i++)	
		if (seen[list[i]])
			sz += dfs_forward(list[i]);
	return sz;
}

int main()
{
	int			u, v, i;
	list<int>::iterator	it;
	list<int>		sccs(5, 0);

	while (cin >> u)
	{
		cin >> v;
		graph[u].forwlist.push_back(v);	/* indicates the original graph */
		graph[v].backlist.push_back(u); /* indicates the reverse graph */
	}
	for (i = 1; i < MAX_VERTICES; i++)
	{
		assert(!seen[i] || f_times[t]);
		if (!seen[i])
			dfs_reverse(i);
	}
	/* Instead of memset'ing 'seen' array to false for the next dfs, we can consider u as being un-explored 
	 * if seen[u] is true.
	 */
	for (i = MAX_VERTICES - 1; i >= 1; i--)
	{
		if (seen[f_times[i]])
		{
			int sz = dfs_forward(f_times[i]);
			for (it = sccs.begin(); it != sccs.end(); it++)
				if (*it > sz)
					break;
			sccs.insert(it, sz);
			sccs.erase(sccs.begin());
		}
	}
	for (it = sccs.begin(); it != sccs.end(); it++)
		cout << *it << " ";
	cout << endl;
	return 0;
}
