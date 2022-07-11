#include<bits/stdc++.h>
using namespace std;

int main(){
	
	// If an exception occurs within outer try block.
	try{
		throw "Exception caught in Outer try block";
		try{
			throw "Exception caught in Inner try block";
		}catch(const char* exp){
			cout<<exp<<endl;
		}
	}catch(const char* exp){
		cout<<exp<<endl;
	}

	cout<<"\n";
	// If an exception occurs inside inner try block.
	try{
		try{
			throw "Exception caught in Inner try block";
		}catch(const char* exp){
			cout<<exp<<endl;
		}
	}catch(const char* exp){
		cout<<exp<<endl;
	}

	cout<<"\n";
	// In case of no such notable exceptions.
	try{
		cout<<"Inside 1nd try block"<<endl;
		try{
			cout<<"Inside 2nd try block"<<endl;
		}catch(...){
			cout<<"Inside catch block"<<endl;
		}
	}catch(const char* exp){
		cout<<exp<<endl;
	}

	cout<<"\n";
	// To re-throw an exception already catched.
	try{
		cout<<"Inside 1st try block"<<endl;
		throw "Exception thrown";
		
	}catch(const char* exp){
		try{
			cout<<"Inside 2nd try block"<<endl;
			throw "Exception2 thrown";
		}
		catch(const char* exp)
		{
			cout<<exp<<endl;
		}
	}

	return 0;
}