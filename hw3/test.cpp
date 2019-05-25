#include <bits/stdc++.h>
#include "hw3_cpp.h"
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V, E, deg, u, v;

    cin >> V >> E;

    vector<vector<int>> adj(V); // Adjacency List
    vector<vector<int>> mat(V); // Adjacency Matrix

    // Adjacency Matrix must be size V * V
    for(int i = 0; i < V; ++i) mat[i].resize(V);

    for(int i = 0; i < E; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        mat[u][v] = 1;
    }

    vector<int> adjans(V);

    int scc1 = find_scc_with_adj_list(adj, V, E, adjans);

    for(int i = 0; i < scc1; ++i) {
        for(int j = 0; j < V; ++j) {
            if(adjans[j] == i) {
                printf("%d ", j);
            }
        }
        puts("");
    }

    freopen("./output.txt", "w", stdout);

    for(int i = 0; i < adjans.size(); ++i) {
        printf("%d\n", adjans[i]);
    }

    // vector<int> matans(V);
    //
    // int scc2 = find_scc_with_adj_mat(mat, V, E, matans);
    //
    // for(int i = 0; i < scc2; ++i) {
    //     for(int j = 0; j < V; ++j) {
    //         if(matans[j] == i) {
    //             printf("%d ", j);
    //         }
    //     }
    //     puts("");
    // }
    return 0;
}
