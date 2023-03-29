#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

struct Student{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
    
};

struct Course{
    int course_id;
    string course_name;
    string class_name;
    string teacher_name;
    int credits;
    int max_students=50;
    string day_of_week;
    string session;
    Student *enrolled_student;
    int size_student;
    int capacity_student;
};

struct Semester{
    Course *data_course=nullptr;
    string start_day;
    string end_day;
    int size_course=0;
    int capacity_course=0;
} ;

struct Classes{
    string class_name;
    Student *data_student=nullptr; // dynamic
    int student_num;       // size
    int student_capacity;
};

struct SchoolYear{
    string year_name;   //Ex:2022-2023???
    Classes *data_classes=nullptr;
    Semester *data_semester1=nullptr ;
    Semester *data_semester2=nullptr;
    Semester *data_semester3=nullptr ;
    int class_num;
    int class_capacity;
};

void view_list_of_course(Course ccc){
	for(int i=0; i<ccc.size_student; i++){
		cout<<ccc.enrolled_student[i].student_num<<" ";
		cout<<ccc.enrolled_student[i].studentID<<" ";
		cout<<ccc.enrolled_student[i].firstname<<" ";
		cout<<ccc.enrolled_student[i].lastname<<" ";
		cout<<ccc.enrolled_student[i].gender<<" ";
		cout<<ccc.enrolled_student[i].birthday<<" ";
		cout<<ccc.enrolled_student[i].socialID<<" ";
	}
}