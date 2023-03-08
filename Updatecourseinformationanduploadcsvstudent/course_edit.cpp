#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

using namespace std;

struct Student
{
    int student_id;
    string first_name;
    string last_name;
    string gender;
    string birth;
    string social_id;
};

// Struct to represent a course
struct Course
{
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

// Struct to represent a semester
struct Semester
{
    int semester_num; // 1,2,3
    string start_date;
    string end_date;
    Course *courses;
    int num_courses;
    Semester *next;
};

// Struct to represent a school year
struct schoolyear
{
    string year_name;
    Semester *semesters;
    int num_cursemesters;
};

struct user
{
    string username;
    string password;
    int type_of_user;
    string fullname;
};

struct node_student
{
    Student* data;
    node_student* next;
};

node_student* head = nullptr;

void upload_csv_stu(node_student* &head){
    string csv;
    cout<<"Input the csv file name (eg: name.csv): ";
    cin>>csv;

    ifstream in(csv);

    if (!in.is_open()){
        cout<<"Canot open file!"<<endl;
    }
    else{
        //Variables for students in course
        head = new node_student;
        node_student* temp = head;

        int temp_student_id;
        string str_student_id;
        string temp_first_name;
        string temp_last_name;
        string temp_gender;
        string temp_birth;
        string temp_social_id;

        while (!in.eof()){
            //Getting students in that from csv file
            getline(in, str_student_id,',');
            temp_student_id = stoi(str_student_id);
            getline(in, temp_first_name,',');
            getline(in, temp_last_name,',');
            getline(in, temp_gender,',');
            getline(in, temp_birth,',');
            getline(in, temp_social_id,',');
        
            head->data->student_id = temp_student_id;
            head->data->first_name = temp_first_name;
            head->data->last_name = temp_last_name;
            head->data->gender = temp_gender;
            head->data->birth = temp_birth;
            head->data->social_id = temp_social_id;

            head->next=new node_student;
            head=head->next;

            cout<<temp_student_id<<", "
                <<temp_first_name<<", "
                <<temp_last_name<<", "
                <<temp_gender<<", "
                <<temp_birth<<", "
                <<temp_social_id<<endl;
        }
        head = temp;
        temp = nullptr;
    }

    in.close();
}

void update_course(Course the_course){
    string course_input;
    cout<<"Input the courseID (eg: courseID.csv): ";
    cin>>course_input;

    ifstream in(course_input);

    //Variables for course information
    string temp_courseID;
    string temp_courseName;
    string temp_className;
    string temp_teacherName;
    string str_credits;
    int temp_credits;
    string str_maxstudent;
    int temp_maxstudent = 50;
    string temp_day_of_week;
    string temp_session;
    Student *senrolled_student;
    string str_num_student;
    int temp_num_students;

    //Getting course information from csv file
    getline(in, temp_courseID, ',');
    getline(in, temp_courseName, ',');
    getline(in, temp_className, ',');
    getline(in, temp_teacherName, ',');
    getline(in, str_credits, ',');
    temp_credits = stoi(str_credits);
    getline(in, str_maxstudent, ',');
    temp_maxstudent = stoi(str_maxstudent);
    getline(in, temp_day_of_week, ',');
    getline(in, temp_session, ',');
    getline(in, str_num_student, ',');
    temp_num_students = stoi(str_num_student);

    //Variables for students in course
    head = new node_student;
    node_student* temp = head;

    int temp_student_id;
    string str_student_id;
    string temp_first_name;
    string temp_last_name;
    string temp_gender;
    string temp_birth;
    string temp_social_id;
    
    //Getting students in that from csv file
    while(!in.eof()){
        getline(in, str_student_id,',');
        temp_student_id = stoi(str_student_id);
        getline(in, temp_first_name,',');
        getline(in, temp_last_name,',');
        getline(in, temp_gender,',');
        getline(in, temp_birth,',');
        getline(in, temp_social_id,',');
        
        head->data->student_id = temp_student_id;
        head->data->first_name = temp_first_name;
        head->data->last_name = temp_last_name;
        head->data->gender = temp_gender;
        head->data->birth = temp_birth;
        head->data->social_id = temp_social_id;

        head->next=new node_student;
        head=head->next;
    }
    head = temp;
    temp = nullptr;

    in.close();
    
    //Updating course information
    int choice = -1;
    int flag = 0;
    while (choice != 0){
        cout<<"What information of the course do you want to changed?"<<endl;
        cout<<"Enter 1 to change the course ID."<<endl;
        cout<<"Enter 2 to change the course name."<<endl;
        cout<<"Enter 3 to change the class name."<<endl;
        cout<<"Enter 4 to change the teacher name."<<endl;
        cout<<"Enter 5 to change the course credit."<<endl;
        cout<<"Enter 6 to change the course max students."<<endl;
        cout<<"Enter 7 to change the course day of week."<<endl;
        cout<<"Enter 8 to change the course sessions."<<endl;
        cout<<"Enter 9 to add a student to course."<<endl;
        cout<<"Enter 10 to remove a student from course."<<endl;
        cout<<"Enter 11 to remove course."<<endl;
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter the new course ID: ";
                cin>>temp_courseID;
                break;

            case 2:
                cout<<"Enter the new course name: ";
                cin>>temp_courseName;
                break;

            case 3:
                cout<<"Enter the new class name: ";
                cin>>temp_className;
                break;

            case 4:
                cout<<"Enter the new teacher name: ";
                cin>>temp_teacherName;
                break;

            case 5:
                cout<<"Enter the new credit: ";
                cin>>temp_credits;
                break;

            case 6:
                cout<<"Enter the new max students: ";
                cin>>temp_maxstudent;
                break;

            case 7:
                cout<<"Enter the new days of week: ";
                cin>>temp_day_of_week;
                break;

            case 8:
                cout<<"Enter the new sessions: ";
                cin>>temp_session;
                break;

            case 9:
                if (temp_num_students < temp_maxstudent){
                    node_student* temp = head;
                    while (temp->next){
                        temp = temp->next;
                    }
                    temp->next = new node_student;
                    temp = temp->next;

                    cout<<"Enter the student ID: ";
                    cin>>temp_student_id;
                    temp->data->student_id = temp_student_id;
                    cout<<"Enter the student first name: ";
                    cin>>temp_first_name;
                    temp->data->first_name = temp_first_name;
                    cout<<"Enter the student last name: ";
                    cin>>temp_last_name;
                    temp->data->last_name = temp_last_name;
                    cout<<"Enter the student gender: ";
                    cin>>temp_gender;
                    temp->data->gender = temp_gender;
                    cout<<"Enter the student date of birth: ";
                    cin>>temp_birth;
                    temp->data->birth = temp_birth;
                    cout<<"Enter the student social ID: ";
                    cin>>temp_social_id;
                    temp->data->social_id = temp_social_id;

                    temp->next = nullptr;

                    temp_num_students++;
                }
                break;

            case 10:
                cout<<"Enter the student ID: ";
                cin>>temp_student_id;

                node_student* temp = head;
                while (temp->next && temp->next->data->student_id != temp_student_id){
                    temp = temp->next;
                }
                if (temp->next && temp->next->data->student_id == temp_student_id){
                    node_student* cur = temp->next;
                    temp->next = cur->next;
                    delete cur->data;
                    delete cur;
                }

                temp_num_students--;
                break;

            case 11:
                cout<<"Course has been deleted";
                choice = 0;
                flag = 1;
                break;

            case 0:
                cout<<"Ending updating course information.";
                break;

            default:
                cout<<"Invalid input! Please enter an option.";
                break;
        }
    }

    //Input the information into a new csv file
    string output_course = temp_courseID + ".txt";
    ofstream out(output_course);

    if (flag == 0){
        out<<temp_courseID<<','
            <<temp_courseName<<','
            <<temp_className<<','
            <<temp_teacherName<<','
            <<temp_credits<<','
            <<temp_maxstudent<<','
            <<temp_day_of_week<<','
            <<temp_session<<','
            <<temp_num_students<<','<<endl;

        node_student* cur = head;
        while (cur != nullptr){
            out<<cur->data->student_id<<','
                <<cur->data->first_name<<','
                <<cur->data->last_name<<','
                <<cur->data->gender<<','
                <<cur->data->birth<<','
                <<cur->data->social_id<<',';
            cur = cur->next;
        }
    }

    while (head != nullptr){
        node_student* cur = head;
        head = head->next;
        delete cur->data;
        delete cur;
    }

    out.close();
}