#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

struct string_vectors{
    string* data;
    int size;
    int capacity;
};

void init(string_vectors *&arr){
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void resize(string_vectors *&arr, int new_capacity){
    string *new_data = new string[new_capacity];
    for (int i = 0; i < arr->size; i++)   new_data[i] = arr->data[i];
    delete[] arr->data;
    arr->data = new_data;
    arr->capacity = new_capacity;
}

void push_back(string_vectors *&arr, string value){
    if (arr->size == arr->capacity){
        int new_capacity = (arr->capacity == 0) ? 1 : arr->capacity + 15;
        resize(arr, new_capacity);
    }
    arr->data[arr->size] = value;
    arr->size++;
}

void pop_back(string_vectors *&arr){
    if (arr->size > 0){
        arr->size--;
        if (arr->size * 4 <= arr->capacity)
        {
            int new_capacity = arr->capacity / 2;
            if (new_capacity < 1)
            {
                new_capacity = 1;
            }
            resize(arr, new_capacity);
        }
    }
}

void erase(string_vectors *&arr, int index)
{
    if (index < 0 || index >= arr->size)
    {
        return;
    }
    for (int i = index + 1; i < arr->size; i++)
    {
        arr->data[i - 1] = arr->data[i];
    }
    pop_back(arr);
}
struct student
{
    string_vectors* student_num;
    string_vectors* studentID;
    string_vectors* firstname;
    string_vectors* lastname;
    string_vectors* gender;
    string_vectors* birthday;
    string_vectors* socialID;
};

void upload_csv_stu(student &upload){
    string csv;
    cout<<"Input the csv file name (eg: name.csv): ";
    cin>>csv;

    ifstream in(csv);

    if (!in.is_open()) cout<<"Canot open file!"<<endl;
    else{
        //Variables for students in course
        init(upload.student_num);
        init(upload.studentID);
        init(upload.firstname);
        init(upload.lastname);
        init(upload.gender);
        init(upload.birthday);
        init(upload.socialID);

        string temp_student_num;
        string temp_student_id;
        string temp_first_name;
        string temp_last_name;
        string temp_gender;
        string temp_birth;
        string temp_social_id;

        while (!in.eof()){
            //Getting students in that from csv file
            getline(in, temp_student_num,',');
            getline(in, temp_student_id,',');
            getline(in, temp_first_name,',');
            getline(in, temp_last_name,',');
            getline(in, temp_gender,',');
            getline(in, temp_birth,',');
            getline(in, temp_social_id,',');
        
            push_back(upload.student_num, temp_student_num);
            push_back(upload.studentID, temp_student_id);
            push_back(upload.firstname, temp_first_name);
            push_back(upload.lastname, temp_last_name);
            push_back(upload.gender, temp_gender);
            push_back(upload.birthday, temp_birth);
            push_back(upload.socialID, temp_social_id);

            cout<<temp_student_num<<", "
                <<temp_student_id<<", "
                <<temp_first_name<<", "
                <<temp_last_name<<", "
                <<temp_gender<<", "
                <<temp_birth<<", "
                <<temp_social_id<<endl;
        }
    }

    in.close();
}

void update_course(){
    string course_input;
    cout<<"Input the courseID (eg: courseID.csv): ";
    cin>>course_input;

    ifstream in(course_input);

    if (!in)
    {
        cout << "Cannot open file" << endl;
        return;
    }
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
    student *senrolled_student;
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

    student course_students;
    init(course_students.student_num);
    init(course_students.studentID);
    init(course_students.firstname);
    init(course_students.lastname);
    init(course_students.gender);
    init(course_students.birthday);
    init(course_students.socialID);

    string temp_student_num;
    string temp_student_id;
    string temp_first_name;
    string temp_last_name;
    string temp_gender;
    string temp_birth;
    string temp_social_id;
    int i = 0;

     while (!in.eof()){
        //Getting students in that from csv file
        getline(in, temp_student_num,',');
        getline(in, temp_student_id,',');
        getline(in, temp_first_name,',');
        getline(in, temp_last_name,',');
        getline(in, temp_gender,',');
        getline(in, temp_birth,',');
        getline(in, temp_social_id,'\n');
        
        push_back(course_students.student_num, temp_student_num);
        push_back(course_students.studentID, temp_student_id);
        push_back(course_students.firstname, temp_first_name);
        push_back(course_students.lastname, temp_last_name);
        push_back(course_students.gender, temp_gender);
        push_back(course_students.birthday, temp_birth);
        push_back(course_students.socialID, temp_social_id);

        i++;
    }

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
                    cout<<"Enter the student number: ";
                    cin>>temp_student_num;
                    push_back(course_students.student_num, temp_student_num);
                    cout<<"Enter the student ID: ";
                    cin>>temp_student_id;
                    push_back(course_students.studentID, temp_student_id);
                    cout<<"Enter the student first name: ";
                    cin>>temp_first_name;
                    push_back(course_students.firstname, temp_first_name);
                    cout<<"Enter the student last name: ";
                    cin>>temp_last_name;
                    push_back(course_students.lastname, temp_last_name);
                    cout<<"Enter the student gender: ";
                    cin>>temp_gender;
                    push_back(course_students.gender, temp_gender);
                    cout<<"Enter the student date of birth: ";
                    cin>>temp_birth;
                    push_back(course_students.birthday, temp_birth);
                    cout<<"Enter the student social ID: ";
                    cin>>temp_social_id;
                    push_back(course_students.socialID, temp_social_id);
                    temp_num_students++;
                    cout<<"Adding student completed"<<endl;
                }
                else{
                    cout<<"The number of student had exceeded the max number of student"<<endl;
                }
                break;

            case 10:
                cout<<"Enter the student ID: ";
                cin>>temp_student_id;

                int x = 0;
                while (x < i && course_students.studentID->data[x] != temp_student_id)
                    x++;
                erase(course_students.student_num, x);
                erase(course_students.studentID, x);
                erase(course_students.firstname, x);
                erase(course_students.lastname, x);
                erase(course_students.gender, x);
                erase(course_students.birthday, x);
                erase(course_students.socialID, x);

                temp_num_students--;

                cout<<"Erase student completed"<<endl;

                if (x >= i)
                    cout<<"Student ID does not exist"<<endl;

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
                cout<<"Invalid input! Please enter another option.";
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

        for (int n = 0; n < i; n++){
            out<<course_students.student_num->data[n]<<','
                <<course_students.studentID->data[n]<<','
                <<course_students.firstname->data[n]<<','
                <<course_students.lastname->data[n]<<','
                <<course_students.gender->data[n]<<','
                <<course_students.birthday->data[n]<<','
                <<course_students.socialID->data[n]<<'\n';
        }
    }

    delete[] course_students.student_num;
    delete[] course_students.studentID;
    delete[] course_students.firstname;
    delete[] course_students.lastname;
    delete[] course_students.gender;
    delete[] course_students.birthday;
    delete[] course_students.socialID;

    out.close();

    if (flag == 1){
        int n;
        n = output_course.length();
        char* temp = new char[n+1];
        strcpy(temp, output_course.c_str());
        remove(temp);
        delete[] temp;
    }
}