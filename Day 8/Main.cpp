#include <bits/stdc++.h>
using namespace std;

class MobileConnection
{
public:
    string phoneNumber;
    int billAmount;
    string refNumber;
    MobileConnection(string phoneNumber, int billAmount)
    {
        this->phoneNumber = phoneNumber;
        this->billAmount = billAmount;
        this->refNumber = phoneNumber;
    }
    void payBills()
    {
        this->billAmount = 0;
        cout << phoneNumber << " : Bill Paid" << endl;
    }
};

class LandlineConnection
{
public:
    int lanNumber;
    int STDcode;
    int billAmount;
    string refNumber;
    LandlineConnection(int STDcode, int lanNumber, int billAmount)
    {
        this->lanNumber = lanNumber;
        this->STDcode = STDcode;
        this->billAmount = billAmount;
        this->refNumber = to_string(STDcode) + to_string(lanNumber);
        cout << refNumber << endl;
    }
    void payBills()
    {
        billAmount = 0;
        cout << lanNumber << " , " << STDcode
             << " : Bill Paid" << endl;
    }
};

template <class T>
class Manager
{
public:
    vector<T> Users;
    void add(T &x)
    {
        Users.push_back(x);
    }
    void payBill(string num)
    {
        for (int i = 0; i < Users.size(); i++)
        {
            if (Users[i].refNumber == num)
            {
                Users[i].billAmount = 0;
                cout << Users[i].refNumber << "...You have paid the bill..Bill remaining = " << Users[i].billAmount << endl;
                break;
            }
        }
    }
    void updateBill(string num, int amount)
    {
        for (int i = 0; i < Users.size(); i++)
        {
            if (Users[i].refNumber == num)
            {
                Users[i].billAmount += amount;
                cout << Users[i].refNumber << "...Bill remaining = " << Users[i].billAmount << endl;
                break;
            }
        }
    }
};

int main()
{
    Manager<MobileConnection> manager1;
    Manager<LandlineConnection> manager2;

    while (1)
    {
        cout << "1.Add a new mobile connection." << endl;
        cout << "2.Add a new landline connection." << endl;
        cout << "3.Pay bill using the connection number." << endl;
        cout << "4.Update bill amount using the connection number" << endl;
        cout << "5.Exit" << endl;

        int input;
        cin >> input;
        if (input == 1)
        {
            string phoneNum;
            int billAmt;
            cout << "Please enter Phone number" << endl;
            cin >> phoneNum;
            cout << "Please enter Bill amount" << endl;
            cin >> billAmt;
            MobileConnection user1(phoneNum, billAmt);
            manager1.add(user1);
        }
        else if (input == 2)
        {
            int lanNum, SSDNum, billAmt;
            cout << "Please enter LAN number" << endl;
            cin >> lanNum;
            cout << "Please enter SSD number" << endl;
            cin >> SSDNum;
            cout << "Please enter Bill amount" << endl;
            cin >> billAmt;
            LandlineConnection user1(lanNum, SSDNum, billAmt);
            manager2.add(user1);
        }
        else if (input == 3)
        {
            int flag;
            cout << "Please enter 1 for mobile, 2 for landline" << endl;
            cin >> flag;
            string connectionNum;
            cout << "Please enter the connection number" << endl;
            cin >> connectionNum;
            if (flag == 1)
            {
                manager1.payBill(connectionNum);
            }
            if (flag == 2)
            {
                manager2.payBill(connectionNum);
            }
        }
        else if (input == 4)
        {
            int flag;
            cout << "Please enter 1 for mobile, 2 for landline" << endl;
            cin >> flag;
            string connectionNum;
            int amt;
            cout << "Please enter the connection number and amount" << endl;
            cin >> connectionNum;
            cin >> amt;
            if (flag == 1)
            {
                manager1.updateBill(connectionNum, amt);
            }
            if (flag == 2)
            {
                manager2.updateBill(connectionNum, amt);
            }
        }
        else if (input == 5)
        {
            break;
        }
        else
        {
            cout << "Invalid selection" << endl;
        }
    }

    // LandlineConnection user1(1234, 5678, 200);
    // LandlineConnection user2(4321, 8765, 200);
    // LandlineConnection user3(2341, 1234, 200);
    // manager2.add(user1);
    // manager2.add(user2);
    // manager2.add(user3);
    // manager2.updateBill("12345678", 100);
    // manager2.payBill("12345678");
}
