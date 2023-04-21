#include "Schoolyear_header.h"

void view_scoreboard_of_a_course(SchoolYear *school_year)
{
    int check = 0;
    string courseid;
    Course *course = nullptr;
    cout << "Enter CourseID: ";
    cin >> courseid;
    cout << setw(65) << setfill(' ') << "SCOREBOARD OF COURSE" << endl;
    cout << setw(8) << left << "No"
         << setw(9) << "StudentID" << setw(18) << "Firstname" << setw(20) << "Lastname" << setw(15) << "Other" << setw(15) << "Midterm" << setw(16) << "Final" << setw(10) << "Total" << endl;
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
    for (int i = 0; i < course->size_student; i++)
    {
        cout << setw(4) << setfill(' ') << setw(3) << left << i + 1 << setw(5) << left << ". "
             << setw(21) << left << course->enrolled_student[i].studentID
             << setw(21) << left << course->enrolled_student[i].firstname
             << setw(22) << left << course->enrolled_student[i].lastname
             << setw(15) << left << course->enrolled_student[i].other
             << setw(14) << left << course->enrolled_student[i].midterm
             << setw(12) << left << course->enrolled_student[i].final
             << setw(10) << left << course->enrolled_student[i].score << endl;
    }
}