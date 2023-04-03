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
    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "Can not open file!" << endl;
        return;
    }
    Classes *arr = nullptr;
    for (int i = 0; i < school_year->class_num; i++)
    {
        if (school_year->data_classes[i].class_name == classname)
        {
            arr = &(school_year->data_classes[i]);
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
        push_back_student_to_class(arr, tmp);
    }
    in.close();
}

void input_student_to_class(SchoolYear *&school_year, string classname)
{
    Classes *arr = NULL;
    for (int i = 0; i < school_year->class_num; i++)
    {
        if (school_year->data_classes[i].class_name == classname)
        {
            arr = &(school_year->data_classes[i]);
            break; // moi add
        }
    }
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
    push_back_student_to_class(arr, tmp);
}

bool check_class_is_empty(SchoolYear *school_year)
{
    if (school_year->class_num == 0)
        return true;
    return false;
}

void view_student_in_class(SchoolYear *school_year)
{
    for (int i = 0; i < school_year->class_num; i++)
    {
        cout << school_year->data_classes[i].class_name << endl;
        if (school_year->data_classes[i].student_num != 0)
        {
            for (int j = 0; j < school_year->data_classes[i].student_num; j++)
            {
                cout << school_year->data_classes[i].data_student[j].studentID << " \t"
                     << school_year->data_classes[i].data_student[j].firstname << " \t"
                     << school_year->data_classes[i].data_student[j].lastname << endl;
            }
        }
    }
}