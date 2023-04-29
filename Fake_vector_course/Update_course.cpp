#include "Schoolyear_header.h"

void update_course(Course *&update, SchoolYear *&year)
{
    // Updating course information
    int flag = -1;
    while (flag != 0)
    {
        cout << "What information of the course do you want to changed?" << endl;
        cout << "Enter 1 to change the course ID." << endl;
        cout << "Enter 2 to change the course name." << endl;
        cout << "Enter 3 to change the class name." << endl;
        cout << "Enter 4 to change the teacher name." << endl;
        cout << "Enter 5 to change the course credit." << endl;
        cout << "Enter 6 to change the course max students." << endl;
        cout << "Enter 7 to change the course day of week." << endl;
        cout << "Enter 8 to change the course sessions." << endl;
        cout << "Enter 9 to add a student to course." << endl;
        cout << "Enter 10 to remove a student from course." << endl;
        cout << "Enter 11 to remove course." << endl;
        cout << "Enter 0 to exit." << endl;
        cout << "Option: ";
        cin >> flag;
        string temp_remove;
        switch (flag)
        {
        case 1:
            cout << "Enter the new course ID: ";
            cin >> update->course_id;
            break;

        case 2:
            cout << "Enter the new course name: ";
            cin >> update->course_name;
            break;

        case 3:
            cout << "Enter the new class name: ";
            cin >> update->class_name;
            break;

        case 4:
            cout << "Enter the new teacher name: ";
            cin >> update->teacher_name;
            break;

        case 5:
            cout << "Enter the new credit: ";
            cin >> update->credits;
            break;

        case 6:
            cout << "Enter the new max students: ";
            cin >> update->size_student;
            update->size_student = update->size_student;
            break;

        case 7:
            cout << "Enter the new days of week: ";
            cin >> update->day_of_week;
            break;

        case 8:
            cout << "Enter the new sessions: ";
            cin >> update->session;
            break;

        case 9:
            input_student_to_course(year, update->course_id);

            break;

        case 10:
        {
            cout << "Enter the student ID: ";
            cin >> temp_remove;

            int x = 0;
            int stop = 1;
            while (x < update->size_student - 1 && stop != 0)
            {
                if (update->enrolled_student[x].studentID == temp_remove)
                {
                    stop = 0;
                    for (int n = x; n < update->size_student - 1; n++)
                    {
                        update->enrolled_student[n] = update->enrolled_student[n + 1];
                    }
                    break;
                }
                x++;
            }
            if (x == update->size_student - 1 && update->enrolled_student[x].studentID == temp_remove)
            {
                update->enrolled_student[x].studentID = "0";
                stop = 0;
            }
            if (stop == 0)
            {
                update->size_student--;
                cout << "Erase student completed" << endl;
            }
            if (stop == 1)
                cout << "Student ID does not exist" << endl;

            break;
        }
        case 11:
            for (int i = 0; i < year->data_semester[year->current_semester].course_capacity - 1; i++)
            {
                if (year->data_semester[year->current_semester].data_course[i].course_id == update->course_id)
                {
                    delete[] year->data_semester[year->current_semester].data_course[i].enrolled_student;
                    for (int j = i; j < year->data_semester[year->current_semester].course_capacity - 1; j++)
                    {
                        year->data_semester[year->current_semester].data_course[j] = year->data_semester[year->current_semester].data_course[j + 1];
                    }
                }
            }
            delete[] year->data_semester[year->current_semester].data_course[year->data_semester[year->current_semester].course_capacity - 1].enrolled_student;
            year->data_semester[year->current_semester].data_course[year->data_semester[year->current_semester].course_capacity - 1].course_id = "0";
            year->data_semester[year->current_semester].course_num--;
            cout << "Course has been deleted";
            flag = 0;
            break;

        case 0:
            cout << "Ending updating course information.";
            break;

        default:
            cout << "Invalid input! Please enter an option.";
            break;
        }
        system("pause");
        cout << endl;
    }
}