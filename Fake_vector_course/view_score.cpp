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

struct Student{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
    
};

struct Student
{
    string student_num; // so thu tu cua tung hoc sinh
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
    int max_students; // student capacity in a course
    string day_of_week;
    string session;
    Student *enrolled_student;
    int size_student = 0; // so luong hoc sinh
    Score* scores;
};

struct Semester
{
    Course *data_course;
    int course_num;
    int course_capacity;
    int semester_id;
    string start_day;
    string end_day;
};

struct Classes
{
    string class_name;
    Student *data_student; // dynamic
    int student_num = 0;   // size
    int student_capacity;
};

struct SchoolYear
{
    string year_name;
    Classes *data_classes;
    Semester *data_semester;
    int semester_num = 0;
    int current_semester = 0;
    int semester_capacity = 0;
    int class_num = 0;
    int class_capacity;
};

//The show variable is student ID value
//This function output the score of a semester to csv file
void show_score_semester_student(Semester semester, string show){
    string temp = show + "_scores.csv";
    ofstream in(temp, ios::app);

    //The first line in csv is the courses names
    for (int i = 0; i < semester.course_num - 1; i++){
        in<<semester.data_course[i].course_name<<',';
        cout<<semester.data_course[i].course_name<<',';
    }
    in<<semester.data_course[semester.course_num - 1].course_name<<endl;
    cout<<semester.data_course[semester.course_num - 1].course_name<<endl;

    //The second line is the score
    for (int i = 0; i < semester.course_num - 1; i++){
        int flag = 1;
        for (int j = 0; j < semester.data_course[i].size_student; j++){
            if (semester.data_course[i].enrolled_student[j].studentID == show){
                flag = 0;
                in<<semester.data_course[i].scores[j].score<<',';
                cout<<semester.data_course[i].scores[j].score<<',';
            }
        }
        
        if (flag == 1){
            in<<'X'<<',';
            cout<<'X'<<',';
        }
    }
    int flag = 1;
    for (int j = 0; j < semester.data_course[semester.course_num - 1].size_student; j++){
        if (semester.data_course[semester.course_num - 1].enrolled_student[j].studentID == show){
            flag = 0;
            in<<semester.data_course[semester.course_num - 1].scores[j].score<<endl;
            cout<<semester.data_course[semester.course_num - 1].scores[j].score<<endl;
        }
    }
        
    if (flag == 1){
        in<<'X'<<endl;
        cout<<'X'<<endl;
    }

    in.close();
}

//This function output the entire school year and gpa to csv file
void show_score_schoolyear_student(SchoolYear* year, string show){
    string temp = show + "_scores.csv";

    double gpa = 0;
    double n = 0;
    
    if (year->data_semester){
        ofstream in(temp, ios::app);
        in<<"Semester "<<year->current_semester + 1<<endl;
        in.close();
        cout<<"Semester "<<year->current_semester + 1<<endl;

        show_score_semester_student(year->data_semester[year->current_semester], show);

        for (int j = 0; j < year->data_semester[year->current_semester].course_num; j++){
            for (int z = 0; z < year->data_semester[year->current_semester].data_course[j].size_student; z++){
                if (year->data_semester[year->current_semester].data_course[j].enrolled_student[z].studentID == show){
                    gpa += year->data_semester[year->current_semester].data_course[j].scores[z].score;
                    n++;
                }
            }
        }
        ofstream in(temp, ios::app);

        in<<"Overall GPA,"<<gpa/n;

        in.close();
        cout<<"Overall GPA,"<<gpa/n;
    }
}

void show_scores_class(SchoolYear* year, Classes* classes){
    string temp = classes->class_name + "_scores.csv";
    double gpa = 0;
    double n = 0;
    
    
    ofstream in(temp, ios::app);
    in<<"Class "<<classes->class_name<<endl;
    cout<<"Class "<<classes->class_name<<endl;
    in.close();
    

    for (int i = 0; i < classes->student_num - 1; i++){
        ofstream in(temp, ios::app);
        in<<classes->data_student[i].studentID<<", "<<classes->data_student[i].firstname<<", "<<classes->data_student[i].lastname<<endl;
        in.close();

        show_score_semester_student(year->data_semester[year->current_semester], classes->data_student[i].studentID);

        for (int j = 0; j < year->data_semester[year->current_semester].course_num; j++){
            for (int z = 0; z < year->data_semester[year->current_semester].data_course[j].size_student; z++){
                if (year->data_semester[year->current_semester].data_course[j].enrolled_student[z].studentID == classes->data_student[i].studentID){
                    gpa += year->data_semester[year->current_semester].data_course[j].scores[z].score;
                    n++;
                }
            }
        }
        ofstream in(temp, ios::app);

        in<<"Overall GPA,"<<gpa/n;

        in.close();
        cout<<"Overall GPA,"<<gpa/n;
    }
}