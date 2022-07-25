//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

struct student
{
	int rollno;
	char name[80];
	int p_marks, c_marks, m_marks, e_marks, cs_marks;
	float per;
	char grade;
}s;

//****************************************************************
//                   BASIC FUNCTION USED IN PROJECT
//****************************************************************

void calculate()
{
	s.per=(s.p_marks+s.c_marks+s.m_marks+s.e_marks+s.cs_marks)/5;
	if(s.per>=60)
		s.grade='A';
	else if(s.per>=50)
		s.grade='B';
	else if(s.per>=33)
		s.grade='C';
	else
		s.grade='F';
}

void getdata()
{
	printf("\nEnter The roll number of student ");
	scanf("%d",&s.rollno);
	printf("\n\nEnter The Name of student ");
	scanf("%s",&s.name);
	printf("\nEnter The marks in physics out of 100 : ");
	scanf("%d",&s.p_marks);
	printf("\nEnter The marks in chemistry out of 100 : ");
	scanf("%d",&s.c_marks);
	printf("\nEnter The marks in maths out of 100 : ");
	scanf("%d",&s.m_marks);
	printf("\nEnter The marks in english out of 100 : ");
	scanf("%d",&s.e_marks);
	printf("\nEnter The marks in computer science out of 100 : ");
	scanf("%d",&s.cs_marks);
	calculate();
}

void showdata()
{
	printf("\nRoll number of student : %d",s.rollno);
	printf("\nName of student : %s",s.name);
	printf("\nMarks in Physics : %d",s.p_marks);
	printf("\nMarks in Chemistry : %d",s.c_marks);
	printf("\nMarks in Maths : %d",s.m_marks);
	printf("\nMarks in English : %d",s.e_marks);
	printf("\nMarks in Computer Science : %d",s.cs_marks);
	printf("\nPercentage of student is  : %.2f",s.per);
	printf("\nGrade of student is : %c",s.grade);
}

void show_tabular()
{
	printf("\n %d  %s  %d  %d  %d  %d  %d  %.2f  %c",s.rollno,s.name,s.p_marks,s.c_marks,s.m_marks,s.e_marks,s.cs_marks,s.per,s.grade);
}

//***************************************************************
//    	Function Declaration
//****************************************************************

void write_student();		//write the record in binary file
void display_all();		//read all records from binary file
void display_sp(int);		//accept rollno and read record from binary file
void modify_student(int);	//accept rollno and update record of binary file
void delete_student(int);	//accept rollno and delete selected records from binary file
void class_result();		//display all records in tabular format from binary file
void result();			//display result menu
void intro();			//display welcome screen
void entry_menu();		//display entry menu on screen

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{

	printf("\n\t\t ..:: STUDENT ::..");
	printf("\n \t\t    REPORT CARD ");
	printf("\n\t\t      PROJECT ");
	printf("\n CODE BY: PREETI SINGH");
	printf("\n COURSE: BDFT");
	printf("\n SESSION: 2022\n");

	system("pause");
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	char ch;
	int z;
	intro();

	do
	{
		printf(" MAIN MENU ");
		printf("\n1: RESULT ");
		printf("\n2: ENTRY / EDIT ");
		printf("\n3: EXIT ");
		printf("\nPlease Select Your Option (1-3) ");
		ch=getche();

		switch(ch)
		{
			case '1':
				result();
				break;

			case '2':
				entry_menu();
				break;

			case '3':
				break;

			default :
				printf("\a");
		}
	 }while(ch!='3');
	return 0;
}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_student()
{
	FILE *fp;
	fp = fopen ("student.dat","a+b");
	getdata();
	fwrite(&s,sizeof(s),1,fp);
	fclose(fp) ;
	printf("\n\nStudent record Has Been Created ");
	getch();
}

//***************************************************************
//    	function to read all records from file
//****************************************************************

