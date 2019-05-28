#ifndef HW3CPP_H
#define HW3CPP_H

#include <vector>
using namespace std;
typedef vector<vector<int>> Graph;
// parameters

// adj : adjacent list of graph where the smallest element is the 0th element.
	// in array adj[i], neighbors of the ith vertices are inserted.

// num_v : the number of vertices.

// num_e : the number of edges.

// ans : ans[i] means that ith vertex is included in the ans[i]th strongly connected component.
	// ans[i] should be non-negative integer.
	// if there are multiple answers, please find the lexicoraphically smallest sequence.

// This function should return the number of strongly connnected components.

vector<bool> visited; // check visited
int curr_time; // Checks finish time
vector<int> finished; // Gets vertex that finished at time x
vector<int> cc; // connected components
Graph gph, gphT, scc;

// tranpose of adjacency list
void create_transpose(const Graph& adj) {
	gphT.clear();
	gphT.resize(adj.size());
	for(int u = 0; u < adj.size(); ++u) {
		for(int v : gph[u]) {
			gphT[v].push_back(u);
		}
	}
}

// dfs for adjacency list
void dfs(int v) {
	visited[v] = true;
	for(int next : gph[v]) {
		if(!visited[next]) dfs(next);
	}
	finished[++curr_time] = v;
}

// reverse dfs for adjcency list
void rdfs(int v, vector<int>& cc) {
	cc.push_back(v);
	visited[v] = true;
	for(int next : gphT[v]) {
		if(!visited[next]) rdfs(next, cc);
	}
}

int find_scc_with_adj_list(const Graph& adj, int num_v, int num_e, vector<int>& ans) {
	gph = adj;
	int V = num_v, E = num_e;
	curr_time = 0;

	scc.clear(); // clear answer

	// initializations

	finished.clear();
	finished.resize(V + 1, 0);

	visited.clear();
	visited.resize(V, false);

	// DFS on each vertices that have not been visited
	for(int idx = 0; idx < V; ++idx) {
		if(!visited[idx]) dfs(idx);
	}

	// clear visited array
	visited.clear();
	visited.resize(V, false);

	// Calculate G transpose
	create_transpose(adj);

	// DFS in decreasing order of finish time
	for(int t = V; t >= 1; --t) {
		int curr = finished[t];
		if(!visited[curr]) {
			cc.clear(); // connected component
			rdfs(curr, cc); // reverse dfs
			sort(cc.begin(), cc.end()); // sort each component
			scc.push_back(cc);
		}
	}

	sort(scc.begin(), scc.end()); // sort the components
	for(int i = 0; i < scc.size(); ++i) {
		vector<int> cc = scc[i];
		for(int curr : cc) {
			ans[curr] = i; // set ans array
		}
	}
	return scc.size(); // return number of sccs
}

// dfs for adjacency matrix
void dfs_mat(int v) {
	visited[v] = true;
	for(int i = 0; i < gph[v].size(); ++i) {
		if(gph[v][i] && !visited[i]) dfs_mat(i);
	}
	finished[++curr_time] = v;
}

// reverse dfs for adjaceny matrix
void rdfs_mat(int v, vector<int>& cc) {
	cc.push_back(v);
	visited[v] = true;
	for(int i = 0; i < gphT[v].size(); ++i) {
		if(gphT[v][i] && !visited[i]) rdfs_mat(i, cc);
	}
}

// matrix transpose
void create_transpose_mat(const Graph& adj) {
	gphT.clear();
	int V = adj.size();
	gphT.resize(V);
	for(int i = 0; i < V; ++i) {
		for(int j = 0; j < V; ++j) {
			gphT[i].push_back(gph[j][i]);
		}
	}
}

//adj : num_v x num_v dimension adjacency matrix of the given graph

//the other parameters have same as above function.

int find_scc_with_adj_mat(const Graph& adj, int num_v, int num_e, vector<int>& ans) {
	gph = adj;
	int V = num_v, E = num_e;
	curr_time = 0;

	scc.clear(); // clear answer

	// initializations

	finished.clear();
	finished.resize(V + 1, 0);

	visited.clear();
	visited.resize(V, false);

	// DFS on each vertices that have not been visited
	for(int idx = 0; idx < V; ++idx) {
		if(!visited[idx]) dfs_mat(idx);
	}

	// clear visited array
	visited.clear();
	visited.resize(V, false);

	// Calculate G transpose
	create_transpose_mat(adj);

	// DFS in decreasing order of finish time
	for(int t = V; t >= 1; --t) {
		int curr = finished[t];
		if(!visited[curr]) {
			cc.clear(); // connected component
			rdfs_mat(curr, cc);
			sort(cc.begin(), cc.end()); // sort each component
			scc.push_back(cc);
		}
	}

	sort(scc.begin(), scc.end()); // sort the components
	for(int i = 0; i < scc.size(); ++i) {
		vector<int> cc = scc[i];
		for(int curr : cc) {
			ans[curr] = i; // set ans array
		}
	}
	return scc.size(); // return number of sccs
}


#endif
