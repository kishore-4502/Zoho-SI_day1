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

// Circular Dependency
// One pointer shares other
struct struct2;

struct struct1
{
	shared_ptr<struct2> val;
	~struct1() { cout << "struct1 Destroyed." << endl; }
};
struct struct2
{
	weak_ptr<struct1> val;
	~struct2() { cout << "struct2 Destroyed." << endl; }
};

int main()
{

	Student s1(1);
	Student s2(2);
	Student s3(3);
	cout << "No of Students : " << mect.use_count() - 1 << endl;

	// Weak pointers
	auto temp1 = make_shared<struct1>();
	auto temp2 = make_shared<struct2>();

	temp1->val = temp2;
	temp2->val = temp1;

	return 0;
}