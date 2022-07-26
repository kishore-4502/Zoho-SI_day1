#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Bank
{
public:
    string name;
    string establishedDate;
    bool bankType;
    string branchName;
    float interestRate;
    Bank(string name, string establishedDate, bool bankType, string branchName, float interestRate)
    {
        this->name = name;
        this->establishedDate = establishedDate;
        this->bankType = bankType;
        this->branchName = branchName;
        this->interestRate = interestRate;
    }
    string getName()
    {
        return name;
    }
    string getEstablishedDate()
    {
        return establishedDate;
    }
    float getInterestRate()
    {
        return interestRate;
    }
    void details()
    {
        cout << "Name : " << name << endl;
        cout << "Established date : " << establishedDate << endl;
        bankType ? cout << "Bank Type : "
                        << "Public" << endl
                 : cout << "Bank Type : "
                        << "Private" << endl;

        cout << "Branch Name : " << branchName << endl;
        cout << "Interest Rate : " << interestRate << "%" << endl;
    }
};
class Loan
{
public:
    vector<string> availableLoans;
    unordered_map<string, vector<string>> documents;
    Loan(vector<string> availableLoans)
    {
        this->availableLoans = availableLoans;

        documents["goldLoan"] = {"Aadhar card", "Bank Passbook", "PAN Card", "Voter id"};
        documents["landLoan"] = {
            "Aadhar card",
            "Bank Passbook",
            "PAN Card", "Address proof"};
        documents["personalLoan"] = {"Aadhar card", "Bank Passbook", "PAN Card", "salary slip"};
    }

    void getAvailableLoans()
    {
        for (int i = 0; i < availableLoans.size(); i++)
        {
            cout << (availableLoans[i]) << endl;
        }
    }

    vector<string> documentRequired(string a)
    {
        return documents[a];
    }
    void printRequiredDocuments()
    {
        for (int i = 0; i < availableLoans.size(); i++)
        {

            cout << availableLoans[i] + " : ";
            vector<string> temp = documents[availableLoans[i]];
            for (int j = 0; j < temp.size(); j++)
            {
                cout << temp[j] + ",";
            }
            cout << endl;
        }
    }
    void details()
    {
        cout << "The Available loans and their required documents are ," << endl;
        printRequiredDocuments();
    }
};

class HDFC : public Bank, public Loan
{
public:
    HDFC(string name, string establishedDate, bool bankType, string branchName, float interestRate, vector<string> availableLoans)
        : Bank(name, establishedDate, bankType, branchName, interestRate), Loan(availableLoans)
    {
    }
    void details()
    {
        cout << "Name : " << name << endl;
        cout << "Established date : " << establishedDate << endl;
        bankType ? cout << "Bank Type : "
                        << "Public" << endl
                 : cout << "Bank Type : "
                        << "Private" << endl;

        cout << "Branch Name : " << branchName << endl;
        cout << "Interest Rate : " << interestRate << "%" << endl;
        cout << "The Required documents for different loans are ," << endl;
        printRequiredDocuments();
    }
};

class SBI : public Bank, public Loan
{
public:
    SBI(string name, string establishedDate, bool bankType, string branchName, float interestRate, vector<string> availableLoans)
        : Bank(name, establishedDate, bankType, branchName, interestRate), Loan(availableLoans)
    {
    }
    void details()
    {
        cout << "Name : " << name << endl;
        cout << "Established date : " << establishedDate << endl;
        bankType ? cout << "Bank Type : "
                        << "Public" << endl
                 : cout << "Bank Type : "
                        << "Private" << endl;

        cout << "Branch Name : " << branchName << endl;
        cout << "Interest Rate : " << interestRate << "%" << endl;
        cout << "The Required documents for different loans are ," << endl;
        printRequiredDocuments();
    }
};
class ICICI : public Bank, public Loan
{
public:
    ICICI(string name, string establishedDate, bool bankType, string branchName, float interestRate, vector<string> availableLoans)
        : Bank(name, establishedDate, bankType, branchName, interestRate), Loan(availableLoans)
    {
    }
    void details()
    {
        cout << "Name : " << name << endl;
        cout << "Established date : " << establishedDate << endl;
        bankType ? cout << "Bank Type : "
                        << "Public" << endl
                 : cout << "Bank Type : "
                        << "Private" << endl;

        cout << "Branch Name : " << branchName << endl;
        cout << "Interest Rate : " << interestRate << "%" << endl;
        cout << "The Required documents for different loans are ," << endl;
        printRequiredDocuments();
    }
};

class Broker
{
public:
    // To compare interest rates of diff banks
    void compare(Bank b1, Bank b2)
    {
        if (b1.interestRate < b2.interestRate)
        {
            cout << "The Bank with minimum interest rate is " << b1.name << endl;
        }

        else if (b1.interestRate > b2.interestRate)
        {
            cout << "The Bank with minimum interest rate is " << b2.name << endl;
        }
        else
        {
            cout << "Both banks have the same Interest rate" << endl;
        }
    }
    void compare(Bank b1, Bank b2, Bank b3)
    {
        if (b1.interestRate < b2.interestRate && b1.interestRate < b3.interestRate)
        {
            cout << "The Bank with minimum interest rate is " << b1.name << endl;
        }

        else if (b2.interestRate < b1.interestRate && b2.interestRate < b3.interestRate)
        {
            cout << "The Bank with minimum interest rate is " << b2.name << endl;
        }
        else
        {
            cout << "The Bank with minimum interest rate is " << b3.name << endl;
        }
    }
    void compare(vector<Bank> list)
    {
        float min_rate = INT_MAX / 1.0;
        string min_bank = "";
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i].interestRate < min_rate)
            {
                min_rate = list[i].interestRate;
                min_bank = list[i].name;
            }
        }
        cout << "The Bank with minimum interest rate is " << min_bank << endl;
    }
    void printDetails(Bank b1)
    {
        cout << "Name : " << b1.name << endl;
        cout << "Established date : " << b1.establishedDate << endl;
        b1.bankType ? cout << "Bank Type : "
                           << "Public" << endl
                    : cout << "Bank Type : "
                           << "Private" << endl;

        cout << "Branch Name : " << b1.branchName << endl;
        cout << "Interest Rate : " << b1.interestRate << "%" << endl;
    }
    void printDetails(Bank list[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            cout << "Name : " << list[i].name << endl;
            cout << "Established date : " << list[i].establishedDate << endl;
            list[i].bankType ? cout << "Bank Type : "
                                    << "Public" << endl
                             : cout << "Bank Type : "
                                    << "Private" << endl;

            cout << "Branch Name : " << list[i].branchName << endl;
            cout << "Interest Rate : " << list[i].interestRate << "%\n"
                 << endl;
        }
    }
};
int main()
{
    HDFC hdfc1 = HDFC("HDFC", "04.05.2002", true, "Namakkal", 13.7, {"goldLoan", "landLoan", "personalLoan"});
    SBI sbi1 = SBI("SBI", "05.05.2002", true, "Madurai", 12.4, {"goldLoan", "landLoan", "personalLoan"});
    ICICI icici1 = ICICI("ICICI", "06.05.2002", false, "Chennai", 14.5, {"goldLoan", "landLoan"});
    Broker broker1;
    Bank arr[] = {hdfc1, sbi1, icici1};
    int size = sizeof(arr) / sizeof(Bank);
    broker1.printDetails(arr, size);
    broker1.compare(hdfc1, sbi1, icici1);

    return 0;
}