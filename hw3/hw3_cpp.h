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

void create_transpose(const Graph& adj) {
	gphT.clear();
	gphT.resize(adj.size());
	for(int u = 0; u < adj.size(); ++u) {
		for(int v : gph[u]) {
			printf("%d -> %d\n", u, v);
			gphT[v].push_back(u);
		}
	}
}

void dfs(int v) {
	visited[v] = true;
	for(int next : gph[v]) {
		if(!visited[next]) dfs(next);
	}
	finished[++curr_time] = v;
}

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

	finished.clear();
	finished.resize(V + 1, 0);

	visited.clear();
	visited.resize(V, false);


	for(int idx = 0; idx < V; ++idx) {
		if(!visited[idx]) dfs(idx);
	}

	visited.clear();
	visited.resize(V, false);

	create_transpose(adj);

	for(int t = V; t >= 1; --t) {
		int curr = finished[t];
		if(!visited[curr]) {
			cc.clear(); // connected component
			rdfs(curr, cc);
			sort(cc.begin(), cc.end());
			scc.push_back(cc);
		}
	}

	sort(scc.begin(), scc.end());
	// cout << scc.size() << '\n';
	for(int i = 0; i < scc.size(); ++i) {
		vector<int> cc = scc[i];
		for(int curr : cc) {
			ans[curr] = i;
			// cout << curr << ' ';
		}
		// cout << "-1\n";
	}
	return scc.size();
}

//adj : num_v x num_v dimension adjacency matrix of the given graph

//the other parameters have same as above function.

int find_scc_with_adj_mat(const Graph& adj, int num_v, int num_e, vector<int>& ans) {
	return 2;
}


#endif
