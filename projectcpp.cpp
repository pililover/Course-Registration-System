#include <bits/stdc++.h>
using namespace std;

struct Course{
    string courseID;
    string courseName;
    string className;
    string teacherName;
    int credits;
    int maxstudent = 50;
    string day_of_week;
    string session;
    Student *enrolled_students;
};

struct Semester{
    int cursemester; // Semester 1 (Fall), Semester 2 (Summer), and Semester 3 (Autumn).
    string begindate;
    string enddate;
    void create_semester(){
		cout<<"enter start date ";
		cin>>begindate;
		cout<<"enter end date ";
		cin>>enddate;
	}
    Course courses;
    void add_course(){
    	cout<<"enter course ID:";
    	cin>>course.courseID;
    	cout<<"enter course name:";
    	cin>>course.courseName;
    	cout<<"enter class name:"
    	cin>>course.className;
    	cout>>"enter teacher name";
    	cin>>course.teacherName;
    	cout<<"enter credits:";
    	cin>>credits;
    	cout>>"enter number student"
    	cin>>maxstudent;
    	cout<<"enter session:";
    	cin>>session;
	}
};




int main(){

}