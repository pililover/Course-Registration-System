#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

struct Student{
    int student_id;
    string first_name;
    string last_name;
    string gender;
    string birth;
    string social_id;
};

struct Course{
    int course_id;
    string course_name;
    int credits;
    int max_students = 50;
    string class_name;
    string teacher_name;
    string day_of_week;
    string session;
    Student *enrolled_students;
    int num_students;
    Course *next;
};

struct Semester{
    int semester_num; // 1,2,3
    string start_date;
    string end_date;
    Course *courses;
    int num_courses;
    Semester *next;
};

struct Schoolyear{
    string year_name;
    Semester *semesters;
    int num_cursemesters;
	Schoolyear* next;
};

void add_semester(Schoolyear* &school_year){
	string ss;
	cout<<"nhap nam muon hoc them hoc ki";
	cin>>ss;
	Schoolyear *year_need_add_semester = school_year;
	while(year_need_add_semester && year_need_add_semester->year_name!=ss) year_need_add_semester=year_need_add_semester->next;
	if(!year_need_add_semester) {
		cout<<"nam hoc muon them hoc ki vao hien khong ton tai trong he thong";
		return;
	}

	cout<<"Nhap hoc ki muon them vao";
	int x; 
	cin>>x;
	Semester* semester_need_add=year_need_add_semester->semesters;
	if(!semester_need_add) {
		semester_need_add=new Semester();
	}
	else{
		while(!semester_need_add){
			if(semester_need_add->semester_num==x) {
				cout<<"hoc ki da co san";
				return;
			}
			if(!semester_need_add->next) semester_need_add=semester_need_add->next;
		}
		semester_need_add->next=new Semester();
		semester_need_add=semester_need_add->next;
	}

	semester_need_add->next=nullptr;	
	semester_need_add->semester_num=x;
	cout<<"nhap ngay bat dau hoc ki";
	cin>>ss;
	semester_need_add->start_date=ss;
	cout<<"nhap ngay ket thuc hoc ki";
	cin>>ss;
	semester_need_add->end_date=ss;
}