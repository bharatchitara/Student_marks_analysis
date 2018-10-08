//*************************************************************** //                   HEADER FILE USED IN PROJECT //****************************************************************
#include<fstream.h>
#include<string.h>
#include<iomanip.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>

//*************************************************************** //                   CLASS USED IN PROJECT //****************************************************************

class student
{
int rollno ;
char name [ 50 ];
int poc_marks;
int spt_marks;
int ppl_marks;
int dms_marks;
int se_marks;
int mp_marks;
float per ;
char grade ;
void calculate (); //function to calculate grade

public :
   void getdata (); //function to accept data from user
   void showdata (); //function to show data on screen
   void show_tabular ();
   int retrollno ();
}; //class ends here

   void student :: calculate ()
   {
   per = ( poc_marks + spt_marks + ppl_marks + dms_marks + se_marks + mp_marks)/ 6.0 ;
if ( per >= 75 )
grade= 'A' ;
else if ( per>=60 && per<=74.99 )
grade= 'B' ;
else if ( per>=33 && per<=59.99)
grade= 'C' ;
else
grade= 'F' ;
    }

void student :: getdata()
{
cout << "\nEnter The roll number of student " ;
cin >> rollno ;
cout << "\n\nEnter The Name of student " ;
gets ( name );
cout << "\nEnter The marks in POC out of 100 : " ;
cin >> poc_marks ;
cout << "\nEnter The marks in SPT out of 100 : " ;
cin >> spt_marks ;
cout << "\nEnter The marks in PPL out of 100 : " ;
cin >> ppl_marks ;
cout << "\nEnter The marks in DMS out of 100 : " ;
cin >> dms_marks ;
cout << "\nEnter The marks in SE out of 100 : " ;
cin >> se_marks ;
cout << "\nEnter The marks in MP out of 100 : " ;
cin >> mp_marks ;

calculate ();
}


void student :: showdata ()
{
cout << "\nRoll number of student : " << rollno ;
cout << "\nName of student : " << name ;
cout << "\nMarks in POC : " << poc_marks ;
cout << "\nMarks in SPT : " << spt_marks ;
cout << "\nMarks in PPL : " << ppl_marks ;
cout << "\nMarks in DMS : " << dms_marks ;
cout << "\nMarks in SE :" << se_marks ;
cout << "\nMarks in MP :" << mp_marks ;
cout << "\nPercentage of student is  :" << per;
cout << "\nGrade of student is :" << grade;

}


void student :: show_tabular ()
{

cout << rollno << setw ( 6 )<< " " << name << setw ( 10 )<< " " <<poc_marks << setw ( 4)<< " " << spt_marks << setw ( 4 )<< " " << ppl_marks << setw ( 4 )<< " "
<< dms_marks << setw ( 4 )<< " " <<se_marks << setw ( 4 )<< " " <<mp_marks << setw( 4 ) << " " <<per << setw ( 6 )<<" " << grade<< endl ;
}


int student :: retrollno ()
{
return rollno ;
}


//*************************************************************** // function declaration //****************************************************************
void write_student (); //write the record in binary file
void display_all (); //read all records from binary file
void display_sp ( int ); //accept rollno and read record from binary file
void modify_student ( int); //accept rollno and update record of binary file
void delete_student ( int); //accept rollno and delete selected records from binary file
void class_result (); //display all records in tabular format from binary file
void result (); //display result menu
void intro (); //display welcome screen
void entry_menu (); //display entry menu on screen


//*************************************************************** // THE MAIN FUNCTION OF PROGRAM //****************************************************************

int main ()
{
char ch ;
cout . setf ( ios :: fixed| ios:: showpoint );
cout << setprecision( 2 ); // program outputs decimal number to two decimal places
clrscr ();
intro ();
do
{
clrscr ();
cout << "\n\n\n\tMAIN MENU" ;
cout << "\n\n\t01. RESULT MENU" ;
cout << "\n\n\t02. ENTRY/EDIT MENU" ;
cout << "\n\n\t03. EXIT" ;
cout << "\n\n\tPlease Select Your Option (1-3) " ;
cin>> ch ;
clrscr ();
switch ( ch )
{
case '1' : result ();
break;
case '2' : entry_menu ();
break;
case '3' : exit(0);
break;
default : cout << "\a" ;
}
}
while ( ch != '3' );
return 0 ;
}
//*************************************************************** // function to write in file //****************************************************************
void write_student ()
{
student st ;
ofstream outFile ;
outFile. open ( "student.doc" , ios :: binary |ios :: app);
st . getdata();
outFile. write (( char *) & st , sizeof ( student));
outFile. close ();
cout << "\n\nStudent record Has Been Created " ;
cin . ignore ();
getch (); }

//*************************************************************** // function to read all records from file //****************************************************************
void display_all ()
{
student st ;
ifstream inFile ;
inFile . open ( "student.doc" , ios :: binary );
if (! inFile )
{
cout << "File could not be open !! Press any Key..." ;
getch();
return ;
}
cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n" ;
while ( inFile . read (( char *) & st , sizeof ( student)))
{
st . showdata ();
cout << "\n\n====================================\n" ;
}
inFile . close();
getch ();
}

