#include "Schoolyear_header.h"

void import_scoreboard_of_a_course(SchoolYear *school_year)
{
    int check = 0;
    string courseid;
    cout << "Enter courseID to import: ";
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
    string filename;
    cout << "Enter file want to import score: ";
    cin >> filename;
    ifstream fin(filename);
    while (!fin)
    {
        cout << "File want to import not available, enter again: ";
        cin >> filename;
        fin.open(filename);
    }
    int stt = 0;
    float score_st = 0;
    string stuid;
    string stufirstname;
    string stulastname;
    string stu_score;
    while (!fin.eof())
    {
        getline(fin, stuid, ',');
        getline(fin, stufirstname, ',');
        getline(fin, stulastname, ',');
        getline(fin, stu_score, '\n');
        score_st = stof(stu_score);
        course->enrolled_student[stt].score = score_st;
        stt++;
    }
    fin.close();
}