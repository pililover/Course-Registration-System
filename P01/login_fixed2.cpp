#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <sstream>

using namespace std;

struct user
{
    string username;
    string password;
    int type_of_user;
    string fullname;
};

struct node
{
    user *data;
    node *next;
};

node *head = NULL;

node *createnode(user *newacc)
{
    node *temp = new node;
    temp->data = newacc;
    temp->next = NULL;
    return temp;
}

node *addnode(node *p, user *newacc)
{
    node *temp = NULL;
    temp = createnode(newacc);
    p->next = temp;
    return temp;
}

void getnode(node *&head, user *newacc)
{
    node *p = head;
    if (p == NULL)
    {
        p = createnode(newacc);
        head = p;
    }
    else
    {
        while (p->next != NULL)
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
    return acc;
}

void read_file_acc(node *&head)
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

        node *temp = createnode(already_acc);

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            node *p = head;
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = temp;
        }
    }
    ip.close();
}

int check_available_acc(node *head, user *newacc)
{
    node *p = head;
    while (p != NULL)
    {
        if (p->data->username == newacc->username && p->data->password == newacc->password)
        {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

int check_login(node *head, string &u_name, string &pass, int &usertype)
{
    node *p = head;
    while (p != NULL)
    {
        if (p->data->username == u_name && p->data->password == pass)
        {
            usertype = p->data->type_of_user;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

void login(node *head, string &u_name, string &pass, int &usertype, int &access)
{
    cout << "Username: ";
    cin >> u_name;
    cout << "Password: ";
    cin >> pass;
    if (check_login(head, u_name, pass, usertype))
    {
        access = 1;
        cout << "Log in succefully!" << endl;
    }
    else
    {
        cout << "Fail! Try again!" << endl;
    }
}
void print_in_file(node *head)
{
    fstream ip("new_update_acc.csv", ios::out);
    while (head != NULL)
    {
        ip << head->data->fullname << ',';
        /*if (head->data->type_of_user == 0)
            ip << "STAFF" << endl;
        else
            ip << "STUDENT" << endl;*/
        ip << head->data->type_of_user << ',';
        ip << head->data->username << ',';
        ip << head->data->password << endl;
        head = head->next;
    }
    remove("account.csv");
    rename("new_update_acc.csv", "account.csv");
    ip.close();
}

void deleteall(node *&head)
{
    while (head != NULL)
    {
        node *p = head;
        head = head->next;
        delete p;
    }
}

void display_profile(node *head, string u_name, string pass) // đợi lúc có đầy đủ lớp, niên khoá thì add vào
{
    cout << "PROFILE: " << endl;
    while (head != NULL)
    {
        if (head->data->username == u_name && head->data->password == pass)
        {
            cout << "Full name: " << head->data->fullname << endl;
            if (head->data->type_of_user == 0)
                cout << "STAFF" << endl;
            else
                cout << "STUDENT" << endl;
            cout << "Username: " << head->data->username << endl;
            cout << "Password: " << head->data->password << endl;
        }
        head = head->next;
    }
}

void change_password(node *head, string u_name, string &pass)
{
    node *p = head;
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
    while (p != NULL)
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
int main()
{
    int op, usertype, access = 0;
    string u_name, pass;
    user *newacc = new user;
    read_file_acc(head);
    do
    {
        cout << setw(120) << setfill('-') << endl;
        cout << setw(50) << setfill(' ') << "WELCOME TO LOGIN PAGE" << endl;
        cout << "1. Register" << endl;
        cout << "2. Log in" << endl;
        cout << "3. View profile" << endl;
        cout << "4. Change password" << endl;
        cout << "5. Log out" << endl;
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
            if (check_available_acc(head, newacc) == 0)
            {
                getnode(head, newacc);
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
            login(head, u_name, pass, usertype, access);
            break;
        }
        case 3:
        {
            if (access == 1)
                display_profile(head, u_name, pass);
            else
                cout << "Please, login first" << endl;
            break;
        }
        case 4:
        {
            if (access == 1)
                change_password(head, u_name, pass);
            else
                cout << "Please, login first" << endl;
            break;
        }
        case 5:
        {
            if (access == 1)
            {
                access == 0;
                cout << "Log out successfully" << endl;
            }
            else
            {
                cout << "Loged out already" << endl;
            }
        }
        }
    } while (op != 0);
    print_in_file(head);
    deleteall(head);
    return 0;
}