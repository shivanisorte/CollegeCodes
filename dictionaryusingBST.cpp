#include <iostream>
#include <string.h>

using namespace std;

struct Node {
    char key[20];
    char meaning[20];
    Node *left, *right;
} *root;

class Dictionary {
    public:
        Dictionary() {
            root = NULL;
        }

        Node *getData();
        Node *getInorderSuccessor(Node *curr);
        void createDictionary();
        void insertNode(Node *);
        void displayDictionary(Node *);
        void searchInDictionary(char *);
        void updateInDictionary(char *);
        Node *deleteFromDictionary(Node *, char *);
};

Node *Dictionary:: getInorderSuccessor(Node *curr){ // gets the closest highest value
    curr=curr->right;
    while(curr!=NULL && curr->left!=NULL)
        curr=curr->left; // since closest highest value will be the leftmost node of the right child
    return curr;
}

Node *Dictionary :: getData() {
    Node *new_node = new Node;
    cout << "Enter a key value - ";
    cin >> new_node -> key;

    cout << "Enter its meaning - ";
    cin >> new_node -> meaning;

    new_node -> right = NULL;
    new_node -> left = NULL;

    return new_node;
}

void Dictionary :: createDictionary() {
    Node *new_node = new Node;
    new_node = getData();

    if (root == NULL)
        root = new_node;
    else 
        insertNode(new_node);
}

void Dictionary :: insertNode(Node *new_node) {
    Node *temp = new Node;
    temp = root;
    
    while (1) {
        if (strcmp(new_node -> key, temp -> key) < 0) {
            if (temp -> left == NULL){
                temp -> left = new_node;
                break;
            }
            else
                temp = temp -> left;
        }
        else {
            if (temp -> right == NULL){
                temp -> right = new_node;
                break;
            }
            else
                temp = temp -> right;
        }
    }
}

void Dictionary :: displayDictionary(Node *temp) {
    if (temp != NULL) {
        displayDictionary(temp -> left);
        cout << "\n Keyword : " << temp -> key;
        cout << "\t Meaning : " << temp -> meaning;
        displayDictionary(temp -> right);
    }

    cout << "\n";
}

void Dictionary :: searchInDictionary(char search_key[]) {
    Node *temp = root;
    
    while (temp != NULL) {
        if (strcmp(search_key, temp -> key) == 0) {
            cout << "Keyword found! The meaning is: " << temp -> meaning;
            return;
        }
        else if (strcmp(search_key, temp -> key) < 0)
            temp = temp -> left;
        else
            temp = temp -> right;
    }

    cout << "Keyword " << search_key << " not found.\n";
}

void Dictionary :: updateInDictionary(char search_key[]){
    Node *temp = root;
    
    while (temp != NULL) {
        if (strcmp(search_key, temp -> key) == 0) {
            cout << "Keyword found! The meaning is: " << temp -> meaning;
            cout << "\nEnter the new meaning: ";
            cin >> temp -> meaning;
            return;
        }
        else if (strcmp(search_key, temp -> key) < 0)
            temp = temp -> left;
        else
            temp = temp -> right;
    }

    cout << "Keyword " << search_key << " not found.\n";
}

Node *Dictionary :: deleteFromDictionary(Node *root, char delete_key[]) {

    if (root == NULL){
        cout << "Tree Empty. No changes made. \n\n";
        return root;
    }

    if (strcmp(delete_key, root -> key) < 0)
        root->left = deleteFromDictionary (root->left,delete_key);

    else if (strcmp(delete_key, root -> key) > 0)
        root->right = deleteFromDictionary (root->right,delete_key);

    else{
        if (root->left == NULL){
            Node *temp = root -> right;
            delete root;
            return temp;
        }
        else if (root -> right == NULL){
            Node *temp = root -> left;
            delete root;
            return temp;
        }
        else{
            Node *succ=getInorderSuccessor(root);
            *root->key=*succ->key;
            root->right=deleteFromDictionary(root->right,succ->key);
        }

    }

    return root;

}




int main() {
    Dictionary dictObj;

    int choice;
    char permission, search_key[20];

    do {
        cout << "\nEnter: 1 to create, 2 to display, 3 to search, 4 to update and 5 to delete. \n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            dictObj.createDictionary();
            break;
        case 2:
            dictObj.displayDictionary(root);
            break;
        case 3:
            cout << "Enter the keyword you would like to search - ";
            cin >> search_key;
            dictObj.searchInDictionary(search_key);
            break;
        case 4:
            cout << "Enter the keyword you would like to update - ";
            cin >> search_key;
            dictObj.updateInDictionary(search_key);
            break; 
        case 5:
            cout << "Enter the keyword you would like to delete - ";
            cin >> search_key;
            cout<<endl;
            root = dictObj.deleteFromDictionary(root, search_key);
            cout<<"Your dictionary :"<<endl;
            dictObj.displayDictionary(root);
            break;

        default:
            cout << "Please enter a valid number";
            break;
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> permission;
    } while (permission == 'y');

    return 0;
}