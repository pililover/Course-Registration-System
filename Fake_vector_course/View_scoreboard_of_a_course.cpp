#include "Schoolyear_header.h"

void view_scoreboard_of_a_course(SchoolYear *school_year)
{
    int check = 0;
    string courseid;
    Course *course = nullptr;
    cout << "Enter CourseID: ";
    cin >> courseid;
    cout << setw(40) << setfill(' ') << "SCOREBOARD OF COURSE" << endl;
    cout << '\t' << "No"
         << "\t" << setw(15) << "StudentID" << setw(20) << "Firstname" << setw(20) << "Lastname" << setw(10) << "Score" << endl;
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
        cout << '\t' << '\t' << i + 1 << setw(4) << ". "
             << setw(20) << course->enrolled_student[i].studentID << " "
             << setw(20) << course->enrolled_student[i].firstname << " "
             << setw(20) << course->enrolled_student[i].lastname << " "
             << setw(10) << course->enrolled_student[i].score << endl;
    }
}