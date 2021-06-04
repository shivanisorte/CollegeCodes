#include <bits/stdc++.h> 
using namespace std; 
#define V 3

vector<int> djikstra(int graph[V][V],int src) 
{ 

	vector<int> dist(V,INT_MAX);
	dist[src]=0;
	vector<bool> fin(V,false);

	for (int count = 0; count < V-1 ; count++) 
	{ 
		int u = -1; 

		for(int i=0;i<V;i++)
		    if(!fin[i]&&(u==-1||dist[i]<dist[u]))
		        u=i;
		fin[u] = true; 
		
		for (int v = 0; v < V; v++) 

			if (graph[u][v]!=0 && fin[v] == false) 
				dist[v] = min(dist[v],dist[u]+graph[u][v]); 
	} 
    return dist;
} 

int main() 
{ 
	int graph[V][V] = { { 0, 5, 3}, 
						{ 5, 0, 1}, 
						{ 3, 1, 0 },}; 
						
						//src =  1 
						// output: dist[] = {4,0,1}

	for(int x: djikstra(graph,1)){
	    cout<<x<<" ";
	} 

	return 0; 
} 
