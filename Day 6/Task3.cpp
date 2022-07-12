#include <bits/stdc++.h>
using namespace std;
string toLower(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

class AgeNotWithinRangeException : public exception
{
public:
	const char *what()
	{
		return "Age not within limit";
	}
};
class NameNotValidException
{
public:
	const char *what()
	{
		return "Name not valid";
	}
};
class InvalidCourseException
{
public:
	const char *what()
	{
		return "Course not valid";
	}
};
class studentLimitExceededException
{
public:
	const char *what()
	{
		return "Student limit exceeded";
	}
};

string availableCourses[7] = {"CSE", "IT", "ECE", "EEE", "Mechatronics", "Mechanical", "Civil"};
static bool objectCreated = false;

class Student
{
public:
	int rollNumber;
	string name;
	int age;
	string course;

	Student(int rollNumber, string name, int age, string course)
	{
		
		if (objectCreated)
		{
			studentLimitExceededException a;
			throw a;
		}
		objectCreated = true;
		this->rollNumber = rollNumber;
		bool isValid = true;
		for (char ch : name)
		{
			if (!(ch >= 65 && ch <= 90 || ch >= 97 && ch <= 122))
			{
				isValid = false;
			}
		}
		if (!isValid)
		{
			NameNotValidException a;
			throw a;
		}
		this->name = name;
		if (!(age >= 15 && age <= 21))
		{
			AgeNotWithinRangeException a;
			throw a;
		}
		this->age = age;
		bool isCourseValid = false;
		for (int i = 0; i < 7; i++)
		{
			if (toLower(availableCourses[i]) == toLower(course))
			{
				isCourseValid = true;
			}
		}
		if (!isCourseValid)
		{
			InvalidCourseException a;
			throw a;
		}
		this->course = course;

	}
};

int main()
{
	try
	{
		Student s1(12, "kishore", 20, "mechatronics");
	}
	catch (AgeNotWithinRangeException &e)
	{
		cout << e.what() << endl;
	}
	catch (NameNotValidException &e)
	{
		cout << e.what() << endl;
	}
	catch (studentLimitExceededException &e)
	{
		cout << e.what() << endl;
	}
	catch (InvalidCourseException &e)
	{
		cout << e.what() << endl;
	}catch(...){
		cout<<"Exception occured"<<endl;
	}

	return 0;
}