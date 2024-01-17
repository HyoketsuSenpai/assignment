#include <iostream>
#include <string>
#include <fstream>

using namespace std;

double calcGrade(string s);

struct rec
{
	int currentYr = 2024;
	int numOfCourses = 14;

	struct
	{
		string name;
		string id;
		string dept;
		int admissionYr = 2020;
		double cgpa[8] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
		double ggpa[8] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 };
	} stInfo;
	
	struct course
	{
		string title;
		string code;
		double creditHr = 0;
		string grade;
		int yr = 1;
		int sem = 1;
	};

	void iStu()
	{
		cout << "Enter student's name: ";
		getline(cin >> ws, stInfo.name);
		cout << "Enter student's id: ";
		cin >> stInfo.id;
		cout << "Enter student's department: ";
		getline(cin >> ws, stInfo.dept);
		cout << "Eter student's year of admission: ";
		cin >> stInfo.admissionYr;

		numOfCourses = 7 * 2 * cNum();
	}

	int cNum()
	{
		if (currentYr - stInfo.admissionYr > 4)
			return 4;
		if (currentYr - stInfo.admissionYr <= 0)
			return 0;
		return currentYr - stInfo.admissionYr;
	}

	course courses[56];

	void iCourse()
	{
		int yr = 1;
		int sem = 1;
		int coursesPerSem = 7;
		double cgpa = 0.0;
		double ggpa = 0.0;
		int j = 0;

		for (int i = 0; i < numOfCourses; i++)
		{
			if (i % coursesPerSem == 0 && i != 0)
			{
				sem = (sem == 1) ? 2 : 1;

				if (sem == 1)
					yr++;
			}

			if ((i % coursesPerSem == 0 && i != 0) || i == numOfCourses - 1)
			{
				stInfo.cgpa[j] = cgpa / (7 * (j + 1));
				stInfo.ggpa[j] = ggpa / 7;
				ggpa = 0;
				j++;
			}

			courses[i].yr = yr;
			courses[i].sem = sem;

			cout << "Current year: " << yr << endl << "Current semester: " << sem << endl;

			cout << "Enter course title: ";
			getline(cin >> ws, courses[i].title);
			cout << "Enter course code: ";
			getline(cin >> ws, courses[i].code);
			cout << "Enter course credit hour: ";
			cin >> courses[i].creditHr;
			cout << "Enter course grade: ";
			cin >> courses[i].grade;

			
			cgpa += courses[i].creditHr * calcGrade(courses[i].grade);
			ggpa += courses[i].creditHr * calcGrade(courses[i].grade);
		}
		
	}

	void wfile()
	{
		fstream f("student.txt",ios::app);
		int coursesPerSem = 7;
		int j = 0;

		if (f.is_open())
		{
			f << '*' << endl;

			f << stInfo.name << endl;
			f << stInfo.id << endl;
			f << stInfo.dept << endl;
			f << stInfo.admissionYr << endl;

			for (int i = 0; i < numOfCourses; i++)
			{
				f << "Year:" << courses[i].yr << endl << "Sem:" << courses[i].sem << endl;
				f << courses[i].title << ' ' << courses[i].code << ' ' << courses[i].creditHr << ' ' << courses[i].grade << endl;
				
				if ((i + 1) % coursesPerSem == 0 && i != 0)
				{
					f << "CGPA: " << stInfo.cgpa[j] << ' ' << "GPA: " << stInfo.ggpa[j] << endl;
					j++;
				}
			}

		}

		f.close();
	}


	void iall()
	{
		iStu();
		iCourse();
		wfile();
	}

	void grade(string name, int year = 0)
	{
		ifstream f("student.txt");

		if(f.is_open())
		{
			f.seekg(0);
			string s;

			while (getline(f >> ws, s))
			{

				if (s == "*")
				{
					getline(f >> ws, s);
					if (s == name)
					{
						if(year == 0)
						{
							while (s != "*" && f.tellg() != -1)
							{
								cout << s << endl;
								getline(f >> ws, s);
							}
						}
						else
						{
							for(int i = 0;i < 3;i++)
							{
								cout << s << endl;
								getline(f >> ws, s);
							}
							cout << s << endl;
							stInfo.admissionYr = stoi(s);

							year = cNum();

							while (s != "*" && f.tellg() != -1)
							{
								if(s == ("Year:" + to_string(year)))
								{		
									
									for(int i = 0;i < 22;i++)
										getline(f >> ws, s);

									for(int i = 0;i < 22;i++)
									{
										cout << s << endl;
										getline(f >> ws, s);
									}
								}

								getline(f >> ws, s);
								
							}
						}
						return;
					}
				}
				
				


			}
			cout << "Student not found";
			f.close();
		}

	}

};


int main()
{
	rec record;
	int choice;
	string stuName;
	while(true)
	{

		cout << "1.Add new student record \n2.Student grade report\n3.Student semester grade report\nEnter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			record.iall();
			break;
		case 2:
			cout << "Enter student name:";
			getline(cin >> ws, stuName);
			record.grade(stuName);
			break;
		case 3:
			cout << "Enter student name:";
			getline(cin >> ws, stuName);
			record.grade(stuName,1);
			break;
		}
	}


}

double calcGrade(string s)
{
	string gr[] = { "A+","A","A-","B+","B","B-","C+","C","C-","D","Fx","F" };
	double gd[] = { 4.0,4.0,3.75,3.5,3.0,2.75,2.5,2.0,1.75,1.0,0.0,0.0};

	for (int i = 0; i < 15; i++)
	{
		if (s == gr[i])
			return gd[i];
	}

	return 0.0;
}