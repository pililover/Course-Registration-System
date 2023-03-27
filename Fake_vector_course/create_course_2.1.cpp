#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

#include <iostream>
#include <string>
#include <fstream>
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
    // SchoolYear *next;
};

void recap_course(Semester *s, int new_capacity){
    Course *s_new=new Course[new_capacity];
    for(int i=0; i<s->size_course; i++) s_new[i]=s->data_course[i];
    delete[] s->data_course;
    s->data_course=s_new;
    s->capacity_course=new_capacity;
}

void pushback_course(Semester* s, Course val){
    if(s->capacity_course==s->size_course) recap_course(s,s->capacity_course+15);
    s->size_course=s->size_course++;
    s->data_course[s->size_course]=val;
}

void add_course2semester_from_(Semester *s){
    Course val;
    cout << setw(40) << setfill(' ') << "ADD COURSE TO SEMETER" << endl;
    cout << "Enter the course information: " << endl;
    cout << "Course ID: ";
    cin >> val.course_id;
    cout << "Name of course: ";
    cin >> val.course_name;
    cout << "Class name: ";
    cin >> val.class_name;
    cout << "Name of teacher: ";
    cin >> val.teacher_name;
    cout << "Number of credit: ";
    cin >> val.credits;
    cout << "Day of week: ";
    cin >> val.day_of_week;
    cout << "Session of course: ";
    cin >> val.session;
    pushback_course(s,val);
}