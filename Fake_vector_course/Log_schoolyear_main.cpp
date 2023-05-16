#include "Log_header.h"
#include "Schoolyear_header.h"

int main()
{
    node *accHead = NULL;
    node *accTail = NULL;
    int usertype, access = 0; // 0 - staff, 1 - student
    int op1, op2;
    string u_name, pass, ID;
    user *newacc = new user;

    string year_name, classname, courseid, filename;
    System systems;
    init_system(systems);           // control system
    SchoolYear *school_year = NULL; // control current schoolyear
    read_file_acc(accHead);
    do
    {
        switch (access)
        {
        case 0:
        {
            do
            {
                set_color(14);
                cout << setw(120) << setfill('-') << endl;
                cout << setfill(' ') << setw(50) << right << (char)1 << " WELCOME TO LOGIN PAGE " << (char)1 << endl;
                cout << "1. Register" << endl;
                cout << "2. Log in" << endl;
                cout << "0. Exit" << endl;
                set_color(12);
                cout << "OPTION: ";
                cin >> op1;
                set_color(15);
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
                    login(accHead, u_name, pass, usertype, access, ID);
                    break;
                }
                case 0:
                {
                    break;
                }
                default:
                {
                    cout << "Invalid option!" << endl;
                    break;
                }
                }
            } while (op1 != 0 && access == 0);
            if (op1 == 0)
            {
                break;
            }
        }

        case 1:
        {
            system("CLEAR");
            do
            {
                set_color(14);
                cout << setw(120) << setfill('-') << endl;
                cout << setfill(' ') << setw(50) << right << (char)21 << " HOME PAGE " << (char)21 << endl;
                set_color(3);
                cout << "3. View profile" << endl;
                cout << "4. Change password" << endl;
                cout << "5. Log out" << endl;
                cout << setfill((char)4) << setw(30) << (char)4 << endl;
                cout << endl;
                if (usertype == 0)
                {
                    set_color(7);
                    cout << "6. Create school year" << endl;
                    cout << "7. Add class to current school year" << endl;
                    cout << "8. Add new student to class" << endl;
                    cout << "9. Import students from csv file to class in current school year" << endl;
                    cout << setfill((char)4) << setw(30) << (char)4 << endl;
                    cout << endl;
                    set_color(9);
                    cout << "10. Create semester" << endl;
                    cout << "11. Add course to current semester" << endl;
                    cout << "12. Add a student to the course" << endl;
                    cout << "13. Upload CSV file of enrolled students to course" << endl;
                    cout << "14. Update course information " << endl;
                    cout << setfill((char)4) << setw(30) << (char)4 << endl;
                    cout << endl;
                    set_color(15);
                    cout << "15. View list of class" << endl;
                    cout << "16. View student in a class" << endl;
                    cout << setfill((char)4) << setw(30) << (char)4 << endl;
                    cout << endl;
                    set_color(2);
                    cout << "17. View list of courses in current semester" << endl;
                    cout << "18. View list of courses in a school year" << endl;
                    cout << "19. View list of students in a course" << endl;
                    cout << "20. Export list of students in a course to CSV file" << endl;
                    cout << setfill((char)4) << setw(30) << (char)4 << endl;
                    cout << endl;
                    set_color(10);
                    cout << "21. Import scoreboard of a course" << endl;
                    cout << "22. View scoreboard of a course" << endl;
                    cout << "23. Update student's result" << endl;
                    cout << setfill((char)4) << setw(30) << (char)4 << endl;
                    cout << endl;
                    set_color(11);
                    cout << "24. View the scoreboard of a class, including final marks of all courses in the semester, GPA in this semester, and the overall GPA" << endl;
                    cout << "0. Exit" << endl;
                    cout << setfill((char)4) << setw(30) << (char)4 << setfill(' ') << endl;
                    set_color(12);
                    cout << "OPTION: ";
                    cin >> op2;
                    set_color(15);
                    switch (op2)
                    {
                    case 3:
                    {
                        system("CLEAR");
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
                        create_semester(systems, sem);
                        break;
                    }
                    case 11:
                    {
                        system("CLEAR");
                        if (!school_year)
                        {
                            cout << "No school year available" << endl;
                            break;
                        }
                        Course temp;
                        cout << "Course id: ";
                        cin >> temp.course_id;
                        cout << "Course name: ";
                        cin.ignore();
                        getline(cin,temp.course_name);
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
                        if (!school_year)
                        {
                            cout << "No school year available" << endl;
                            break;
                        }
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
                        if (!school_year)
                        {
                            cout << "No school year available" << endl;
                            break;
                        }
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
                        if (!school_year)
                        {
                            cout << "No school year available" << endl;
                            break;
                        }
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
                        view_class_in_schoolyear(systems);
                        break;
                    }
                    case 16:
                    {
                        system("CLEAR");
                        view_student_in_class(systems);
                        break;
                    }
                    case 17:
                    {
                        system("CLEAR");
                        if (!school_year)
                        {
                            cout << "No school year available" << endl;
                            break;
                        }
                        view_list_of_course(school_year);
                        break;
                    }
                    case 18:
                    {
                        system("CLEAR");
                        string year_name;
                        cout << "School year: ";
                        cin >> year_name;
                        view_course_in_schoolyear(systems, year_name);
                        break;
                    }
                    case 19:
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
                    case 20:
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
                    case 21:
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
                        import_scoreboard_of_a_course(school_year);
                        break;
                    }
                    case 22:
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
                        view_scoreboard_of_a_course(school_year);
                        break;
                    }
                    case 23:
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
                        update_student_result(school_year);
                        break;
                    }
                    case 24:
                    {
                        system("CLEAR");
                        string classname;
                        cout << "Enter class name: ";
                        cin >> classname;
                        Classes *cur_class = nullptr; // lớp cần xem điểm
                        int cur_semester;             // học kỳ cần xem điểm
                        if (systems.year_num >= 1)
                        {
                            for (int i = 0; i < systems.year_num; i++)
                            {
                                for (int j = 0; j < systems.data_schoolyear[i].class_num; j++)
                                {
                                    if (classname == systems.data_schoolyear[i].data_classes[j].class_name)
                                    {
                                        cur_class = &(systems.data_schoolyear[i].data_classes[j]);
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
                        }
                        else
                        {
                            find_score_class(classname);
                        }

                        break;
                    }
                    case 0:
                    {
                        break;
                    }
                    default:
                    {
                        cout << "Invalid option" << endl;
                        break;
                    }
                    }
                }
                else
                {
                    set_color(11);
                    cout << "6. View student own registered courses" << endl;
                    cout << "7. View student own scoreboard (after the scoreboard has been published)" << endl;
                    cout << "0. Exit" << endl;
                    cout << setfill((char)4) << setw(30) << (char)4 << setfill(' ') << endl;
                    set_color(12);
                    cout << "OPTION: ";
                    cin >> op2;
                    set_color(15);
                    switch (op2)
                    {
                    case 3:
                    {
                        system("CLEAR");
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
                        personal_registered_course(school_year, ID);
                        break;
                    }
                    case 7:
                    {
                        system("CLEAR");
                        string classname;
                        cout << "Enter class name: ";
                        cin >> classname;
                        find_score_student(classname, ID);
                        break;
                    }
                    case 0:
                    {
                        break;
                    }
                    default:
                    {
                        cout << "Invalid option!" << endl;
                        break;
                    }
                    }
                }
            } while (op2 != 0 && access != 0);
            if (access == 0)
            {
                cout << "You have loged out. Please come back to the login page." << endl;
            }
        }
        }
    } while (op1 != 0 && op2 != 0);

    for (int k = 0; k < systems.year_capacity; k++)
    {
        for (int i = 0; i < systems.data_schoolyear[k].class_capacity; i++)
        {
            delete[] systems.data_schoolyear[k].data_classes[i].data_student;
        }
        delete[] systems.data_schoolyear[k].data_classes;
    }

    for (int k = 0; k < systems.year_num; k++)
    {
        for (int i = 0; i < systems.data_schoolyear[k].semester_capacity; i++)
        {
            for (int j = 0; j < systems.data_schoolyear[k].data_semester[i].course_capacity; j++)
            {
                delete[] systems.data_schoolyear[k].data_semester[i].data_course[j].enrolled_student;
            }
            delete[] systems.data_schoolyear[k].data_semester[i].data_course;
        }
        delete[] systems.data_schoolyear->data_semester;
    }
    delete[] systems.data_schoolyear;
    print_in_file(accHead);
    deleteall(accHead);
    return 0;
}
