#include "Schoolyear_header.h"

void push_back_student_to_class(Classes *&arr, Student value)
{
    if (arr->student_num == arr->student_capacity)
    {
        int new_capacity = arr->student_capacity + 15;
        resize_class(arr, new_capacity);
    }
    arr->data_student[arr->student_num] = value; // add to the end
    arr->student_num++;
}

void import_students_csv_to_class(SchoolYear *&school_year, string classname, string filename)
{
    int index;
    while (!check_classname_in_a_year(*(school_year), classname, index))
    {
        cout << "Not found. Please choose a different name: ";
        cin >> classname;
    }

    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "Can not open file!" << endl;
        return;
    }
    Classes *arr = &(school_year->data_classes[index]);
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
        push_back_student_to_class(arr, tmp);
    }
    in.close();
}

void input_student_to_class(SchoolYear *&school_year, string classname)
{
    int index;
    while (!check_classname_in_a_year(*(school_year), classname, index))
    {
        cout << "Not found. Please choose a different name: ";
        cin >> classname;
    }

    Classes *arr = &(school_year->data_classes[index]);
    Student tmp;
    cout << "Enter student information" << endl;
    cout << "No: ";
    cin >> tmp.student_num;
    cout << "Student ID: ";
    cin >> tmp.studentID;
    cout << "First name: ";
    cin >> tmp.firstname;
    cout << "Last name: ";
    cin >> tmp.lastname;
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
    push_back_student_to_class(arr, tmp);
}

bool check_class_is_empty(SchoolYear *school_year)
{
    if (school_year->class_num == 0)
        return true;
    return false;
}
