#include "Log_header.h"

node *createnode(user *newacc)
{
    node *temp = new node;
    temp->data = newacc;
    temp->next = nullptr;
    return temp;
}

node *addnode(node *p, user *newacc)
{
    node *temp = nullptr;
    temp = createnode(newacc);
    p->next = temp;
    return temp;
}

void getnode(node *&accHead, user *newacc)
{
    node *p = accHead;
    if (p == nullptr)
    {
        p = createnode(newacc);
        accHead = p;
    }
    else
    {
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p = addnode(p, newacc);
    }
}

int check_input_usertype()
{
    int x;
    do
    {
        cin >> x;
    } while (x != 0 && x != 1);
    return x;
}

user *register_acc()
{
    user *acc = new user;
    cout << "Full name: ";
    cin.ignore();
    getline(cin, acc->fullname);
    cout << "Type of user (staff - 0, student - 1): ";
    acc->type_of_user = check_input_usertype();
    cout << "Username (Do not have space character): " << endl;
    cin >> acc->username;
    cout << "Password (Do not have space character): " << endl;
    cin >> acc->password;
    if (acc->type_of_user == 1)
    {
        cout << "Student ID (Do not have space character): " << endl;
        cin >> acc->ID;
    }
    else
    {
        acc->ID = "No_ID";
    }
    return acc;
}

void read_file_acc(node *&accHead)
{
    string row, u_type;
    fstream ip("account.csv", ios::in);

    while (getline(ip, row))
    {
        istringstream inp(row);
        user *already_acc = new user;

        getline(inp, already_acc->fullname, ',');
        getline(inp, u_type, ',');
        already_acc->type_of_user = stoi(u_type);
        getline(inp, already_acc->username, ',');
        getline(inp, already_acc->password, ',');
        getline(inp, already_acc->ID, '\n');

        node *temp = createnode(already_acc);

        if (accHead == nullptr)
        {
            accHead = temp;
        }
        else
        {
            node *p = accHead;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = temp;
        }
    }
    ip.close();
}

int check_available_acc(node *accHead, user *newacc)
{
    node *p = accHead;
    while (p != nullptr)
    {
        if (p->data->username == newacc->username && p->data->password == newacc->password)
        {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

int check_login(node *accHead, string &u_name, string &pass, int &usertype, string &ID)
{
    node *p = accHead;
    while (p != nullptr)
    {
        if (p->data->username == u_name && p->data->password == pass)
        {
            usertype = p->data->type_of_user;
            ID = p->data->ID;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

void login(node *accHead, string &u_name, string &pass, int &usertype, int &access, string &ID)
{
    cout << "Username: ";
    cin >> u_name;
    cout << "Password: ";
    cin >> pass;
    if (check_login(accHead, u_name, pass, usertype, ID))
    {
        cout << "Log in succefully!" << endl;
        access = 1;
    }
    else
    {
        cout << "Fail! Try again!" << endl;
    }
}
void print_in_file(node *accHead)
{
    if (accHead == nullptr)
        return;
    fstream ip("new_update_acc.csv", ios::out);
    while (accHead != nullptr)
    {
        ip << accHead->data->fullname << ',';
        ip << accHead->data->type_of_user << ',';
        ip << accHead->data->username << ',';
        ip << accHead->data->password << ',';
        ip << accHead->data->ID << endl;
        accHead = accHead->next;
    }
    ip.close();
    remove("account.csv");
    rename("new_update_acc.csv", "account.csv");
}

void deleteall(node *&accHead)
{
    if (accHead == nullptr)
        return;
    while (accHead != nullptr)
    {
        node *p = accHead;
        accHead = accHead->next;
        delete p;
    }
}

void display_profile(node *accHead, string u_name, string pass) // đợi lúc có đầy đủ lớp, niên khoá thì add vào
{
    cout << "PROFILE: " << endl;
    while (accHead != nullptr)
    {
        if (accHead->data->username == u_name && accHead->data->password == pass)
        {
            cout << "Full name: " << accHead->data->fullname << endl;
            if (accHead->data->type_of_user == 0)
                cout << "STAFF" << endl;
            else
                cout << "STUDENT" << endl;
            cout << "Username: " << accHead->data->username << endl;
            cout << "Password: " << accHead->data->password << endl;
            cout << "ID: " << accHead->data->ID << endl;
        }
        accHead = accHead->next;
    }
}

void change_password(node *accHead, string u_name, string &pass)
{
    node *p = accHead;
    string new_pass, cur_pass;
    do
    {
        cout << "Current password: ";
        cin >> cur_pass;
        if (cur_pass != pass)
            cout << "Wrong current password!" << endl;
    } while (cur_pass != pass);
    cout << "New pass: ";
    cin >> new_pass;
    while (p != nullptr)
    {
        if (p->data->username == u_name && p->data->password == pass)
        {
            p->data->password = new_pass;
            pass = p->data->password;
            cout << "Change password successfully!" << endl;
            return;
        }
        p = p->next;
    }
}

void set_color(int code)
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, code);
}
/*Code
0 = Black       8 = Gray
1 = Blue        9 = Light Blue
2 = Green      10 = Light Green
3 = Aqua       11 = Light Aqua
4 = Red        12 = Light Red
5 = Purple     13 = Light Purple
6 = Yellow     14 = Light Yellow
7 = White      15 = Bright White
*/
