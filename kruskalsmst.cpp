#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

//structure to define weighted edge
struct Edge{
    int src,dest,weight;

};

//structure to represent a connnected graph
struct Graph{ 
    int V;
    int E;

    struct Edge * edge;
    
};//here graph is an array of edges because we want to sort them on the basis of edges. no other pattern. 

// create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
};

//a structure to represent a subset for union and find
struct subset{
    int parent;
    int rank;

};


//find set of an element
// path compression technique
int find(struct subset subsets[], int i){
    if(subsets[i].parent != i){
        subsets[i].parent = find(subsets,subsets[i].parent);
        
    }
    return subsets[i].parent;
}


//A function that does union of two sets of x and y
void Union(struct subset subsets[],int x,int y){
    int xroot = find(subsets,x);
    int yroot = find(subsets,y);

    //attach smaller rank tree under root of high rank tree
    //union by rank
    if(subsets[xroot].rank < subsets[yroot].rank){
        subsets[xroot].parent = yroot;

    }
    else if(subsets[xroot].rank > subsets[yroot].rank){
        subsets[yroot].parent = xroot;
    }//if ranks are same, then make one as root and increment/
    //its rank by one
    else{
            //ToDo:: 
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++; 
    }
}


int myComp(const void*a, const void*b){  //to sort edges in ascending order
    struct Edge*a1 = (struct Edge*)a;
    struct Edge*b1 = (struct Edge*)b;
    return a1->weight > b1->weight;

}

void KruskalMST(struct Graph* graph){
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge,graph->E,sizeof(graph->edge[0]),myComp);

    struct subset *subsets = (struct subset*) malloc(V * sizeof(struct subset));

    for(int v = 0; v < V;++v){
        subsets[v].parent = v;
        subsets[v].rank = 0;

    }

    while(e< V-1){
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets,next_edge.src);
        int y = find(subsets, next_edge.dest);

        if(x != y){
            result[e++] = next_edge;
            Union(subsets,x,y);
        }
    }

    cout << "Following are the edges in the constructed MST\n";
    for(int i=0;i<e;++i){
            printf("%d -- %d == %d\n",result[i].src,result[i].dest,result[i].weight);
            
        }
    // return;
    return;
    
}


int main(){
    int V = 4;
    int E = 5;
    struct Graph* graph = createGraph(V,E);

    //add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    //add edge 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    //add edge 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    //add edge 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    //add edge 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    KruskalMST(graph);

    return 0;
}