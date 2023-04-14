#include "Schoolyear_header.h"

void import_scoreboard_of_a_course(SchoolYear *school_year)
{
    int check = 0;
    string courseid;
    cout << "Enter courseID to import: ";
    cin >> courseid;
    float percentage_final;
    float percentage_midterm;
    float percentage_other;
    cout << "Percentage of other (x%): ";
    cin >> percentage_other;
    cout << "Percentage of midterm (x%): ";
    cin >> percentage_midterm;
    cout << "Percentage of final (x%): ";
    cin >> percentage_final;
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
    float total = 0;
    float final = 0;
    float midterm = 0;
    float other = 0;
    string stunum;
    string stuid;
    string stufirstname;
    string stulastname;
    string stu_score;
    while (!fin.eof())
    {
        getline(fin, stunum, ',');
        getline(fin, stuid, ',');
        getline(fin, stufirstname, ',');
        getline(fin, stulastname, ',');
        
        getline(fin, stu_score, ',');
        if (!isdigit(stu_score[0])) {
            cout<<"File doesn't have at least a other score. Import unsuccessful. ";
            fin.close();
            return;
        }
        other = stof(stu_score);
        course->enrolled_student[stt].other = other;
        
        getline(fin, stu_score, ',');
        if (!isdigit(stu_score[0])) {
            cout<<"File doesn't have at least a midterm score. Import unsuccessful. ";
            fin.close();
            return;
        }
        midterm = stof(stu_score);
        course->enrolled_student[stt].midterm = midterm;
        
        getline(fin, stu_score, '\n');
        if (!isdigit(stu_score[0])) {
            cout<<"File doesn't have at least a final score. Import unsuccessful. ";
            fin.close();
            return;
        }
        final = stof(stu_score);
        course->enrolled_student[stt].final = final;
        
        total = final * percentage_final / 100 + midterm * percentage_midterm / 100 + other * percentage_other / 100;
        course->enrolled_student[stt].score = total;
        stt++;
    }
    cout<<"Import successful. ";
    fin.close();
}