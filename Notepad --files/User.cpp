#include<iostream>
#include<regex>
#include "main.pb.h"
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
    string encrypt(string password) {
        string newPassword;
        int len = password.length();
        for (int i = 0; i < len; i++) {
            newPassword += password[i] + len;
        }
        return newPassword;
    }
};