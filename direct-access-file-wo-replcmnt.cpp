#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>

#define SIZE 5

using namespace std;

struct Student {
    int roll_no, status, link;
    char name[20];
    float marks;
};

class LinearProbe {
    char table[30];
    fstream tab;
    Student rec;

    public:
    LinearProbe();
    void displayAll();
    void insert(Student);
    int search(int);
    void display(int);
    void read(int);
    void write(int);
    int modify(int);
};

LinearProbe :: LinearProbe() {
    int i;
    cout << "\nEnter the file name: ";
    cin >> table;
    rec.status = 1;
    rec.link = 1;
    
    tab.open(table, ios :: binary | ios :: out);
    tab.close();
    for (i = 0; i < SIZE; i++)
        write(i);
}

void LinearProbe :: displayAll() {
    int i = 1;
    for (i = 0; i < SIZE; i++)
        display(i);
}

int main() {
    return 0;
}