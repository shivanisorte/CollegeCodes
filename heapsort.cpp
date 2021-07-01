#include <iostream> 
using namespace std; 


void heapify(int arr[], int n, int i)   //find max of node and its 2 children
{ 
	int largest = i; 
	int l = 2*i + 1; 
	int r = 2*i + 2;
	if (l < n && arr[l] > arr[largest]) 
		largest = l; 

	if (r < n && arr[r] > arr[largest]) 
		largest = r; 

	if (largest != i) 
	{ 
		swap(arr[i], arr[largest]);  //swap largest node w root node
		heapify(arr, n, largest); 
	} 
} 

//parent(i) = (i-1)/2

void buildheap(int arr[],int n){   //converting BT to a maxheap
    for (int i = n / 2 - 1; i >= 0; i--) //begin from last internal node and go to the root node
		heapify(arr, n, i);
}
void heapSort(int arr[], int n) 
{  
	buildheap(arr,n); 

	for (int i=n-1; i>0; i--) 
	{ 
		swap(arr[0], arr[i]);
		heapify(arr, i, 0); 
	} 
} 

void printArray(int arr[], int n) 
{ 
	for (int i=0; i<n; ++i) 
		cout << arr[i] << " "; 
	cout << "\n"; 
} 
 
int main() 
{ 
	int arr[20], m;
	cin>>m;

	for (int i=0; i<m; i++){
		cin>>arr[i];
	}

	int n = sizeof(arr)/sizeof(arr[0]); 

	heapSort(arr, n); 

	cout << "Sorted array is \n"; 
	printArray(arr, n); 
} 
