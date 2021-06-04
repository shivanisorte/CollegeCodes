#include <iostream>
using namespace std;
#define infinite 9999;

class Graph {

    public:
    int numberOfNodes;
    int graphAdjMAtrix[20][20]; //not a good way to declare. Good way - Dynamic
    void acceptGraph();
    void displayGraph();
    int calculateDistance();
};

void Graph :: acceptGraph() {  //taking input in the form of matrix
    cout << "Enter the number of nodes : ";
    cin >> numberOfNodes;

    int startVertex, endVertex;

    // setting all node initial values to infinite
    for (int startVertex = 1; startVertex <= numberOfNodes; startVertex++) {
        for (endVertex = 1; endVertex <= numberOfNodes; endVertex++) {
            graphAdjMAtrix[startVertex][endVertex] = infinite;
        }
    }


    //accepting inputs edge-wise
    for (int startVertex = 1; startVertex < numberOfNodes; startVertex++) {
        for (endVertex = startVertex + 1; endVertex <= numberOfNodes; endVertex++) {
            cout << "Is there an edge between " << startVertex << " and " << endVertex << "? : ";
            cin >> graphAdjMAtrix[startVertex][endVertex];
            // graphAdjMAtrix[endVertex][startVertex]=graphAdjMAtrix[startVertex][endVertex];
        }
    }
}



void Graph :: displayGraph() {

    cout << " Graph in matrix format : \n";

    //displaying graph in the form of matrix
    int startVertex, endVertex;

    //displaying edge-wise
    for (int startVertex = 1; startVertex<=numberOfNodes; startVertex++) {
        for (endVertex = 1; endVertex <= numberOfNodes; endVertex++) {
            cout << graphAdjMAtrix[startVertex][endVertex] <<" ";
        }
        cout<<"\n";
    }
}


int Graph :: calculateDistance() {
    //Slide 99 
    int vertex, visited[20], minDistance[20];
    for (vertex = 1; vertex <= numberOfNodes; vertex++) {
        visited[vertex] = 0;
        minDistance[vertex] = infinite;
    }

    int source, destination;
    cout << "Enter Sorce and Destination Vertex : ";
    cin >> source >> destination;
    visited[source] = 1;
    minDistance[source] = 0;  //Source vertex distance is set to zero.

    int startSourceDistance;
    int tempDistance; 
    int tempSource;
    int cost;
    int minCost = 0;

    while( source != destination ) {

        cost = infinite;
        startSourceDistance =  minDistance[source];

        for( int endVertex = 1; endVertex <= numberOfNodes; endVertex++ ){

            tempDistance = startSourceDistance + graphAdjMAtrix[source][endVertex];
            if (tempDistance < minDistance[endVertex]) {

                minDistance[endVertex] = tempDistance;
                if(minDistance[endVertex]<cost)
                {
                    cost =  minDistance[endVertex];
                    tempSource = endVertex;
                }

            }
        }
        source = tempSource;
        visited[source] = 1;
        minCost = minCost + cost;
    }

    return minCost;
}  


int main() {
    int minCost = 0;
    Graph graphobj;
    graphobj.acceptGraph();
    graphobj.displayGraph();
    minCost= graphobj.calculateDistance();
    cout<< " Min. distance between source and destination is "<<minCost;

    return 0;
}