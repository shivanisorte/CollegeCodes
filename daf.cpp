
#include<fstream> // stream class to both read and write from/to files
#include<iostream> // standared input output stream
#include<iomanip>   // header providing parametric manipulators
#include<string.h>
#define SIZE 10         // size of hash table defined here
using namespace std;

struct student              // created struct student
{
    int rollno;             
    char name[20];
    float marks;
    int status;
    int link;
};

class linear_probe  
{                   //defining datamebers in the class
    char table[30];          // creation of hash table 
    fstream tab;             //read amd write records from table
    student rec;             //obj to access student records
    
public:            // member functions
    linear_probe();   //constuctor
    void displayall();  // display key here
    void insert(student);     //insert ele at a key
    int search(int);    //search at a key
    void display(int);  //display
    void read(int);    //read elements
    void write(int);   //write elements
    int modify(int);   //modify keys
};
 
linear_probe::linear_probe()    // constructing hash table
{
    int i;
    cout<<"\nEnter filename: ";           
    cin>>table;
    rec.status = 1;                // rec is the reference variable which is used to access data members of class
    rec.link = -1;       //table link initially 1
    tab.open(table, ios::binary | ios::out);      // open table here to write the output
    tab.close();               // close the table it is inbuilt function
    for(i=0; i<SIZE; i++)          // size of hash table from 0th index to 9th index (table size=10)
        write(i);
}

void linear_probe::displayall()              // to display the keys
{
    int i =1;
    for(i = 0; i< SIZE; i++)
        display(i);
}

void linear_probe::insert(student s)    // to insert data into table
{ 
    int i, j, start, k;             // initialization of variables as per requirement
    s.status = 0;           
    s.link = -1;
    start = s.rollno % SIZE;           // calculate hash value index of roll number
    
    for(i =0; i< SIZE; i++)
    {
        j = (start + i)% SIZE;           // to find the next empty location
        read(j);
        if(rec.status == 0 && (rec.rollno % SIZE) == start)  // checking the vaccant space and start value
            break;
    }
    if(i < 10)
    {
        while(rec.link != -1)        // to read the link value
        {
            j = rec.link;
            read(j);
        }
        for(i=0; i< SIZE; i++)
        {
            k = (start + i)%SIZE;    // extra element want to insert in hash table i.e.k
            read(k);
            if(rec.status)
            {
                rec = s;            // parameterised function
                write(k);
                read(j);
                rec.link = k;
                write(j);
                return;
            }
        }
        cout<<"\nTable is full!";     // when table is full beacuse table is having size=10
    }
    else
    {
        for(i=0; i< SIZE; i++)
        {
            k = (start + i)%SIZE;
            read(k);
            if(rec.status)
            {
                rec = s;
                write(k);
                return;
            }
        }
        cout<<"\nTable is full!";
    }
    
}

int linear_probe::search(int rno)      // rno is the variable the number which we want to search
{
    int start, i, j;
    start = rno % SIZE;
    
    for(i =0; i< SIZE; i++)
    {
        j = (start + i)% SIZE;
        read(j);
        if(rec.status == 0 && (rec.rollno % SIZE) == start)
            break;
    }
    
    if(i < 10)
    {
        while(rec.rollno != rno && rec.link != -1)
        {
            j = rec.link;
            read(j);
        }
        
        if(rec.rollno == rno)
            return j;            // if number is found it resturns j
        
        else
            return -1;           // if number is not found
    }
    else
        return -1;
}
void linear_probe::display(int rno)   // to display int rno
{
    int i = rno;
    tab.open(table, ios::binary | ios::in);
    tab.seekg(rno*sizeof(student), ios::beg);   // get pointer at begging 
    tab.read((char*)&rec,sizeof(student));       // to read a specific number of bytes from the file // size of(students)yeilds the object that we are referring
    if(rec.status == 0)                          //& rec is memory address of the object called rec 
    {
        cout<<endl;
        cout<<i<<" "<<rec.rollno<<" "<<rec.name<<" "<<rec.marks<<" "<<rec.link;
    }
    else
        cout<<"\n"<<i<<" !Empty!";
    tab.close();
}

void linear_probe::read(int rno)               // the function helps us to read a specific number of bytes from the file
{
    tab.open(table, ios::binary | ios::in);
    tab.seekg(rno * sizeof(student), ios::beg);
    tab.read((char*)&rec, sizeof(student));
    tab.close();
}

