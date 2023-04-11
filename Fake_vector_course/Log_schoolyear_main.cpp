#include "Log_header.h"
#include "Schoolyear_header.h"

int main()
{
    node *accHead = NULL;
    node *accTail = NULL;
    int usertype, access = 0; // 0 - staff, 1 - student
    int op1, op2;
    string u_name, pass;
    user *newacc = new user;

    string year_name, classname, courseid, filename;
    System systems;
    init_system(systems);           // kiểm soát full hệ thống
    SchoolYear *school_year = NULL; // kiểm soát schoolyear hiện tại
    read_file_acc(accHead);
    do
    {
        switch (access)
        {
        case 0: // biến dùng để check đã login hay chưa
        {
            do
            {
                cout << setw(120) << setfill('-') << endl;
                cout << setw(50) << setfill(' ') << "WELCOME TO LOGIN PAGE" << endl;
                cout << "1. Register" << endl;
                cout << "2. Log in" << endl;
                cout << "0. Exit" << endl;
                cout << "OPTION: ";
                cin >> op1;
                switch (op1)
                {
                case 1: // Register
                {
                    newacc = register_acc();
                    if (check_available_acc(accHead, newacc) == 0)
                    {
                        getnode(accHead, newacc);
                    }
                    else
                    {
                        cout << "This account has already exist!" << endl;
                    }
                    newacc = NULL;
                    access = 0;
                    break;
                }
                case 2: // Log in
                {
                    login(accHead, u_name, pass, usertype, access);
                    // op1 = 0;
                    break;
                }
                case 0:
                {
                    break;
                }
                }
            } while (op1 != 0 && access == 0);
            if (op1 == 0)
            {
                break;
            }
        }

        case 1: // chỉ khi đã login
        {
            system("CLEAR");
            do
            {
                cout << setw(120) << setfill('-') << endl;
                cout << setw(50) << setfill(' ') << "HOME PAGE" << endl;
                cout << "3. View profile" << endl;
                cout << "4. Change password" << endl;
                cout << "5. Log out" << endl;
                cout << endl;
                cout << "6. Create school year" << endl;
                cout << "7. Add class to school year" << endl;
                cout << "8. Add new student to class" << endl;
                cout << "9. Import students from csv file to class" << endl;
                cout << endl;
                cout << "10. Create semester" << endl;
                cout << "11. Add course to current semester" << endl;
                cout << "12. Add a student to the course" << endl;
                cout << "13. Upload CSV file of enrolled students to course" << endl;
                cout << "14. Update course information " << endl;
                cout << endl;
                cout << "15. View list of class" << endl;
                cout << "16. View student in a class" << endl;
                cout << endl;
                cout << "17. View list of courses" << endl;
                cout << "18. View list of students in a course" << endl;
                cout << "19. Export list of students in a course to CSV file" << endl;
                cout << endl;
                cout << "20. Import scoreboard of a course" << endl;
                cout << "21. View scoreboard of a course" << endl;
                cout << "22. Update student's result" << endl;
                cout << endl;
                cout << "23. View the scoreboard of a class, including final marks of all courses in the semester, GPA in this semester, and the overall GPA" << endl;
                cout << "24. View student own scoreboard (after the scoreboard has been published)" << endl;
                /*cout << "17. View course in semester" << endl;
                cout << "18. View student in course" << endl;*/
                // cout << "15. Remove a student from the course" << endl;
                // cout << "16. Delete course " << endl;
                cout << "0. Exit" << endl;
                cout << "OPTION: ";
                cin >> op2;
                switch (op2)
                {
                case 3:
                {
                    display_profile(accHead, u_name, pass);
                    break;
                }
                case 4:
                {
                    system("CLEAR");
                    change_password(accHead, u_name, pass);
                    break;
                }
                case 5:
                {
                    system("CLEAR");
                    access = 0;
                    cout << "Log out successfully" << endl;
                    break;
                }
                case 6:
                {
                    system("CLEAR");
                    cout << "School year: ";
                    cin >> year_name;
                    create_school_year(systems, year_name);
                    school_year = &(systems.data_schoolyear[systems.year_num - 1]);
                    break;
                }
                case 7:
                {
                    system("CLEAR");
                    if (school_year == nullptr)
                    {
                        cout << "No school year available" << endl;
                        break;
                    }
                    cout << "Class name (add class to schoolyear): ";
                    cin >> classname;
                    add_class_to_schoolyear(systems, school_year, classname);
                    break;
                }
                case 8:
                {
                    system("CLEAR");
                    if (!school_year)
                    {
                        cout << "No school year available" << endl;
                        break;
                    }
                    if (check_class_is_empty(school_year))
                    {
                        cout << "No class available" << endl;
                        break;
                    }
                    cout << "Class needs to add student: ";
                    cin >> classname;
                    input_student_to_class(school_year, classname);
                    break;
                }
                case 9:
                {
                    system("CLEAR");
                    if (!school_year)
                    {
                        cout << "No school year available" << endl;
                        break;
                    }
                    if (check_class_is_empty(school_year))
                    {
                        cout << "No class available" << endl;
                        break;
                    }
                    
                    string filename;
                    cout << "Name of import file: ";
                    cin >> filename;
                    cout << "Class needs to add student: ";
                    cin >> classname;
                    import_students_csv_to_class(school_year, classname, filename);
                    break;
                }
                case 10:
                {
                    system("CLEAR");
                    Semester sem;
                    if (!school_year)
                    {
                        cout << "No school year available" << endl;
                        break;
                    }
                    cout << "Semester: ";
                    cin >> sem.semester_id; // 1,2 or 3 or 4 or 5...
                    cout << "Start day: ";
                    cin >> sem.start_day;
                    cout << "End day: ";
                    cin >> sem.end_day;
                    create_semester(school_year, sem);
                    break;
                }
                case 11:
                {
                    system("CLEAR");
                    Course temp;
                    cout << "Course id: ";
                    cin >> temp.course_id;
                    cout << "Course name: ";
                    cin >> temp.course_name;
                    cout << "Class name: ";
                    cin >> temp.class_name;
                    cout << "Teacher name: ";
                    cin.ignore();
                    getline(cin, temp.teacher_name);
                    temp.max_students = 50;
                    cout << "Credit: ";
                    cin >> temp.credits;
                    cout << "Day of week: ";
                    cin >> temp.day_of_week;
                    cout << "Session: ";
                    cin >> temp.session;
                    Semester *sem = nullptr;
                    sem = &(school_year->data_semester[school_year->current_semester]);
                    add_course_to_semester(sem, temp);
                    break;
                }
                case 12:
                {
                    system("CLEAR");
                    if (check_course_is_empty(school_year))
                    {
                        cout << "No course available" << endl;
                        break;
                    }
                    int check = 0;
                    cout << "CourseID of course needs to add student: ";
                    cin >> courseid;
                    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
                    {
                        if (courseid == school_year->data_semester[school_year->current_semester].data_course[i].course_id)
                        {
                            input_student_to_course(school_year, courseid);
                            check = 1;
                            break;
                        }
                    }
                    if (check == 0)
                    {
                        cout << "CourseID does not exist" << endl;
                    }
                    break;
                }
                case 13:
                {
                    system("CLEAR");
                    if (check_course_is_empty(school_year))
                    {
                        cout << "No course available" << endl;
                        break;
                    }
                    cout << "CourseID of course needs to add student: ";
                    cin >> courseid;
                    cout << "File name: ";
                    cin >> filename;
                    int check = 0;
                    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
                    {
                        if (courseid == school_year->data_semester[school_year->current_semester].data_course[i].course_id)
                        {
                            import_students_csv_to_course(school_year, filename, courseid);
                            check = 1;
                            break;
                        }
                    }
                    if (check == 0)
                    {
                        cout << "CourseID does not exist" << endl;
                    }
                    break;
                }
                case 14:
                {
                    system("CLEAR");
                    if (check_course_is_empty(school_year))
                    {
                        cout << "No course available" << endl;
                        break;
                    }
                    int check = 0;
                    cout << "CourseID of course needs to be updated: ";
                    cin >> courseid;
                    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
                    {
                        if (courseid == school_year->data_semester[school_year->current_semester].data_course[i].course_id)
                        {
                            Course *course = &(school_year->data_semester[school_year->current_semester].data_course[i]);
                            update_course(course, school_year);
                            check = 1;
                            break;
                        }
                    }
                    if (check == 0)
                    {
                        cout << "CourseID does not exist" << endl;
                    }
                    break;
                }
                case 15:
                {
                    system("CLEAR");
                    // view_class_in_schoolyear(school_year); // just for check
                    view_class_in_schoolyear(systems);
                    break;
                }
                case 16:
                {
                    system("CLEAR");
                    // view_student_in_class(school_year); //// just for check
                    view_student_in_class(systems);
                    break;
                }
                case 17:
                {
                    system("CLEAR");
                    view_list_of_course(school_year);
                    break;
                }
                case 18:
                {
                    system("CLEAR");
                    if (!school_year)
                    {
                        cout << "No school year available" << endl;
                        break;
                    }
                    if (!school_year->data_semester)
                    {
                        cout << "No semester available" << endl;
                        break;
                    }
                    if (check_course_is_empty(school_year))
                    {
                        cout << "No course available" << endl;
                        break;
                    }
                    cout << "CourseID of course needs to be viewed: ";
                    cin >> courseid;
                    int check = 0;
                    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
                    {
                        if (courseid == school_year->data_semester[school_year->current_semester].data_course[i].course_id)
                        {
                            int cur_course = i;
                            view_student_in_course(school_year, cur_course);
                            check = 1;
                            break;
                        }
                    }
                    if (check == 0)
                    {
                        cout << "CourseID does not exist" << endl;
                    }
                    break;
                }
                case 19:
                {
                    system("CLEAR");
                    if (check_course_is_empty(school_year))
                    {
                        cout << "No course available" << endl;
                        break;
                    }
                    int check = 0;
                    cout << "Enter CourseID: ";
                    cin >> courseid;
                    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
                    {
                        if (courseid == school_year->data_semester[school_year->current_semester].data_course[i].course_id)
                        {
                            export_student_from_course_to_file(school_year, courseid);
                            check = 1;
                            break;
                        }
                    }
                    if (check == 0)
                    {
                        cout << "CourseID does not exist" << endl;
                    }
                    break;
                }
                case 20:
                {
                    system("CLEAR");
                    if (check_course_is_empty(school_year))
                    {
                        cout << "No course available" << endl;
                        break;
                    }
                    import_scoreboard_of_a_course(school_year);
                    break;
                }
                case 21:
                {
                    system("CLEAR");
                    if (check_course_is_empty(school_year))
                    {
                        cout << "No course available" << endl;
                        break;
                    }
                    view_scoreboard_of_a_course(school_year);
                    break;
                }
                case 22:
                {
                    system("CLEAR");
                    if (check_course_is_empty(school_year))
                    {
                        cout << "No course available" << endl;
                        break;
                    }
                    update_student_result(school_year);
                    break;
                }
                case 23:
                {
                    system("CLEAR");
                    string classname;
                    cout << "Enter class name: ";
                    cin >> classname;
                    Classes *cur_class = nullptr; // lớp cần xem điểm
                    int cur_semester;             // học kỳ cần xem điểm
                    for (int i = 0; i < systems.year_num; i++)
                    {
                        for (int j = 0; j < systems.data_schoolyear[i].class_num; j++)
                        {
                            if (classname == systems.data_schoolyear[i].data_classes[j].class_name)
                            {
                                cur_class = &(systems.data_schoolyear[i].data_classes[j]);
                                // Vòng lặp này để tính gpa của mọi năm của lớp để tránh bị segmentation fault
                                for (int z = 0; z < systems.year_num; z++)
                                {
                                    for (int k = 0; k < systems.data_schoolyear[z].semester_num; k++)
                                    {
                                        SchoolYear *temp = &(systems.data_schoolyear[i]);
                                        cal_GPA_current(temp, cur_class, k);
                                    }
                                }
                                cur_semester = systems.data_schoolyear[i].current_semester;
                                cal_GPA_all_student_in_class(systems, cur_class);
                                show_scores_class(school_year, cur_class, cur_semester);
                                break;
                            }
                        }
                    }
                    break;
                }
                case 24:
                {
                    system("CLEAR");
                    string stuid, classname;
                    Classes *cur_class1 = nullptr; // lớp cần xem điểm
                    int cur_semester;              // học kỳ cần xem điểm
                    cout << "Enter Student ID: ";
                    cin >> stuid;
                    cout << "Enter class name: ";
                    cin >> classname;
                    for (int i = 0; i < systems.year_num; i++)
                    {
                        for (int j = 0; j < systems.data_schoolyear[i].class_num; j++)
                        {
                            if (classname == systems.data_schoolyear[i].data_classes[j].class_name)
                            {
                                cur_class1 = &(systems.data_schoolyear[i].data_classes[j]);
                                // Vòng lặp này để tính gpa của mọi năm của lớp để tránh bị segmentation fault
                                for (int z = 0; z < systems.year_num; z++)
                                {
                                    for (int k = 0; k < systems.data_schoolyear[z].semester_num; k++)
                                    {
                                        SchoolYear *temp = &(systems.data_schoolyear[i]);
                                        cal_GPA_current(temp, cur_class1, k);
                                    }
                                }
                                cur_semester = systems.data_schoolyear[i].current_semester;
                                cal_GPA_all_student_in_class(systems, cur_class1);
                                show_score_student(school_year, cur_semester, cur_class1, stuid);
                                break;
                            }
                        }
                    }
                    break;
                }
                    /*case 25:
                    {
                        view_couse_in_semester(school_year); // just for check
                        break;
                    }
                    case 26:
                    {
                        // view_student_in_course(school_year, cur_course); // also just for check
                        break;
                    }*/
                }
            } while (op2 != 0 && access != 0);
            if (access == 0)
            {
                cout << "You have loged out. Please come back to the login page.";
                op2 = 0;
            }
        }
        }
    } while (op1 != 0 && op2 != 0);

    if (school_year != NULL)
    {
        for (int i = 0; i < school_year->class_num; i++)
        {
            delete[] school_year->data_classes[i].data_student;
        }
        delete[] school_year->data_classes;
    }
    if (school_year != nullptr)
    {
        for (int i = 0; i < school_year->semester_capacity; i++)
        {
            for (int j = 0; j < school_year->data_semester[i].course_capacity; j++)
            {
                delete[] school_year->data_semester[i].data_course[j].enrolled_student;
            }
            delete[] school_year->data_semester[i].data_course;
        }
        delete[] school_year->data_semester;
    }
    // delete school_year;
    delete[] systems.data_schoolyear;
    print_in_file(accHead);
    deleteall(accHead);
    return 0;
}
