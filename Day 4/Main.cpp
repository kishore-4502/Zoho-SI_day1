#include <iostream>
#include <cmath>
using namespace std;

class Rectangle
{
public:
	int *width = new int();
	int *height = new int();
	int *left = new int[2];
	int *top = new int[2];
	int *area = new int[1];

	int calculateArea(int w, int h)
	{
		return w * h;
	}

	// Default Constructor
	Rectangle()
	{
		*width = 0;
		*height = 0;
		left[0] = 0;
		left[1] = 0;
		top[0] = 0;
		top[1] = 0;
		*area = calculateArea(*width, *height);
	}
	// Parameterized Constructors
	Rectangle(int w, int h)
	{
		*width = w;
		*height = h;
		left[0] = 0;
		left[1] = 0;
		top[0] = 0;
		top[1] = 0;
		*area = calculateArea(*width, *height);
	}
	Rectangle(int w, int h, int l[], int t[])
	{
		*width = w;
		*height = h;
		left[0] = l[0];
		left[1] = l[1];
		top[0] = t[0];
		top[1] = t[1];
		*area = calculateArea(*width, *height);
	}
	Rectangle(float w, float h, float l[], float t[])
	{
		*width = round(w);
		*height = round(h);
		left[0] = round(l[0]);
		left[1] = round(l[1]);
		top[0] = round(t[0]);
		top[1] = round(t[1]);
		*area = calculateArea(*width, *height);
	}
	// Copy Constructor
	Rectangle(Rectangle &x)
	{
		*width = *(x.width);
		*height = *(x.height);
		left[0] = x.left[0];
		left[1] = x.left[1];
		top[0] = x.top[0];
		top[1] = x.top[1];
		*area = calculateArea(*width, *height);
	}
	// Destructor --to free out all the dynamic memory used
	~Rectangle()
	{
		delete width;
		delete height;
		delete[] left;
		delete[] top;
		delete[] area;
		width = NULL;
		height = NULL;
		left = NULL;
		top = NULL;
		area = NULL;
	}

	void printDetails()
	{
		cout << "Height : " << (*height) << endl;
		cout << "Width : " << (*width) << endl;
		cout << "Left : {" << left[0] << "," << left[1] << "}" << endl;
		cout << "Top : {" << top[0] << "," << top[1] << "}" << endl;
		cout << "Area : " << (*area) << endl;
		cout << "\n";
	}
};

int main()
{
	Rectangle r1(10, 2, new int[2]{3, 4}, new int[2]{5, 14});
	r1.printDetails();

	Rectangle r2(5.3, 4.9, new float[2]{8.0, 1.5}, new float[2]{12.9, 6.8});
	r2.printDetails();

	Rectangle r3(r1);
	r3.printDetails();

	return 0;
}
