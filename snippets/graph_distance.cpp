////////////// Dijkstra's algorithm ///////////////
// In directed graph with non-negative weights, return distances from one node to all other nodes
// Pseudocode:
// Build adjancecy list from edges.
// distances[] = INT_MAX;
// priority_queue pq
// pq push startNode
// while pq not empty:
//     u = pq extract min
//     if visited u:
//         continue
//     add u to visited
//     for all u neighbours that have not been visited
//          add to pq
//          distances[neighbour] = min(distances[neighbour], distanceHere + edge)
void dijkstra(int src, vector<vector<int>>& adj) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(adj.size(), INF);
    vector<int> visited(adj.size(), false);

    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;

        // Iterate through all adjacent vertices of the current vertex
        for (auto &neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // If a shorter path to v is found
            if (!visited[v] && dist[v] > dist[u] + weight) {
                // Update distance and push new distance to the priority queue
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    // Stored in dist
}



///////////// Bellman Ford algorithm ////////////
// From source vertex in directed graph (with negative values), find shortest path to all nodes
// Report a negative cycle
// Pseudocode:
// function BellmanFord(list vertices, list edges, vertex source, distance[], parent[]) 
// Step 1 – initialize the graph. In the beginning, all vertices weight of
// INFINITY and a null parent, except for the source, where the weight is 0 for each vertex v in vertices    
// distance[v] = INFINITY    
// parent[v] = NULL distance[source] = 0
// Step 2 – relax edges repeatedly    
// for i = 1 to V-1    // V – number of vertices        
// for each edge (u, v) with weight w        
//     if (distance[u] + w) is less than distance[v]        
//             distance[v] = distance[u] + w         
//             parent[v] = u 
// Step 3 – check for negative-weight cyclesfor each edge (u, v) with weight w    
// if (distance[u] + w) is less than distance[v]    
//     return “Graph contains a negative-weight cycle” 
// return distance[], parent[]