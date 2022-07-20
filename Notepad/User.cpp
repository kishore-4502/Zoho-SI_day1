#include<iostream>
#include<regex>
#include<conio.h>
#include "user.pb.h"
#include "version.pb.h"
#include "project.pb.h"
#include <stdexcept>
#include <string>
#include <windows.h>
using namespace std;


class UserPortal {
public:
    void addUser(User* user, string username, string email,int age, string location,string userID, string password)
    {
        user->set_username(username);
        user->set_email(email);
        user->set_age(age);
        user->set_location(location);
        user->set_userid(userID);
        user->set_password(password);
    }
    bool isEmailValid(string email) {
        const regex pattern(
            "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return regex_match(email, pattern);
    }
    string getpassword(const string& prompt = "Enter password> ")
    {
        string result;

        // Set the console mode to no-echo, not-line-buffered input
        DWORD mode, count;
        HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
        if (!GetConsoleMode(ih, &mode))
            throw runtime_error(
                "getpassword: You must be connected to a console to use this program.\n");
        SetConsoleMode(ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

        // Get the password string
        WriteConsoleA(oh, prompt.c_str(), prompt.length(), &count, NULL);
        char c;
        while (ReadConsoleA(ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
        {
            if (c == '\b')
            {
                if (result.length())
                {
                    WriteConsoleA(oh, "\b \b", 3, &count, NULL);
                    result.erase(result.end() - 1);
                }
            }
            else
            {
                WriteConsoleA(oh, "*", 1, &count, NULL);
                result.push_back(c);
            }
        }

        // Restore the console mode
        SetConsoleMode(ih, mode);

        return result;
    }
};