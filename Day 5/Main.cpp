#include <iostream>

namespace namespace1
{
	// Create class inside namespace
	class class1
	{
	public:
		int data;
		class1(int x)
		{
			data = x;
		}
	};
	// Create Nested namespace with math equations
	namespace Math
	{
		int add(int a, int b)
		{
			return a + b;
		}
		int sub(int a, int b)
		{
			return a - b;
		}
		int square(int a)
		{
			return a * a;
		}
		int power(int num, int power)
		{
			int ans = 1;
			for (int i = 0; i < power; ++i)
			{
				ans = ans * num;
			}
			return ans;
		}

	}
}
namespace version
{
	namespace version1
	{
		void display()
		{
			std::cout << "version1" << std::endl;
		}
	}
	namespace version2
	{
		void display()
		{
			std::cout << "version2" << std::endl;
		}
	}
	inline namespace version3
	{
		void display()
		{
			std::cout << "version3" << std::endl;
		}
	}
}

// Import it in a separate class
class Square
{
public:
	int side;
	int area;
	int volume;

	Square(int side)
	{
		using namespace namespace1::Math;
		this->side = side;
		this->area = square(side);
		this->volume = power(side, 3);
	}
};

int main()
{
	namespace1::class1 obj1(5);
	std::cout << obj1.data << std::endl;

	Square s1(4);
	std::cout << "Area of s1 : " << s1.area << std::endl;
	std::cout << "Volume of s1 : " << s1.volume << std::endl;

	// Namespace aliases
	namespace a = namespace1::Math;
	std::cout << "3+4 = " << a::add(3, 4) << std::endl;

	// Use inline namespace calling
	std::cout << "The current version is ";
	version::display();
	return 0;
}