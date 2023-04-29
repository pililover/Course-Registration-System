#include "Schoolyear_header.h"

void push_back_student_to_course(Course *&arr, Student value)
{
    if (arr->size_student == arr->max_students)
    {
        cout << "Maximum of a class: 50 students" << endl;
        return;
    }
    arr->enrolled_student[arr->size_student] = value; // add to the end
    arr->size_student++;
}

void import_students_csv_to_course(SchoolYear *&school_year, string filename, string courseid)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "Can not open file!" << endl;
        return;
    }
    Course *arr = nullptr;
    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
    {
        if (school_year->data_semester[school_year->current_semester].data_course[i].course_id == courseid)
        {
            arr = &(school_year->data_semester[school_year->current_semester].data_course[i]);
            break;
        }
    }
    while (!in.eof())
    {
        Student tmp;
        getline(in, tmp.student_num, ',');
        getline(in, tmp.studentID, ',');
        getline(in, tmp.firstname, ',');
        getline(in, tmp.lastname, ',');
        getline(in, tmp.gender, ',');
        getline(in, tmp.birthday, ',');
        getline(in, tmp.socialID, '\n');
        tmp.score = -1; // To check if there are no score
        tmp.final = -1;
        tmp.midterm = -1;
        tmp.other = -1;
        tmp.gpa_4_year = 0;
        push_back_student_to_course(arr, tmp);
    }
    in.close();
}

void input_student_to_course(SchoolYear *&school_year, string courseid)
{
    Course *arr = nullptr;
    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
    {
        if (school_year->data_semester[school_year->current_semester].data_course[i].course_id == courseid)
        {
            arr = &(school_year->data_semester[school_year->current_semester].data_course[i]);
            break;
        }
    }
    Student tmp;
    cout << "Enter student information" << endl;
    cout << "No: ";
    cin >> tmp.student_num;
    cout << "Student ID: ";
    cin >> tmp.studentID;
    cout << "First name: ";
    cin.ignore();
    getline(cin, tmp.firstname);
    cout << "Last name: ";
    getline(cin, tmp.lastname);
    cout << "Gender: ";
    cin >> tmp.gender;
    cout << "Date of birth: ";
    cin >> tmp.birthday;
    cout << "Social ID: ";
    cin >> tmp.socialID;
    tmp.score = -1; // To check if there are no score
    tmp.final = -1;
    tmp.midterm = -1;
    tmp.other = -1;
    tmp.gpa_4_year = 0;
    push_back_student_to_course(arr, tmp);
}

bool check_course_is_empty(SchoolYear *school_year)
{
    if (school_year->data_semester[school_year->current_semester].course_num == 0)
        return true;
    return false;
}
