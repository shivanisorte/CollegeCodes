#include <bits/stdc++.h> 
using namespace std; 
#define V 5


// INT_MAX -  inifinite (in C++) 

int primMST (int graph[V][V]) 
{ 
    
    // 2 sets: 1-included in MST, 1-not included yet
    
	int key[V]; int res=0; 
	fill(key,key+V,INT_MAX); //key array initialized as infinite
	bool mSet[V] = {false}; //boolean array of size V, vertex as indices
	key[0] = 0; //setting first vertex as zero

	for (int count = 0; count < V ; count++)  //theta(V)
	{ 
		int u = -1; 

		for (int i=0; i<V; i++)
		    if (!mSet[i] && (u==-1 || key[i]<key[u])) 
		        u = i; //index 1 min value key
	
		mSet[u] = true; //added to mst
		res += key[u]; //updating the resultant mstcost


		for (int v = 0; v < V; v++) //theta(V)

			if (graph[u][v] !=0 && mSet[v] == false) 
				key[v] = min(key[v],graph[u][v]); //updating key array
	} 
    return res;
} 

int main() 
{ 
    //undirected connected weighted graph
	int graph[V][V] = { { 0, 2, 0, 6, 0}, 
						{ 2, 0, 3, 8, 5}, 
						{ 0, 3, 0, 0, 7}, 
						{ 6, 8, 0, 0, 9}, 
						{ 0, 5, 7, 9, 0},}; //5x5 matrix
						

	cout<<"Min spanning tree cost is : "<< primMST(graph); 
	//output should be 16 
	// 0-1, 0-3, 1-4, 1-2
	// 2  +  6  + 5  + 3  =  16
	
	return 0; 
} 
  