/* Accept a graph from user using adjacency 
matrix or adjacency list and perform breadth 
first seach and depth first search traversals 
for the same. */


// USING ADJACENCY MATRIX


#include <iostream>
using namespace std;

class Stack
{
    int item[50];  //Stack in array form
    int top;

    public:
        Stack()
        {
            top = -1;
        }

        int pop()
        {
            int x;
            if (isEmpty())
                cout << "\nStack is empty" << endl;
            else
            {
                x = item[top];
                top--;
            }
            return x;
        }

        void push(int x)
        {
            if (isFull())
                cout << "\nStack is full" << endl;
            else
            {
                top++;
                item[top] = x;
            }
        }

        bool isEmpty()
        {
            if (top == -1)
                return true;
            else
                return false;
        }

        bool isFull()
        {
            if (top == 50)
                return true;
            else
                return false;
        }
};

class Queue
{
    int item[50];
    int front, rear;

    public:
        Queue()
        {
            front = rear = -1;
        }

        int dequeue()
        {
            int x;
            if (isEmpty())
                cout << "\nQueue is empty" << endl;
            else
            {
                x = item[front];
                front++;
            }
            return x;
        }

        void enqueue(int x)
        {
            if (isFull())
                cout << "\nQueue is full" << endl;
            else
            {
                if (front == -1)
                    front++;
                item[++rear] = x;
            }
        }

        bool isEmpty()
        {
            if (front == - 1 || front > rear)
                return true;
            else
                return false;
        }

        bool isFull()
        {
            if (front == 50)
                return true;
            else
                return false;
        }
};

class Graph
{
    friend class Stack; // A friend class can access private and protected members of other class in which it is declared
    int n; //vertices
    int adj[50][50]; //graph 2D array 
    int visited[50]; //visited or not (contains 0 or 1)

    public:
        Graph(); //initialization of basic graph
        void create();
        void depthFirstSearch();
        void breadthFirstSearch();
};

Graph :: Graph()
{ 
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++)
            adj[i][j] = 0;
    
    for (int i = 0; i < 50; i++)
        visited[i] = 0;
        //0- not visited
        //1- visited
}
 
void Graph :: create()
{
    int ch;
    cout << "Number of vertices in the graph : ";
    cin >> n;

    int i = 0, j = 0;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            cout << "Is there an edge between " << i << " and " << j << "? (1/0) : ";
            cin >> ch;

            if (ch == 1)
                adj[i][j] = adj[j][i] = 1;
        }
    }
}

void Graph :: depthFirstSearch()
{
    Stack s;
    int i;
    cout << "\n -------------- Depth First Search --------------\n";
    cout << "Enter starting vertex: ";
    cin >> i;

    s.push(i);

    while (!s.isEmpty())
    {
        i = s.pop();

        if (visited[i] == 1)
            continue;
        
        cout << " " << i;

        visited[i] = 1;

        for (int k = 0; k < n; k++) // Push adjacent vertices into the stack
        {
            if (adj[i][k] == 1 && visited[k] == 0)
                s.push(k);
        }
    }

    for (i = 0; i < 50; i++)
        visited[i] = 0;
}

void Graph :: breadthFirstSearch()
{
    Queue q;
    int i;
    cout << "\n -------------- Breadth First Search --------------\n";
    cout << "Enter starting vertex: ";
    cin >> i;

    q.enqueue(i);

    while (!q.isEmpty())
    {
        i = q.dequeue();

        if (visited[i] == 1)
            continue;
        
        cout << " " << i;

        visited[i] = 1;

        for (int k = 0; k < n; k++) // Push adjacent vertices into the stack
        {
            if (adj[i][k] == 1 && visited[k] == 0)
                q.enqueue(k);
        }
    }

    for (i = 0; i < 50; i++)
        visited[i] = 0;
}

int main()
{
    Graph g;

    g.create();
    g.depthFirstSearch();
    g.breadthFirstSearch();

    return 0;
}