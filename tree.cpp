#include <bits/stdc++.h>
using namespace std;

struct Node  
{ 
  int key; 
  struct Node *left; 
  struct Node *right; 
  Node(int k){
      key=k;
      left=right=NULL;
  }
};

void inorder(Node *root){
    if(root!=NULL){
        inorder(root->left);
        cout<<root->key<<" ";
        inorder(root->right);    
    }
}  

void preorder(Node *root){
    if(root!=NULL){
        cout<<root->key<<" ";
        preorder(root->left);
        preorder(root->right);    
    }
} 

void postorder(Node *root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        cout<<root->key<<" ";
    }
}  

int height(Node *root){
    if(root==NULL)
        return 0;
    else
        return (1+max(height(root->left),height(root->right)));
}  


void nodesatdistancek(Node *root, int k){
    if (root==NULL)
    return;
    else
    {
        if(k==0){
            cout<<root->key<<" ";
        }
        else{
            nodesatdistancek(root->left, k-1);
            nodesatdistancek(root->right, k-1);
        }
    }
}


void printLevel(Node *root){
    if(root==NULL)return;
    queue<Node *>q;
    q.push(root);
    while(q.empty()==false){
        Node *curr=q.front();
        q.pop();
        cout<<curr->key<<" ";
        if(curr->left!=NULL)
            q.push(curr->left);
        if(curr->right!=NULL)
            q.push(curr->right);
    }
}  

int main() {
	
	Node *root=new Node(10);
	root->left=new Node(20);
	root->right=new Node(30);
	root->right->left=new Node(40);
	root->right->right=new Node(50);
    cout<<"Inorder : ";
	inorder(root);
    cout<<endl;
    cout<<"Preorder : ";
    preorder(root);
    cout<<endl;
    cout<<"Postorder : ";
    postorder(root);
    cout<<endl;
    cout<<"Height : ";
	cout<<height(root);
    cout<<endl;
    int k;
    cout<<"Enter k < height : ";
    cin>>k;
    if (k>=height(root))
    {cout<<"No nodes found";}
    else{
        cout<<"Node at distance "<<k<<" are : ";
    nodesatdistancek(root,k);}
    cout<<endl;
    cout<<"Tree level order traversal : \n";
    printLevel(root);
}