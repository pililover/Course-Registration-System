#include "header.h"

int main()
{
    node *accHead = NULL;
    node *accTail = NULL;

    student *studentHead = NULL;
    student *curStudent = NULL;

    int op, usertype, access = 0;
    string u_name, pass;
    user *newacc = new user;
    read_file_acc(accHead);
    do
    {
        cout << setw(120) << setfill('-') << endl;
        cout << setw(50) << setfill(' ') << "WELCOME TO LOGIN PAGE" << endl;
        cout << "1. Register" << endl;
        cout << "2. Log in" << endl;
        cout << "3. View profile" << endl;
        cout << "4. Change password" << endl;
        cout << "5. Log out" << endl;
        cout << "6. Import student from CSV file" << endl;
        cout << "OPTION: ";
        cin >> op;
        switch (op)
        {
        case 0:
        {
            break;
        }
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
            break;
        }
        case 2: // Log in
        {
            login(accHead, u_name, pass, usertype, access);
            break;
        }
        case 3:
        {
            if (access == 1)
                display_profile(accHead, u_name, pass);
            else
                cout << "Please, login first" << endl;
            break;
        }
        case 4:
        {
            if (access == 1)
                change_password(accHead, u_name, pass);
            else
                cout << "Please, login first" << endl;
            break;
        }
        case 5:
        {
            if (access == 1)
            {
                access = 0;
                cout << "Log out successfully" << endl;
            }
            else
            {
                cout << "Loged out already" << endl;
            }
            break;
        }
        case 6:
        {
            import_student_csv(studentHead, curStudent);
            break;
        }
        case 7:
        {
            input_student(curStudent);
            break;
        }
        case 8:
        {
            delete_student(studentHead);
            break;
        }
        case 9:
        {
            delete_class();
        }
        }
    } while (op != 0);
    print_in_file(accHead);
    deleteall(accHead);
    return 0;
}