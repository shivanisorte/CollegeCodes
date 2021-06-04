
 #include<iostream>
 #include<algorithm>
 #include<vector>

 using namespace std;


 class Edge{  //class to store an edge in a graph
   public:
   int source, destination, weight;
   Edge( int source, int destination, int weight)
   { //constructor
     this->source = source;
     this->destination = destination;
     this->weight = weight;
   }
 };


 class Graph{  //class for a graph
   public:
   vector<Edge>  All_edges;// to hold list of all edges of the graph

   //member function to add an edge to the undirected graph
   void addEdge(int s, int d, int w)
   {
      Edge obj(s, d, w);//create one edge  
      All_edges.push_back(obj);//push one edge to edge container
   }

   };

  //declare a displayMST function to define it later
  void displayMST(const vector<Edge> &);

//class for finding MST in the graph
  class Kruskal {

  public:
  int totalVertices;//total vertices

  vector<pair<int,int>> subsets;
  // subsets will hold list of [parent - rank] pairs
  // which we will use in Union Find 
  // by path compression algorithm

  vector<Edge> mst;//declare a container to store edges of MST

 //constructor
    Kruskal( int totalVertices)
    {
       this->totalVertices =totalVertices;

       subsets.resize(totalVertices);
       //resize subsets equal to total vertices

       for( int i= 0; i<totalVertices; ++i)
        {
          subsets[i].first =i; //set parent value equal to respective index
          subsets[i].second = 0; //set rank value equal to zero
        }
    }

    static bool comparator( Edge &a , Edge& b)
    {
      return a.weight < b.weight;
    }

    void createMST( Graph& graph)
    {
      //sort the edges of graph in increasing order of their weights
     sort( graph.All_edges.begin(), graph.All_edges.end(), comparator );

    int i=0, e=0;
    // i =  variable to keep track of total vertices 
    // e = variable to keep track of total edges in MST formed so far
    // total edges in MST  == (total vertices - 1)

    //iterate through list of edges in a graph
    while( e < (totalVertices-1) && i < graph.All_edges.size() )
    {
      //store current edge
      Edge currEdge = graph.All_edges[i++];

      //find absolute parent 
     //to detect if current edge form a cycle with MST formed so far
      int x = _find( currEdge.source);//pass current source vertex
      int y = _find( currEdge.destination );//pass current destination vertex

      if( x != y)//is they don't form a cycle 
      {   
        //push current edge to MST
        mst.push_back( currEdge );
        //then make that two vertex Union
        // in other words to create edge between two vertices
        makeUnion( x, y);
      }
    }

    //finally display the MST created by the above function
    displayMST( mst );

    }

   int _find(  int i)
   {
       if( subsets[i].first!=i)//if index is not equal to parent value
       {
         //recursively call _find()
         // and pass current parent value 
         subsets[i].first = _find( subsets[i].first );

       }

       return subsets[i].first;
   }

   void makeUnion( int x, int y)
   {   
     int xroot = _find( x);
     int yroot = _find(y);

    // if-else for rank comparison & update parent-rank values
     if( subsets[xroot].second < subsets[yroot].second)
     { 
       subsets[xroot].first= yroot;
     }
     else if( subsets[xroot].second > subsets[yroot].second)
     {
       subsets[yroot].first=xroot;
     }
     else{
       subsets[xroot].first=yroot;
       subsets[yroot].second++;
      }
   }

 };

  // funciton to display all edges of MST & total cost
  void displayMST(  const vector<Edge>&  edges)
  { 
     int totalMinimumCost=0;
    cout<<"All MST edges [source - destination = weight]\n";

    for( auto edge : edges)
    {
      cout<<edge.source<<" - "<<edge.destination<<" = "<<edge.weight<<'\n';

      totalMinimumCost+=edge.weight;
    }
    cout<<"total minimum cost = "<<totalMinimumCost<<endl;
  }


 int main()
 {

   Graph g;
   //add edeges to graph
   g.addEdge(0, 1, 50);
   g.addEdge( 0 , 2, 10);
   g.addEdge(0, 3, 50);
   g.addEdge(1, 4, 30);
   g.addEdge(3, 4, 100);
   g.addEdge(2, 4, 100);

   //create and object of kruskal class
   Kruskal graph(5);

   //call kruskal class's member function to find MST
   graph.createMST( g);

   return 0;

 }