void linear_probe::write(int rno)                  // the function helps us to write a specific number of bytes from the file
{
    tab.open(table, ios::binary | ios::in | ios::out);
    tab.seekp(rno * sizeof(student), ios::beg);
    tab.write((char*)&rec, sizeof(student));
    tab.close();
}

int linear_probe::modify(int rno)    // rno is the number which we want to modify
{
    int start, i, j;
    start = rno % SIZE;
    
    for(i =0; i< SIZE; i++)
    {
        j = (start + i)% SIZE;
        read(j);
        if(rec.status == 0 && (rec.rollno % SIZE) == start)
            break;
    }
    
    if(i < 10)
    {
        while(rec.rollno != rno && rec.link != -1)
        {
            j = rec.link;
            read(j);
        }
        
        if(rec.rollno == rno)
        {
            tab.open(table, ios::binary | ios::in | ios::out);
            tab.seekg(rno * sizeof(student), ios::beg);
            cout<<"\nEnter modifeied details: ";
            cout<<"\nEnter roll number, name and marks: ";
            cin>>rec.rollno>>rec.name>>rec.marks;
            tab.write((char*)&rec, sizeof(student));
            tab.close();
            return j;
        }
        
        else
            return -1;
    }
    else
        return -1;
}
int main()
{
    int choice, rno, check;
    student rs;
    linear_probe lp;
    while(1)
    {
        cout<<"\n\n1. Create Database";
        cout<<"\n2. Display Database";
        cout<<"\n3. Add a record";
        cout<<"\n4. Search a record";
        cout<<"\n5. Modify a record";
        cout<<"\n6. Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1: cout<<"\nEnter details: ";
                    cout<<"\nEnter roll number, name and marks: ";
                    cin>>rs.rollno>>rs.name>>rs.marks;
                    lp.insert(rs);
                    break;
            case 2: lp.displayall();
                    break;
            case 3: cout<<"\nEnter details: ";
                    cout<<"\nEnter roll number, name and marks: ";
                    cin>>rs.rollno>>rs.name>>rs.marks;
                    lp.insert(rs);
                    break;
            case 4: cout<<"\nEnter roll number to be searched: ";
                    cin>>rno;
                    check = lp.search(rno);
                    if(check >= 0)
                    {
                        cout<<"\nRecord Number: "<<check;
                        lp.display(check);
                    }
                    else
                        cout<<"\nRecord not found!";
                    break;
            case 5: cout<<"\nEnter roll number to be modified: ";
                    cin>>rno;
                    check = lp.modify(rno);
                    if(check >= 0)
                    {
                        cout<<"\nRecord Number: "<<check;
                        lp.display(check);
                    }
                    else
                        cout<<"\nRecord not found!";
                    break;
            case 6: return 0;
        }
    }
    return 0;
}


/*
Enter filename: student.dat


1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 1

Enter details: 
Enter roll number, name and marks: 1 sweety 89


1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 2

0 !Empty!
1 1 sweety 89 -1
2 !Empty!
3 !Empty!
4 !Empty!
5 !Empty!
6 !Empty!
7 !Empty!
8 !Empty!
9 !Empty!

1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 3

Enter details: 
Enter roll number, name and marks: 2
sneha 77


1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 3

Enter details: 
Enter roll number, name and marks: 3 ddd 88


1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 3

Enter details: 
Enter roll number, name and marks: 4
gita 55


1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 2

0 !Empty!
1 1 sweety 89 -1
2 2 sneha 77 -1
3 3 ddd 88 -1
4 4 gita 55 -1
5 !Empty!
6 !Empty!
7 !Empty!
8 !Empty!
9 !Empty!

1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 3

Enter details: 
Enter roll number, name and marks: 44 yogita 66


1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 2

0 !Empty!
1 1 sweety 89 -1
2 2 sneha 77 -1
3 3 ddd 88 -1
4 4 gita 55 5
5 44 yogita 66 -1
6 !Empty!
7 !Empty!
8 !Empty!
9 !Empty!

1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 4

Enter roll number to be searched: 4

Record Number: 4
4 4 gita 55 5

1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 5

Enter roll number to be modified: 4

Enter modifeied details: 
Enter roll number, name and marks: 64 hh 99

Record Number: 4
4 64 hh 99 5

1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 2

0 !Empty!
1 1 sweety 89 -1
2 2 sneha 77 -1
3 3 ddd 88 -1
4 64 hh 99 5
5 44 yogita 66 -1
6 !Empty!
7 !Empty!
8 !Empty!
9 !Empty!

1. Create Database
2. Display Database
3. Add a record
4. Search a record
5. Modify a record
6. Exit
Enter your choice: 
*/