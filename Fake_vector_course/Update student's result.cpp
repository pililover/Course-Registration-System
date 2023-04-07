#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

struct Student
{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
    float score;
};
struct Course
{
    string course_id;
    string course_name;
    string class_name;
    string teacher_name;
    int credits;
    int max_students = 50;
    string day_of_week;
    string session;
    Student *enrolled_student;
    int size_student; //=size_scores
    int capacity_student;  
};
struct Semester
{
    Course *data_course = nullptr;
    string start_day;
    string end_day;
    int course_num = 0;
    int capacity_course = 0;
};
struct Classes
{
    string class_name;
    Student *data_student = nullptr; // dynamic
    int student_num;                 // size
    int student_capacity;
};
struct SchoolYear
{
    string year_name; // Ex:2022-2023???
    Classes *data_classes;
    Semester *semester_data;
    int semester_num = 3;
    int current_semester;
    int class_num;
    int class_capacity;
};

void update_student_result(SchoolYear ssss){
    string stmp1;
    cout<<"Enter student ID: ";
    cin>>stmp1;
    cout<<"Enter name course want to import: ";
    string stmp2;
    cin>>stmp2;
    Semester a=ssss.semester_data[ssss.current_semester];
    Course b;
    for(int i=0;i<a.course_num;i++){
        if(a.data_course[i].course_name==stmp2){
            b=a.data_course[i];
            break;
        }
    }
    float new_scores=0;
    cout<<"Enter new scores: ";
    cin>>new_scores;
    for(int i=0; i<b.capacity_student;i++){
        Student c=b.enrolled_student[i];
        if(c.studentID==stmp1){
            c.score=new_scores;
        }
    }
}