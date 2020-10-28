// Program to find Dijkstra's shortest path using 
// priority_queue in STL 
#include<bits/stdc++.h> 
using namespace std; 
# define INF 0x3f3f3f3f 
typedef pair<int, int> iPair; 
void addEdge(vector <pair<int, int>> adj[], int u, int v, int wt){
	adj[u].push_back(make_pair(v, wt));
}
void dij(vector<pair<int, int>> adj[], int V, int s){
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
	vector<int> dist(V, INF);
	dist[s] = 0;
	pq.push(make_pair(0, s));
	while(!pq.empty()){
		pair<int, int> p = pq.top();
		pq.pop();
		int u = p.second;
		for(auto x : adj[u])
		{	
			int v = x.first;
			int weight = x.second;
			if(dist[u] + weight < dist[v])
			{	dist[v] = weight + dist[u];
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	for (int i = 0; i < V; ++i) 
		printf("%d \t\t %d\n", i, dist[i]); 
}
bool dfsrec(vector<pair<int, int>> adj[], int s, int V, vector<bool>& visited, stack<int>& st)
{
	for(auto x : adj[s]){
		if(!visited[x.first]){
			visited[x.first] = true;
			dfsrec(adj, x.first, V, visited, st);
			st.push(x.first);
		}
	}
}

bool dfsrec(vector<int> radj[], int s, int V, vector<bool>& visited, vector<int>& res)
{
	for(auto x : radj[s]){
		if(visited[x] == true){
			visited[x] = false;
			dfsrec(radj, x, V, visited, res);
			res.push_back(x);
		}
	}
}
void show(vector<int> v){
	cout << endl;
	for(auto x : v){
		cout << x << " ";
	}
	cout << endl;
}
void scc(vector<pair<int, int>> adj[], int V){
	vector<int> radj[V];
	for(int i = 0; i < V; i++){
		for(auto x : adj[i]){
			radj[x.first].push_back(i);
		}
	}
	stack<int> s;
	vector<bool> visited(V, false);
	for(int i = 0; i < V; i++){
		if(!visited[i])
		{
			visited[i] = true;
			dfsrec(adj, i, V, visited, s);
			s.push(i);	
		}
	}
	vector<int> res;
	cout << "\nSCC of given graphs are \n";
	while(!s.empty()){
		int u = s.top();
		s.pop();
		if(visited[u] == true){
			visited[u] = false;
			res.push_back(u);
			dfsrec(radj, u, V, visited,  res);
			show(res);
		}
		res.clear();
	}
}
void prim(vector<pair<int, int>> adj[], int V){
	vector<bool> visited(V, false);
	visited[0] = true;
	vector<pair<int, int>> res;
	int c = 1;
	pair<int, pair<int, int>> min = {INT_MAX, {-1, -1}};
	while(c < V){
		min.first = INT_MAX;
		for(int u = 0; u < V; u++)
		{
			if(visited[u])
			{
				for(auto x : adj[u]){
					if(!visited[x.first]){
						if(x.second < min.first)
						{
							min.first = x.second;
							min.second.first = u;
							min.second.second = x.first;
						}
					}
				}
			}
		}
		visited[min.second.second] = true;
		res.push_back({min.second.first, min.second.second});
		c++;
	}
	cout << endl;
	for(auto x : res){
		cout << x.first << "------" << x.second << endl;
	}
}
void dfsutil(bool& ans, vector<pair<int, int>> adj[], int s, vector<bool> visited){
	for(auto x : adj[s]){
		if(visited[x.first])
		{
			ans = true;
			return;
		}
		else
		{
			visited[x.first] = true;
			dfsutil(ans, adj,  x.first, visited);
		}
	}
}
bool cycle(vector<pair<int, int>> adj[], int V){
	bool ans = false;
	for(int u = 0; u < V; u++){
		vector<bool> visited(V, false);
		visited[u] = true;
		dfsutil(ans, adj, u, visited);
		if(ans)
			return true;
	}
	return false;
}
int main() 
{ 
	int V = 6; 
	vector<pair<int, int>> adj[V];

	addEdge(adj, 0, 1, 2);
	addEdge(adj, 1, 2, 5);
	addEdge(adj, 2, 3, 1);
	addEdge(adj, 3, 4, 4);
	addEdge(adj, 4, 5, 1); 
	/*addEdge(adj, 5, 4, 4);
	addEdge(adj, 3, 1, 2);
	addEdge(adj, 4, 1, 4);	
	*/cout << endl;
	//dij(adj, V, 0);
	//prim(adj, V);
	//scc(adj, V);
	cout << cycle(adj, V);
	return 0; 
} 