void display_all()
{
	FILE *fp;
	fp = fopen ("student.dat","rb+");
	while(fread (&s,sizeof(s),1,fp) == 1)
	{
		showdata();
		printf("\n\n====================================\n");
	}
	fclose (fp) ;
	getch();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	FILE *fp;
	int flag=0;

	fp = fopen("student.dat","rb+");

	while(fread (&s,sizeof(s),1,fp) == 1)
	{

		if(s.rollno==n)
		{
			 showdata();
			 flag=1;
		}
	}
	fclose (fp) ;
	if(flag==0)
		printf("\n\nrecord not exist");

getch();
}

//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_student(int n)
{
	FILE *fp;
	int pos=-sizeof(s);
		fp = fopen ("student.dat","rb+wb");
//rewind (fp) ;
		while (fread(&s,sizeof(s),1,fp)==1)
		{
			if (s.rollno==n)
			{
				fseek(fp, pos, SEEK_CUR) ;
				getdata();
				fwrite(&s,sizeof(s), 1, fp) ;
				break;
			}
		}
	fclose (fp) ;
	getch();
}


//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_student(int n)
{
	FILE *fp, *ft;

	fp = fopen("student.dat","rb+");
	ft = fopen("temp.dat", "wb+") ;
	rewind (fp);
		while (fread (&s,sizeof(s),1,fp) == 1)
		{
			if (s.rollno!=n)
			{
				fwrite (&s,sizeof(s), 1, ft) ;
			}
		}
		fclose(fp) ;
		fclose(ft) ;

		remove("student.dat");
		rename("temp.dat", "student.dat");

		printf("\n\n\t Record Deleted");

	getch();
}

//***************************************************************
//    	function to display all students grade
//****************************************************************

void class_result()
{
	FILE *fp;
	fp = fopen ("student.dat","rb");
	printf("\n\n\t\tALL STUDENTS RESULT \n\n");
	printf("\n==========================================================\n");
	printf("R.No  Name    P  C  M  E  CS  PER   Grade");
	printf("\n==========================================================\n");
	while (fread (&s, sizeof(s), 1, fp) == 1)
	{
		show_tabular();
	}
	fclose (fp);
	printf("\n");
	getch();
}

//***************************************************************
//    	function to display result menu
//****************************************************************

void result()
{
	char ch;
	int rno, z;

	printf(" RESULT MENU ");
	printf("\n1: CLASS RESULT ");
	printf("\n2: Student Report Card ");
	printf("\n3: Back to Main Menu");
	printf("\nPlease Select Your Option (1-3) ");
	ch=getche();
	switch(ch)
	{
		case '1' :
			class_result();
			break;

		case '2' :
			printf("\n\n\tEnter Roll Number Of Student : ");
			scanf("%d",&rno);
			display_sp(rno);
			break;

		case '3' :
			break;

		default:
			printf("\a");
	}
}

//***************************************************************
//    	ENTRY / EDIT MENU FUNCTION
//****************************************************************

void entry_menu()
{
	char ch;
	int num;

	printf("\n1: CREATE STUDENT RECORD ");
	printf("\n2: DISPLAY ALL STUDENTS RECORDS ");
	printf("\n3: SEARCH STUDENT RECORD ");
	printf("\n4: MODIFY STUDENT RECORD ");
	printf("\n5: DELETE STUDENT RECORD ");
	printf("\n6: BACK TO MAIN MENU ");
	printf("\nEnter your choice:");
	ch=getch();

	switch(ch)
	{
		case '1':
			write_student();
			break;

		case '2':
			display_all();
			break;

		case '3':
			printf("\n\n\tPlease Enter The roll number ");
			scanf("%d",&num);
			display_sp(num);
			break;

		case '4':
			printf("\n\n\tPlease Enter The roll number ");
			scanf("%d",&num);
			modify_student(num);
			break;

		case '5':
			printf("\n\n\tPlease Enter The roll number ");
			scanf("%d",&num);
			delete_student(num);
			break;

		case '6':
			break;

		default:
			printf("\a");
			entry_menu();
	}
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
