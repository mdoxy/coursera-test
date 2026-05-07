// Parallel BFS and DFS using OpenMP
#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>              // OpenMP header for parallelism

using namespace std;

const int MAX = 100;          // Maximum number of nodes
vector<int> adj[MAX];         // Adjacency list for graph
bool visited[MAX];            // Array to track visited nodes

// ===== PARALLEL BFS =====
void bfs(int start, int n) {
    fill(visited, visited + n, false);   // Reset visited array
    queue<int> q;                        // Queue used in BFS
    visited[start] = true;               // Mark starting node as visited
    q.push(start);                       // Push start node into queue
    cout << "BFS: ";
    while(!q.empty()) {
        int node = q.front();            // Get front node from queue
        q.pop();                         // Remove node from queue
        cout << node << " ";
        // Process neighbors in parallel
        #pragma omp parallel for
        for(int i = 0; i < adj[node].size(); i++) {
            int neighbor = adj[node][i]; // Get adjacent node
            if(!visited[neighbor]) {              // Check if neighbor is not visited
                // Critical section prevents race condition
                #pragma omp critical
                {
                    if(!visited[neighbor]) {
                        visited[neighbor] = true; // Mark neighbor visited
                        q.push(neighbor);         // Push into queue
                    }
                }
            }
        }
    }

    cout << endl;
}
// ===== DFS =====
void dfs(int node) {
    visited[node] = true;                // Mark current node visited
    cout << node << " ";
    for(int i = 0; i < adj[node].size(); i++) {   // Visit all adjacent nodes
        int neighbor = adj[node][i];
        if(!visited[neighbor]) {                // Visit only unvisited nodes
            dfs(neighbor);               // Recursive DFS call
        }
    }
}
int main() {
    int n = 6;                           // Total number of nodes
    adj[0].push_back(1);                 // Create undirected graph
    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(1);
    adj[1].push_back(4);
    adj[4].push_back(1);
    adj[2].push_back(5);
    adj[5].push_back(2);
    bfs(0, n);                    // Perform BFS traversal
    fill(visited, visited + n, false);             // Reset visited array for DFS
    cout << "DFS: ";
    // Perform DFS traversal
    dfs(0);
    cout << endl;
    return 0;
}
/*
Compile:
g++ -fopenmp bfs_dfs.cpp -o bfs_dfs
Run:./bfs_dfs OR bfs_dfs.exe
BFS: 0 1 2 3 4 5
DFS: 0 1 3 4 2 5
*/