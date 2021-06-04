#include <iostream>

using namespace std;

class Node {
    public: 
        int data;
        Node *left, *right;
};

class BinarySearchTree {
    public:
    Node *root;
    
    BinarySearchTree() {
        root = NULL;
    }

    Node* create(int);   // Takes data as parameter
    Node* insertNode(Node *, Node *);   
    void inorderTraversal(Node *);
    void display(Node *);
    Node *insertRec(Node *, int);
    int mirror(Node *);
    int height(Node *);
    void print(Node *, int);
    void level(Node *);
};

Node* BinarySearchTree :: create(int data) {
    Node *new_node = new Node;
    new_node -> data = data;
    new_node -> left = NULL;
    new_node -> right = NULL;

    if (root == NULL) {
        root = new_node;
    }
    else {
        root = insertNode(root, new_node);
        cout<<"created new node";
    }
     
    return root;
}

Node* BinarySearchTree :: insertNode(Node *root, Node *new_node) {
    
    if (root == NULL) {
        root = new_node;
    }

    if (new_node -> data < root -> data) {
        insertNode(root -> left, new_node);
    }
    else {
        insertNode(root -> right, new_node);
    }

    return root;
}

void BinarySearchTree :: inorderTraversal(Node *t) {
    if (t != NULL) {
        inorderTraversal(t -> left);
        cout << t -> data << " ";
        inorderTraversal(t -> right);
    }
}

void BinarySearchTree :: display(Node * temp) {
    // Node *temp;
    // temp = root;
    inorderTraversal(temp);
}

int BinarySearchTree :: mirror(Node *node) {
    if (node == NULL) {
        return -1;
    }
    else {
        Node *temp;
        mirror(node -> left);
        mirror(node -> right);
        temp = node -> left;
        node -> left = node -> right;
        node -> right = temp;
    }
}

int BinarySearchTree :: height(Node *root) {
    int left_height, right_height;
    
    if (root == NULL) {
        return -1;
    }
    else {
        left_height = height(root -> left);
        right_height = height(root -> right);

        if (left_height > right_height) {
            return (left_height + 1);
        }
        else {
            return (right_height + 1);
        }
    }
}

void BinarySearchTree :: print(Node *root, int level) {
    if (root == NULL) {
        return;
    }
    else if (level == 1) {
        cout << root -> data << " ";
    }
    else if (level > 1) {
        print(root -> left, level - 1);
        print(root -> right, level - 1);
    }
}

void BinarySearchTree :: level(Node *root) {
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++) {
        print(root, i);
        cout << root << i << endl;
    }
}

int main() {
    Node *root;
    BinarySearchTree bstObj;
    root = bstObj.create(1);
    root = bstObj.create(2);
    root = bstObj.create(3);
    root = bstObj.create(4);
    root = bstObj.create(5);
    bstObj.print(root, 1);
    bstObj.display(root);
}