//*************************************************************** // function to read specific record from file //****************************************************************
void display_sp ( int n )
{
student st ;
ifstream inFile ;
inFile . open ( "student.doc" , ios :: binary );
if (! inFile )
{
cout << "File could not be open !! Press any Key..." ;
getch();
return ;
}
int flag = 0 ;
while ( inFile . read (( char *) & st , sizeof ( student)))
{
if ( st . retrollno ()== n )
{
st .showdata ();
flag = 1 ;
}
}
inFile . close();
if ( flag == 0 )
cout << "\n\nrecord not exist" ;
getch ();
}

//*************************************************************** // function to modify record of file //****************************************************************

void modify_student ( int n )
{
int found = 0 ;
student st ;
fstream File ;
File . open ( "student.doc" ,ios :: binary | ios :: in | ios :: out );
if (! File )
{
cout << "File could not be open !! Press any Key..." ;
getch();
return ;
}
while ( File . read (( char *) & st , sizeof ( student)) && found == 0)
{
if ( st . retrollno ()== n )
{
st . showdata();
cout << "\n\nPlease Enter The New Details of student" << endl ;
st . getdata();
int pos =(- 1 )* sizeof (st );
File . seekp (pos , ios :: cur );
File . write (( char *) & st , sizeof ( student));
cout << "\n\n\t Record Updated" ;
found= 1 ;
}
}
File . close();
if ( found== 0 )
cout << "\n\n Record Not Found " ;
getch ();
}

//*************************************************************** // function to delete record of file //****************************************************************

void delete_student ( int n )
{
student st ;
ifstream inFile ;
inFile . open ( "student.doc" , ios :: binary );
if (! inFile )
{
cout << "File could not be open !! Press any Key..." ;
getch();
return ;
}
ofstream outFile ;
outFile. open ( "Temp.doc" ,ios :: out);
inFile . seekg( 0 , ios:: beg );
while ( inFile . read (( char *) & st , sizeof ( student)))
{
if ( st . retrollno ()!= n )
{
outFile. write(( char *) & st , sizeof ( student));
}
}
outFile. close ();
inFile . close();
remove ( "student.doc" );
rename ( "Temp.doc" , "student.doc" );
cout << "\n\n\tRecord Deleted .." ;
getch ();
}

//*************************************************************** // function to display all students grade report //****************************************************************
void class_result ()
{
student st ;
ifstream inFile ;
inFile . open ( "student.doc" , ios :: binary );
if (! inFile )
{
cout << "File could not be open !! Press any Key..." ;
getch();
return ;
}
cout << "\n\n\t\tALL STUDENTS RESULT \n\n" ;
cout << "===============================================================================\n" ;
cout << "R.No     Name          POC   SPT   PPT   DMS    SE    MP     %age      Grade" << endl ;
cout << "===============================================================================\n" ;
while ( inFile . read (( char *) & st , sizeof ( student)))
{
st . show_tabular ();
}
getch ();
inFile . close(); }
//*************************************************************** // function to display result menu //****************************************************************
void result ()
{
char ch ;
int rno ;
cout << "\n\n\n\tRESULT MENU" ;
cout << "\n\n\n\t1. Class Result" ;
cout << "\n\n\t2. Student Report Card" ;
cout << "\n\n\t3. Back to Main Menu" ;
cout << "\n\n\n\tEnter Choice (1/2/3)? " ;
cin >> ch ;
clrscr ();
switch ( ch )
{
case '1' : class_result (); break ;
case '2' : cout << "\n\n\tEnter Roll Number Of Student : " ;
	   cin >> rno;
	   display_sp ( rno ); break ;
case '3' : break ;
default : cout << "\a" ;
} }
//*************************************************************** // INTRODUCTION FUNCTION //****************************************************************
void intro () {
cout << "\n\n\n\t\t  STUDENT" ;
cout << "\n\n\tMARKS ANALYSIS SYSTEM" ;
cout << "\n\n\t\t  PROJECT" ;
cout << "\n\n\n\tMADE BY : Bharat Chitara" ;
cout << "\n\tCOLLEGE : JIET ( CO-ED ) " ;
cout << "\n\tBRANCH : IT   ";
cout << "\n\tSECTION : F " ;
getch ();
}
//*************************************************************** // ENTRY / EDIT MENU FUNCTION //****************************************************************
void entry_menu ()
{
char ch ;
int num ;
clrscr ();
cout << "\n\n\n\tENTRY MENU" ;
cout << "\n\n\t1.CREATE STUDENT RECORD" ;
cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORDS" ;
cout << "\n\n\t3.SEARCH STUDENT RECORD " ;
cout << "\n\n\t4.MODIFY STUDENT RECORD" ;
cout << "\n\n\t5.DELETE STUDENT RECORD" ;
cout << "\n\n\t6.BACK TO MAIN MENU" ;
cout << "\n\n\tPlease Enter Your Choice (1-6) " ;
cin >> ch ;
clrscr ();
switch ( ch )
{
case '1' : write_student (); break ;
case '2' : display_all (); break ;
case '3' : cout << "\n\n\tPlease Enter The roll number " ; cin >> num;
display_sp (num ); break ;
case '4' : cout << "\n\n\tPlease Enter The roll number " ; cin >> num;
modify_student ( num); break ;
case '5' : cout << "\n\n\tPlease Enter The roll number " ; cin >> num;
delete_student ( num); break ;
case '6' : break;
default: cout << "\a" ; entry_menu ();
}
}
//*************************************************************** // END OF PROJECT //***************************************************************//