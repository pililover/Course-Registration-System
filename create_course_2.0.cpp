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
    string course_id;
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

void recapacity_student_in_a_course(Course*& course_need_add_student_now, int new_capacity){
    Student* array_student_need_add_now=course_need_add_student_now->enrolled_student;
    Student *new_array=new Student[new_capacity];
    for (int i = 0; i < course_need_add_student_now->size_student; i++)   new_array[i] = array_student_need_add_now[i];
    delete[] array_student_need_add_now;
    course_need_add_student_now->enrolled_student = new_array;
    course_need_add_student_now->capacity_student = new_capacity;
}

void push_back_student_to_course(Course* &course_need_add_student_now, Student &value){
    if(course_need_add_student_now->size_student==course_need_add_student_now->capacity_student){
        int new_capacity = (course_need_add_student_now->capacity_student == 0) ? 1 : course_need_add_student_now->capacity_student + 15;
        recapacity_student_in_a_course(course_need_add_student_now, new_capacity);
    }
    course_need_add_student_now->size_student++;
    course_need_add_student_now->enrolled_student[course_need_add_student_now->size_student] = value;
}

void upload_csv_stu_to_course(Course* &upload){
    string csv;
    cout<<"Input the csv file name (eg: name.csv): ";
    cin>>csv;

    ifstream fin(csv);

    if (!fin.is_open()) {
        cout<<"The file don't exist!"<<endl;
        return;
    }
    Student tmp; 

    while (!fin.eof()){
        getline(fin, tmp.student_num,',');
        getline(fin, tmp.studentID,',');
        getline(fin, tmp.firstname,',');
        getline(fin, tmp.lastname,',');
        getline(fin, tmp.gender,',');
        getline(fin, tmp.birthday,',');
        getline(fin, tmp.socialID,',');
        
        push_back_student_to_course(upload, tmp);
        }

    fin.close();
}

/// course last semester still exist
bool create_new_course_to_new_semester(SchoolYear &cur_year){
    if(cur_year.data_semester1->data_course && cur_year.data_semester2->data_course && cur_year.data_semester3->data_course) return 0;
    Semester *cur_semester=nullptr;                                      //auto check semester
    if(cur_year.data_semester1)  cur_semester=cur_year.data_semester1; 
    if(cur_year.data_semester2)  cur_semester=cur_year.data_semester2;  
    if(cur_year.data_semester3)  cur_semester=cur_year.data_semester3; 

    cur_semester->data_course=new Course();
    upload_csv_stu_to_course(cur_semester->data_course);
    return 1;
}