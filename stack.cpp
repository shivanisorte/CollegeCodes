#include <iostream>

using namespace std;

class Node {
    public :   
    string data;
    Node *link;
};

class Stack {
    public :
    Node *top, *temp;
    
    Node *createNode();
    void push();
    void pop();
    void display();

    Stack() {
        top = NULL;
    }
};

Node *Stack :: createNode() {
    Node *newNode = new Node();
    cout << "Please enter a data value within the stack - ";
    cin >> newNode -> data;
    newNode -> link = NULL;

    return newNode;
}

void Stack :: push() {
    if(top == NULL) {
        top = createNode();
    }
    else {
        temp = createNode();
        temp -> link = top; // Logic ==> temp (new node) ---> top -> element -> element -> element -> ..... -> NULL
        top = temp;         // Logic ==> temp is now top => top -> element (previous top) -> element -> ..... -> NULL
    }
}

void Stack :: pop() {
    if(top == NULL) {   // If the linked list (stack) is empty
        cout << "The stack is empty, cannot pop any elements. " << endl;
    }
    else {
        temp = top;
        top = top -> link;  // Assigning the next element as top
        cout << "The element being popped is - " << temp -> data << endl;

        delete temp;
        temp = NULL;
    }
}

void Stack :: display() {
    temp = top;
    
    while(temp != NULL) {
        cout << temp -> data << " ";
    }
}

void showMenu() {
    cout << "  Enter 1 to push an element into the stack \n\t2 to pop the top element \n\t3 to display the stack \n\t4 to display the menu \n\t5 to exit the application" << endl;
}

int main() {
    cout << "\n\n\t\t ------ Stack Operations with Linked Lists ------ " << endl;
    showMenu();

    int choice;
    Stack stObj;

    while(true) {
        cout << "\nEnter a number (4 to display the menu) - ";
        cin >> choice;

        if(choice == 5)
            break;

        switch(choice) {
            case 1 :
                stObj.push();
                break;
            case 2 :
                stObj.pop();
                break;
            case 3 : 
                stObj.display();
                break;
            case 4 : 
                showMenu();
                break;
            
            default :
                cout << "Please enter a valid number. " << endl;
        }
    }

    cout << "\n\t ------ Thank you for using the Stack with Linked Lists Application ------\n";

    return 0;
}