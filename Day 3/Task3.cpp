#include <iostream>
#include <memory>
using namespace std;

shared_ptr<string> mect = make_shared<string>("Mechatronics");

class Student
{
public:
	unique_ptr<int> rollNo = make_unique<int>(0);
	shared_ptr<string> department;
	Student(int rollNo)
	{
		*(this->rollNo) = rollNo;
		department = mect;
	}
	~Student()
	{
		cout << "Destroyed " << *rollNo << endl;
	}
};

int main()
{

	Student s1(1);
	Student s2(2);
	Student s3(3);
	cout << "No of Students : " << mect.use_count() - 1 << endl;

	return 0;
}