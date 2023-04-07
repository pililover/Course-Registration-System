#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

struct Score
{
    int student_id;
    float score;
};
struct Student
{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
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
    Score *scores;
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
    cin>>stmp2;
    Semester *a=ssss->semester_data[current_semester];
    Course *b=nullptr;
    for(int i=0;i<course_num;i++){
        if(a->data_course[i].course_name==stmp2){
            b=a->data_course[i];
            break;
        }
    }
    float new_scores=0;
    cout<<"Enter new scores: ";
    cin>>new_scores;
    for(int i=0; i<b->capacity_student;i++){
        if(b->scores[i]->student_ID==stmp1){
            scrores[i]->score=new_scores;
        }
    }
}