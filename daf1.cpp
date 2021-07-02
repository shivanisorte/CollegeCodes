/* Direct access file. Collision handling to be done 
by chaining without replacement for employee data as 
empcode, empname */

#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
#include<process.h>
#include<math.h>

using namespace std;

#define max 15
class employee
{
 public:
 char name[max];
 int empid;
 int chain;
 int delflag;
};

class hashfile
{
 fstream hfile;
 public:
 hashfile();
 int hash(int x){
     return x % 10;
     }
 void insert();
 void search();
 void display();
};

// function to initialize empty file 
hashfile :: hashfile()
{
 int i;
 employee rec2;
 fstream iofile;
 iofile.open("hfile.dat", ios::out | ios::binary);
 strcpy(rec2.name, "\0");
 rec2.chain = -1;
 rec2.delflag = 0;
 for(i = 0; i < 10; i++)
 {
 rec2.empid = 0;
 iofile.write((char*)&rec2, sizeof(rec2));
 }

 iofile.close();
}

// function to insert a record in hash file
void hashfile :: insert()
{
 int i, flag = 0, pos, cnt = 0;
 long temp, start, size;
 fstream iofile;
 employee insertrec, rec3, trec;
 cout << "Enter name";
 cin >> insertrec.name;
 cout << "Enter no. of empid";
 cin >> insertrec.empid;
 insertrec.chain = -1;
 insertrec.delflag = 0;
 size = sizeof(insertrec);
 pos = hash(insertrec.empid);
 iofile.open("hfile.dat", ios :: in | ios :: out | ios :: binary);
 iofile.seekg(0);
 temp = pos * sizeof(insertrec);
 iofile.seekg(temp);
 // move to position given by hash function
 flag = 0;
 iofile.read((char*) &rec3, sizeof(rec3));
 if(rec3.empid == 0) // slot is empty
 {
 flag = 1;
 temp = pos * sizeof(rec3);
 iofile.seekp(temp); /* move to position 
given by hash function */
 iofile.write ((char*) &insertrec, sizeof(insertrec));
 return;
 }
 else // slot is not empty
 {
 if(hash(rec3.empid) == hash(insertrec.empid))
 {
 while(rec3.chain != -1)
 {
 iofile.seekg(rec3.chain * sizeof (rec3));
 pos = rec3.chain;
 iofile.read((char*) &rec3, sizeof(rec3));
 }
 flag = 2;
 }
 int nextpos = pos;
 trec = rec3;
 while(iofile.read((char*) &rec3, sizeof(rec3)))
 // find next empty position
 {
 if(rec3.empid == 0) // empty slot
 {
 iofile.seekp((nextpos+1) * sizeof(rec3));
 // move to position given by hash function
 iofile.write((char*) &insertrec, 
sizeof(insertrec));
 if(flag == 2)
 {
 iofile.seekp(pos * sizeof (rec3));
 trec.chain = nextpos + 1;
 iofile.write ((char*) &trec, sizeof(trec));
 }
 flag = 1;
 break;
 }
 nextpos++;
 }
 }
 if(flag != 1)
 {
 cout << "Error this rec was not inserted";
 cout << "The fi le is full after this index";
 getch(); return;
 }
 getch();
 iofile.close();
} // end of insert
// function to search a record of hash fi le
void hashfile :: search()
{
 int pos = 0, t_empid;
 fstream iofile;
 employee rec1;
 cout << "Enter the empid of the book to be searched";
 cin >> t_empid;
 pos = hash(t_empid);
 // get the position of search record
 iofile.open("hfile.dat", ios::in | ios::binary);
 iofile.seekg(0);
 iofile.seekg(pos*sizeof(rec1));
 while(iofile.read((char *)&rec1, sizeof(rec1)))
 // read record at position
 {
 if(rec1.empid == t_empid) // found
 {
 cout << "name" << rec1.name << "empid" << rec1.
empid;
 getch();
 iofile.close();
 return;
 }
 else if(hash(rec1.empid) == pos)
 // if record is stored at position
 {
 iofile.seekg(0);
 if(rec1.chain != -1)
 iofile.seekg(rec1.chain*sizeof(rec1));
 // jump at position of chain
 }
 }
 cout << "error no. such rec exist";
 getch();
 iofile.close();
}
void hashfile :: display()
{
 int i = 0;
 employee rec2;
 fstream iofile;
 cout << "\n\nserial\tempid\tname\tchain";
 iofile.open("hfile.dat", ios :: in | ios :: binary);
 while(iofile.read((char *)&rec2, sizeof(rec2)))
 cout << "\n\n" << i++;
 cout << "\t" << rec2.empid;
 {
 cout << "\t" << rec2.name;
 cout << "\t" << rec2.chain;
 }
 getch();
 iofile.close();
}
int main()
{
 int ch, pos;
 float flag = 1.1;
 hashfile file1;
 // rec.init();
 // clrscr();
 do
 {
 cout << "\n 1.Insert a rec";
 cout << "\n 2.Disp all rec";
 cout << "\n 3.Search a rec";
 cout << "\n 4.Exit";
 cout << "\n Enter choice";
 cin >> ch;
 switch(ch)
 {
 case 1:
 file1.insert();
 break;
 case 2:
 file1.display();
 break;
 case 3:
 file1.search();
 break;
 case 4:
 exit(0);
 }
 }while(ch != 4);
 return 0;
}
