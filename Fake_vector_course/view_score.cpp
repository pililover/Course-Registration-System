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
    Score *scores;
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
    int semester1_size;
    int semester2_size;
    int semester3_size;
};

//The show variable is student ID value
void show_score_semester_student(Semester semester, string show){
    string temp = show + "_scores.csv";
    ofstream in(temp, ios::app);

    //The first line in csv is the courses names
    for (int i = 0; i < semester.size_course - 1; i++){
        in<<semester.data_course[i].course_name<<',';
    }
    in<<semester.data_course[semester.size_course - 1].course_name<<endl;

    //The second line is the score
    for (int i = 0; i < semester.size_course - 1; i++){
        int flag = 1;
        for (int j = 0; j < semester.data_course[i].size_student; j++){
            if (semester.data_course[i].enrolled_student[j].studentID == show){
                flag = 0;
                in<<semester.data_course[i].scores[j].score<<',';
            }
        }
        
        if (flag == 1){
            in<<'X'<<',';
        }
    }
    int flag = 1;
    for (int j = 0; j < semester.data_course[semester.size_course - 1].size_student; j++){
        if (semester.data_course[semester.size_course - 1].enrolled_student[j].studentID == show){
            flag = 0;
            in<<semester.data_course[semester.size_course - 1].scores[j].score<<endl;
        }
    }
        
    if (flag == 1){
        in<<'X'<<endl;
    }

    in.close();
}


void show_score_schoolyear_student(SchoolYear year, string show){
    string temp = show + "_scores.csv";
    ofstream in(temp, ios::app);

    if (year.semester1_size > 0){
        in<<year.year_name<<endl;
    }

    in.close();

    double gpa = 0;
    double n = 0;
    for (int i = 0; i < year.semester1_size; i++){

        ofstream in(temp, ios::app);
        in<<"First year semeter "<<i<<endl;
        in.close();

        show_score_semester_student(year.data_semester1[i], show);

        for (int j = 0; j < year.data_semester1[i].size_course; j++){
            for (int z = 0; z < year.data_semester1[i].data_course[j].size_student; z++){
                if (year.data_semester1[i].data_course[j].enrolled_student[z].studentID == show){
                    gpa += year.data_semester1[i].data_course[j].scores[z].score;
                    n++;
                }
            }
        }
    }

    for (int i = 0; i < year.semester2_size; i++){

        ofstream in(temp, ios::app);
        in<<"Second year semeter "<<i<<endl;
        in.close();

        show_score_semester_student(year.data_semester2[i], show);

        for (int j = 0; j < year.data_semester2[i].size_course; j++){
            for (int z = 0; z < year.data_semester2[i].data_course[j].size_student; z++){
                if (year.data_semester2[i].data_course[j].enrolled_student[z].studentID == show){
                    gpa += year.data_semester2[i].data_course[j].scores[z].score;
                    n++;
                }
            }
        }
    }

    for (int i = 0; i < year.semester3_size; i++){

        ofstream in(temp, ios::app);
        in<<"Third year semeter "<<i<<endl;
        in.close();

        show_score_semester_student(year.data_semester3[i], show);
        
        for (int j = 0; j < year.data_semester3[i].size_course; j++){
            for (int z = 0; z < year.data_semester3[i].data_course[j].size_student; z++){
                if (year.data_semester3[i].data_course[j].enrolled_student[z].studentID == show){
                    gpa += year.data_semester3[i].data_course[j].scores[z].score;
                    n++;
                }
            }
        }
    }

    ofstream in(temp, ios::app);

    in<<"Overall GPA,"<<gpa/n;

    in.close();
}