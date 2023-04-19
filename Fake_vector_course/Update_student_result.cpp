#include "Schoolyear_header.h"

void update_student_result(SchoolYear *school_year)
{
    string courseid, stuid;
    int check = 0;
    cout << "Enter Student ID: ";
    cin >> stuid;
    cout << "Enter CourseID: ";
    cin >> courseid;
    Course *course = nullptr;
    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
    {
        if (courseid == school_year->data_semester[school_year->current_semester].data_course[i].course_id)
        {
            course = &(school_year->data_semester[school_year->current_semester].data_course[i]);
            check = 1;
            break;
        }
    }
    if (check == 0)
    {
        cout << "CourseID does not exist" << endl;
        return;
    }
    int option;
    cout << "1. Update other scores" << endl;
    cout << "2. Update midterm scores" << endl;
    cout << "3. Update final scores" << endl;
    cout << "Enter option: ";
    do
    {
        cin >> option;
        if (option < 1 || option > 3)
            cout << "Invalid option, enter again: ";
    } while (option < 1 || option > 3);
    float new_scores = 0;
    cout << "Enter new scores: ";
    cin >> new_scores;
    float percentage_final = 100;
    float percentage_midterm = 100;
    float percentage_other = 100;
    cout << "Percentage of other (x% > 0): ";
    cin >> percentage_other;
    cout << "Percentage of midterm (x% > 0): ";
    cin >> percentage_midterm;
    cout << "Percentage of final (x% > 0): ";
    cin >> percentage_final;
    for (int i = 0; i < course->size_student; i++)
    {
        if (stuid == course->enrolled_student[i].studentID)
        {
            if (option == 1)
                course->enrolled_student[i].other = new_scores;
            else if (option == 2)
                course->enrolled_student[i].midterm = new_scores;
            else
                course->enrolled_student[i].final = new_scores;
            float total = 0;
            total = course->enrolled_student[i].other * percentage_other / 100 + course->enrolled_student[i].midterm * percentage_midterm / 100 + course->enrolled_student[i].final * percentage_final / 100;
            course->enrolled_student[i].score = total;
            cout << "Update successfully" << endl;
            return;
        }
    }
    cout << "Student want to update score doen't in this course.";
}