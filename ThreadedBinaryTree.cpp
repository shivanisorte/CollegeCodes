#include<iostream>
using namespace std;


struct node
{
    int data;
    node *left;
    node *right;
    bool lthread, rthread;
}*root, *header;

class TBT
{
    public:
    TBT()
    {
        root = NULL;
        header = NULL;
    }
    void createTBT();
    node* getData();
    void insert(node *, node*);
    void displayInorder(node*, node*);
};

void TBT :: insert(node *rootnode, node *addnode)
{
    if(addnode->data < rootnode->data)
    {
        if(rootnode->lthread == true)
        {
            addnode->left = rootnode->left;
            addnode->right = rootnode;
            rootnode->left = addnode;
            rootnode->lthread = false;
        }
        else
        {
            insert(rootnode->left, addnode);
        }
    }
    else
    {
        if(rootnode->rthread == true)
        {
            addnode->right = rootnode->right;
            addnode->left = rootnode;
            rootnode->right = addnode;
            rootnode->rthread = false;
        }
        else
        {
            insert(rootnode->right, addnode);
        }
    }
}

node* TBT :: getData()
{
    node *newNode = new node();
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->lthread = newNode->rthread = true;
    cout<<"Enter data : ";
    cin>>newNode->data;

    return newNode;
}

void  TBT :: createTBT()
{
    node *newnode = new node();
    node *headnode = new node();
    headnode->data = -999;
    headnode->right= headnode;
    char userchoice = 'y';
    while(userchoice == 'y')
    {
        newnode = getData();
        if(root == NULL)
        {
            root = newnode;
            headnode->left = root;
            header = headnode;
            root->left = header;
            root->right = header;
        }
        else
        {
            insert(root, newnode);
        }
        cout<<"Do you want to add node?(y/n) :";
        cin>>userchoice;
        if(userchoice =='n')
            break;
    }
}

void TBT :: displayInorder(node *tempnode, node *head)
{
    if(tempnode == NULL){
        cout<<"Tree is empty!"<<endl;;
        return;
    }
    while(tempnode != NULL)
    {
        while(tempnode->lthread == false)
        {
            tempnode = tempnode->left;
        }
        cout<<tempnode->data<<"  ";
        while(tempnode->rthread == true)
        {
            tempnode = tempnode->right;
            if(tempnode==head)
                return;
            cout<<tempnode->data<<"  ";
        }
        tempnode = tempnode->right;
    }
    cout<<endl;
}

int main(){
    char ch ='y';
    int data, choice;
    TBT obj;
    
    while(ch == 'y' || ch == 'Y')
    {
        cout<<"1.Create TBT"<<endl;
        cout<<"2.Display"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        
        switch(choice)
        {
            case 1: 
                obj.createTBT();
                break;
            case 2:
                obj.displayInorder(root, header);
                break;
            default:
                cout<<"Invalid choice!";
        }
        cout<<"Do you want to continue? (y/n) :";
        cin>>ch;
    }
}