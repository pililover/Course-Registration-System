#include "Schoolyear_header.h"

void view_class_in_schoolyear(System system)
{
	if (system.year_num == 0)
	{
		cout << "No school year available" << endl;
		return;
	}

	string yearname;
	SchoolYear *school_year = NULL;
	do
	{
		cout << "School year: ";
		cin >> yearname;
		int check = 0;
		for (int i = 0; i < system.year_num; i++)
		{
			if (system.data_schoolyear[i].year_name == yearname)
			{
				check = 1;
				school_year = &(system.data_schoolyear[i]);
				break;
			}
		}
		if (check == 1)
			break;
		if (check == 0)
		{
			cout << "Not found. Please choose a different school year: " << endl;
		}
	} while (!school_year);
	if (check_class_is_empty(school_year))
	{
		cout << "No class available" << endl;
		return;
	}
	cout << "\t\t\t\t"
		 << "LIST OF CLASS IN SCHOOL YEAR " << endl;

	for (int i = 0; i < school_year->class_num; i++)
		cout << '\t' << setw(3) << i + 1 << ". " << school_year->data_classes[i].class_name << endl;
}
/*Check school year first
	if(!school_year) {
		cout << "No school year available" << endl;
		break;
	}
*/
void view_student_in_class(System system)
{
	if (system.year_num == 0)
	{
		cout << "No school year available" << endl;
		return;
	}

	string yearname;
	SchoolYear *school_year = NULL;
	cout << "School year: ";
	cin >> yearname;
	do
	{
		for (int i = 0; i < system.year_num; i++)
		{
			if (system.data_schoolyear[i].year_name == yearname)
				school_year = &(system.data_schoolyear[i]);
		}
		if (!school_year)
		{
			cout << "Not found. Please choose a different school year: ";
			cin >> yearname;
		}
	} while (!school_year);
	if (check_class_is_empty(school_year))
	{
		cout << "No class available" << endl;
		return;
	}

	string classname;
	int index;
	cout << "Class name: ";
	cin >> classname;
	while (!check_classname_in_a_year(*(school_year), classname, index))
	{
		cout << "Not found. Please choose a different name: ";
		cin >> classname;
	}

	if (school_year->data_classes[index].student_num == 0)
	{
		cout << "No student in class" << endl;
		return;
	}

	cout << setw(4) << left << "No" << setw(12) << left << "ID"
		 << setw(15) << left << "First name" << setw(15) << left << "Last name"
		 << setw(9) << left << "Gender" << setw(14) << left << "Birthday"
		 << "Social ID" << endl;
	for (int i = 0; i < school_year->data_classes[index].student_num; i++)
	{
		cout << setw(4) << left << i + 1;
		cout << setw(12) << left << school_year->data_classes[index].data_student[i].studentID;
		cout << setw(15) << left << school_year->data_classes[index].data_student[i].firstname;
		cout << setw(15) << left << school_year->data_classes[index].data_student[i].lastname;
		cout << setw(9) << left << school_year->data_classes[index].data_student[i].gender;
		cout << setw(14) << left << school_year->data_classes[index].data_student[i].birthday;
		cout << school_year->data_classes[index].data_student[i].socialID << endl;
	}
}