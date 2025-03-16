#include "dijkstras.h"
#include <iostream>
#include <queue>
#include <vector>

vector<int> dijkstra_shortest_path(const Graph &G, int source,
                                   vector<int> &previous) {
  vector<int> d(G.numVertices, INF);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

  d[source] = 0;
  pq.push({0, source});
  previous.assign(G.numVertices, -1);

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    for (const Edge &e : G[u]) {
      int v = e.dst;
      int weight = e.weight;

      if (d[u] + weight < d[v]) {
        d[v] = d[u] + weight;
        previous[v] = u;
        pq.push({d[v], v});
      }
    }
  }
  return d;
}

vector<int> extract_shortest_path(const vector<int> &distances,
                                  const vector<int> &previous,
                                  int destination) {
  vector<int> path;
  if (distances[destination] == INF) {
    return path;
  }
  for (int v = destination; v != -1; v = previous[v]) {
    path.insert(path.begin(), v);
  }
  return path;
}

void print_path(const vector<int> &v, int total) {
  for (size_t i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << total;
}
