#include <queue>
#include <utility>
#include <vector>

using namespace std;

void dfs(int s, bool visited[], vector<int> adj[])
{
	if (visited[s]) {
		return;
	};
	visited[s] = true;
	for (auto u : adj[s]) {
		dfs(u, visited, adj);
	}
}

void compute_dfs(int nof_vertices, int nof_edges, int start_vertice,
		 vector<pair<int, int> > edges)
{
	// Create needed structures
	vector<int> adj[nof_vertices + 1];
	bool visited[nof_vertices + 1];
	for (int i = 0; i < nof_vertices + 1; i++)
		visited[i] = false;

	// Add edges to adjacent structure
	for (int j = 0; j < nof_edges; j++) {
		adj[edges[j].first].push_back(edges[j].second);
		adj[edges[j].second].push_back(edges[j].first);
	}
	dfs(start_vertice, visited, adj);
}

void iterate_connected_components(int nof_vertices, int nof_edges,
				  int start_vertice,
				  vector<pair<int, int> > edges)
{
	// Create needed structures
	vector<int> adj[nof_vertices + 1];
	bool visited[nof_vertices + 1];
	for (int i = 0; i < nof_vertices + 1; i++)
		visited[i] = false;

	// Add edges to adjacent structure
	for (int j = 0; j < nof_edges; j++) {
		adj[edges[j].first].push_back(edges[j].second);
		adj[edges[j].second].push_back(edges[j].first);
	}

	int k = start_vertice;
	while (!visited[k]) {
		// Call dfs for first connected component
		dfs(k, visited, adj);

		// Find first unconnected vertice and update start vertice
		for (int i = k; i < nof_vertices + 1; i++) {
			if (!visited[i]) {
				k = i;
				// Do some stuff for each connected component
				break;
			}
		}
	}
}

void bfs(int nof_vertices, int nof_edges, int start_vertice,
	 vector<pair<int, int> > edges)
{
	queue<int> q;
	bool visited[nof_vertices];
	int distance[nof_vertices];
	vector<int> adj[nof_vertices + 1];

	// Add edges to adjacent structure
	for (int j = 0; j < nof_edges; j++) {
		adj[edges[j].first].push_back(edges[j].second);
		adj[edges[j].second].push_back(edges[j].first);
	}
	// Initialize other stuff
	visited[start_vertice] = true;
	distance[start_vertice] = 0;
	q.push(start_vertice);

	while (!q.empty()) {
		int s = q.front();
		q.pop();
		// process node s
		for (auto u : adj[s]) {
			if (visited[u])
				continue;
			visited[u] = true;
			distance[u] = distance[s] + 1;
			q.push(u);
		}
	}
}
