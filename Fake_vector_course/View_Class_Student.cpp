#include "Schoolyear_header.h"

void view_class_in_schoolyear(SchoolYear *school_year)
{
	if (!school_year)
	{
		cout << "No school year available" << endl;
		return;
	}
	cout << "School year: " << school_year->year_name << endl;
	if (check_class_is_empty(school_year))
	{
		cout << "No class available" << endl;
		return;
	}
	for (int i = 0; i < school_year->class_num; i++)
		cout << school_year->data_classes[i].class_name << endl;
}

/*Check school year first
	if(!school_year) {
		cout << "No school year available" << endl;
		break;
	}
*/
void view_student_in_class(SchoolYear *school_year)
{
	if (!school_year)
	{
		cout << "No school year available" << endl;
		return;
	}
	if (check_class_is_empty(school_year))
	{
		cout << "No class available" << endl;
		return;
	}

	string classname;
	int index = -1;
	cout << "Class name: ";
	cin >> classname;
	do
	{
		for (int i = 0; i < school_year->class_num; i++)
		{
			if (school_year->data_classes[i].class_name == classname)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
		{
			cout << "Not found. Please choose a different name: ";
			cin >> classname;
		}
	} while (index == -1);

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
		cout << setw(4) << left << school_year->data_classes[index].data_student[i].student_num;
		cout << setw(12) << left << school_year->data_classes[index].data_student[i].studentID;
		cout << setw(15) << left << school_year->data_classes[index].data_student[i].firstname;
		cout << setw(15) << left << school_year->data_classes[index].data_student[i].lastname;
		cout << setw(9) << left << school_year->data_classes[index].data_student[i].gender;
		cout << setw(14) << left << school_year->data_classes[index].data_student[i].birthday;
		cout << school_year->data_classes[index].data_student[i].socialID << endl;
	}
}
