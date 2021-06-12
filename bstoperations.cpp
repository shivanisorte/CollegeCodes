#include <iostream>
using namespace std;

class BstNode {
public:
	int height, data;
	BstNode *left, *right;
};

BstNode* create_node( int data )
{
	BstNode* newNode = new BstNode;
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

int height( BstNode *pt )
{
	int lt, rt;
	if( pt != NULL )
	{
		lt = height( pt->left );
		rt = height( pt->right );
		if( lt > rt )
			return lt+1;
		else
			return rt+1;
	}
}

void inorder_leaf( BstNode *ptr )
{
	if( ptr != NULL )
	{
		inorder_leaf( ptr->left );
		if ( (ptr->left == NULL) && (ptr->right == NULL))
			cout << ptr->data << " ";
		inorder_leaf ( ptr->right );
	}
}

void mirror( BstNode *node ) 
{
	if( node == NULL )
		return;
	else {
		BstNode *temp;
		mirror( node->left );
		mirror( node->right );
		temp = node->left;
        node->left = node->right;
        node->right=temp;

	}
}

void print ( BstNode *root, int level )
{
	if ( root == NULL )
		return;
	else if ( level == 1)
		cout<< root->data << " ";
	else if ( level > 1 )
	{
		print( root->left, level-1 );
		print( root->right, level-1 );
	}
}

void level( BstNode *root )
{
	int h = height( root );
	int i;
	for (i=1; i<=h; i++)
	{
		print( root, i );
		cout<< endl;
	}
}
BstNode* insert( BstNode* root, int data )
{
	if ( root == NULL )
	{
		root = create_node(data);
	}
	if ( data < root->data )
	{
		root->left = insert( root->left, data );
	}
	else if ( data>root -> data )
	{
		root->right = insert(root->right, data);
	}
	return root ;
}

void inorder( BstNode*ptr )
{
	if (ptr != NULL )
	{
		inorder( ptr->left );
		cout<< ptr->data << " ";
		inorder( ptr->right );
	}
}

int main()
{
	BstNode *root =NULL;
	char ch ='y';
	int data,h,choice;
	while(ch=='y'|| ch=='y')
	{
		cout<<"Enter 1 to insert an element, 2 to display the BST, 3 to display the height of the BST, 4 to display Mirror of the BST, 5 to Display the BST level-wise"<<endl;
		cin>>choice;
		switch( choice )
		{
			case 1:
			   cout << endl << "Enter data value" << endl;
			   cin >> data;
			   root = insert( root, data );
			   break;
			case 2:
			   inorder( root );
			   break;
		    case 3:
		       h= height( root );
			   cout<< "The height of the BST is : "<< h << endl;
			   break;
			case 4:
			   cout<< "The mirror image of the BST is : "<< endl;
			   mirror( root );
			   inorder( root );
			   mirror( root );
			   break;
			case 5:
				cout<< endl <<" BST displayed level-wise : "<< endl;
				level( root );
				mirror( root );
				cout<< endl << " Mirror BST displayed level-wise : " << endl;
				level( root );
				mirror( root );
				break;
			case 6:
				inorder_leaf( root );
				break;
			default:
				cout<< "Invalid choice" << endl;

			
		}
		cout << endl << "Do you wanrt to continue (y/n)? " << endl;
		cin >> ch;
	} 
	return 0;      
}
