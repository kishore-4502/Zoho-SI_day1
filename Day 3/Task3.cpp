#include<iostream>
#include<memory>
using namespace std;

int main(){
	// Unique Pointers
	{
		unique_ptr<int> unPtr=make_unique<int>(25);
		cout<<*unPtr<<endl;
	}

	// Shared Pointers
	{
		shared_ptr<int> shPtr1=make_shared<int>(12);
		shared_ptr<int> shPtr2=shPtr1;
		cout<<*shPtr1<<endl;
		cout<<*shPtr2<<endl;
		cout<<"No of owners : "<<shPtr1.use_count()<<endl;
	}

	// Weak Pointers
	weak_ptr<int> wp;
	{
		shared_ptr<int> shPtr1=make_shared<int>(2);
		wp=shPtr1;
		cout<<"No of owners : "<<shPtr1.use_count()<<endl;
	}
	

	return 0;
}