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
    int size_student;
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

void import_scoreboard_of_a_course(SchoolYear ssss){
	string stmp;
	cout<<"Enter name course want to import: ";
	cin>>stmp;
	Semester a=ssss.semester_data[ssss.current_semester];
	Course b;
	for(int i=0;i<a.course_num;i++){
		if(a.data_course[i].course_name==stmp){
			b=a.data_course[i];
		}
	}
	
    cout<<"Enter file want to import score: ";
    cin>>stmp;
	ifstream fin;
	fin.open(stmp);
	while (!fin.is_open()){
		cout<<"File want to import not invaluable, enter again: ";
		cin>>stmp;
		fin.open(stmp);
    }
    
    int stt=0;
    b.scores=new Score[b.size_student];     
	int st_id;
	float score_st;
	while(!fin.eof()){
		getline(fin,stmp,',');
        st_id=stoi(stmp);
		getline(fin,stmp,',');
        score_st=stof(stmp);
        b.scores[stt].student_id=st_id;
        b.scores[stt++].score=score_st;
    }
	fin.close();
}