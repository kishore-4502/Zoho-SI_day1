#include<bits/stdc++.h>
using namespace std;

int divide(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw "Invalid division ";
	}
	return numerator / denominator;
}

char getChar(string str, int index)
{
	if (index >= str.length())
	{
		throw "Index is invalid";
	}
	return str[index];
}

int getNum(int arr[], int length,int index)
{
	if (index >= length)
	{
		throw "Array Index is invalid";
	}
	return arr[index];
}

int stringToInt(string str){
	for (int i = 0; i < str.length(); ++i)
	{
		if(!(str[i]>=48 && str[i]<=57)){
			throw "Format mismatch";
		}
	}
	int ans=0;
	stringstream converter(str);
	converter >> ans;
 	
	return ans;
}

class MyException{
public:
	int parameter;
	MyException(int parameter){
		this->parameter=parameter;
	}
};

char* allocateMemory(long size){
	char* ptr = new (std::nothrow) char[size];
	if(!ptr){
		throw "Memory is compromised!";
	}
	return ptr;
}

int main()
{

	// Division by zero
	try
	{
		int ans = divide(3, 0);
		cout << ans << endl;
	}
	catch (char const *Exp)
	{
		cout << Exp << endl;
		cout<< "Exception Handling Accomplished\n"<<endl;
	}


	// String parsed to a numeric variable
	try{
		int ans=stringToInt("12a");
	}catch(const char* Exp){
		cout<<Exp<<endl;
		cout<< "Exception Handling Accomplished\n"<<endl;
	}

	// Accessing an invalid index in string
	string str = "kishore";
	try
	{
		char ans = getChar(str, 8);
		cout << ans << endl;
	}
	catch (char const *Exp)
	{
		cout << Exp << endl;
		cout<< "Exception Handling Accomplished\n"<<endl;
	}

	// Accessing an invalid index in array
	int arr[] = {1,2,3,4,5};
	int len=sizeof(arr)/sizeof(int);
	try
	{
		int ans = getNum(arr, len,5);
		cout << ans << endl;
	}
	catch (char const *Exp)
	{
		cout << Exp << endl;
		cout<< "Exception Handling Accomplished\n"<<endl;
	}
	// User Defined Exception
	try{
		throw MyException(4);
	}catch(MyException e1){
		cout<<"MyException"<<"["<<e1.parameter<<"]"<<endl;
		cout<< "Exception Handling Accomplished\n"<<endl;
	}

	// Exceptions other than mentioned above
	try{
		throw "Null pointer exception";
	}
	catch(...){
		cout<<"Exception encountered"<<endl;
		cout<< "Exception Handling Accomplished\n"<<endl;
	}

	// Creation of heap memory variable
	try{
		char* ptr=allocateMemory(0x7fffffff);
	}catch(const char* Exp){
		cout<<Exp<<endl;
		cout<< "Exception Handling Accomplished\n"<<endl;
	}
	
	return 0;
}