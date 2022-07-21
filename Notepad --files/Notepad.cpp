#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include "user.pb.h"
#include "version.pb.h"
#include "project.pb.h"
#include "User.cpp"
#include "Project.cpp"
#include <cstdio>
#include<direct.h>
#include <ctime>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "sha256.h"
#include <conio.h>

using namespace std;

string Actions[] = {"Added","Removed","Updated"};

int main()
{
START:
    UserPortal uPortal;
    UserList list;
    Notepad projects;
    ProjectPortal pPortal;

    while (1) {
        ifstream usersFile;
        usersFile.open("userList.txt", ios::in | ios::binary);
        list.ParseFromIstream(&usersFile);
        int input;
        cout << "1.Log in" << endl;
        cout << "2.sign up" << endl;
        cout << "3.Exit" << endl;
        cin >> input;
        if (input == 1) {
            system("CLS");
            string userID;
            string password;
            int index = -1;

        USID:
            cout << "Enter your user Name" << endl;
            cin >> userID;
            for (int i = 0; i < list.users_size(); i++)
            {
                const auto& user = list.users(i);
                if (user.username() == userID) {
                    index = i;
                }
            }
            if (index == -1) {
                cout << "Invalid user Id" << endl;
                goto USID;
            }
        PASSWORD:
            
            password= uPortal.getpassword("Enter your password\n");
            if (list.users(index).password() == sha256(password)) {
                system("CLS");
                cout << "Welcome " << list.users(index).username() << endl;
            MENUPAGE:
                cout << "1.Create new file..." << endl;
                cout << "2.Go to Existing projects..." << endl;
                cout << "3.Log out..." << endl;
                ifstream projectsFile;
                projectsFile.open("projectList.txt", ios::in | ios::binary);
                projects.ParseFromIstream(&projectsFile);

                int choice1;
                cin >> choice1;
                if (choice1 == 1) {
                    ofstream projectFile;
                    int ind = -1;
                    cout << "Enter the name of your file with extension" << endl;
                    string fileName;
                    cin >> fileName;
                    for (int i = 0; i < projects.projects_size(); i++)
                    {
                        const auto& projectAvailable = projects.projects(i);
                        if (projectAvailable.name() == fileName) {
                            ind = i;
                        }
                    }
                    string id;
                    boost::uuids::uuid uuid = boost::uuids::random_generator()();
                    id = boost::uuids::to_string(uuid);
                    pPortal.addproject(projects.add_projects(), fileName,id,list.users(index).userid());
                    char* loc = &fileName[0];
                    string str = fileName + "/versions";
                    char* vLoc = &str[0];
                    int n = _mkdir(loc);
                    int m = _mkdir(vLoc);
                    string location = fileName + "/" + fileName;
                    projectFile.open(location);
                    projectFile.close();
                    system("CLS");
                    std::ofstream record1("projectList.txt", std::ios_base::out | std::ios_base::binary);
                    projects.SerializeToOstream(&record1);
                    goto MENUPAGE;
                }
                
                else if (choice1 == 2) {
                    Choice2:
                    system("CLS");
                    for (int i = 0; i < projects.projects_size(); i++)
                    {
                        if (list.users(index).userid() == projects.projects(i).userid()) {
                            cout << projects.projects(i).name() << endl;
                        }
                    }
                    cout << "\n" << endl;
                    cout << "Please select a project to open...Enter 0 to go back..." << endl;
                    string proj;
                    int projNum=-1;
                    cin >> proj;
                    if (proj == "0") {
                        system("CLS");
                        goto MENUPAGE;
                    }
                    for (int i = 0; i < projects.projects_size(); i++) {
                        if (projects.projects(i).name() == proj && list.users(index).userid()== projects.projects(i).userid()) {
                            projNum = i;
                        }
                    }
                    if (projNum == -1) {
                        goto Choice2;
                    }
                    projNum += 1;
                    string rootDir = projects.projects(projNum - 1).name() + "/";
                    string location = projects.projects(projNum - 1).name() + "/" + projects.projects(projNum - 1).name();
                    string versionsLocation = projects.projects(projNum - 1).name() + "/versions";
                    string verDir = rootDir + "versionDetails.txt";
                    string verDir2 = rootDir + "changes.txt";
                l4:
                    system("CLS");
                    Project selectedProject;
                    ifstream projectFile;
                    projectFile.open(location, ios::in | ios::binary);
                    selectedProject.ParseFromIstream(&projectFile);
                    selectedProject.set_name(projects.projects(projNum - 1).name());
                    selectedProject.set_id(projects.projects(projNum - 1).id());
                    selectedProject.set_userid(projects.projects(projNum - 1).userid());

                    Changes c1;
                    ifstream chFile;
                    chFile.open(verDir2, ios::in | ios::binary);
                    c1.ParseFromIstream(&chFile);
                l3:
                    system("CLS");
                    Version v1;
                    v1.set_projectid(selectedProject.name());
                    ifstream temp;
                    temp.open(verDir, ios::in | ios::binary);
                    v1.ParseFromIstream(&temp);

                   

                OPTIONS:
                    
                    cout << "Name : " << selectedProject.name() << endl;
                    cout << "Please select what you want to do with this file" << endl;
                    cout << "1.Display the contents of the file" << endl;
                    cout << "2.Add to the file" << endl;
                    cout << "3.Update / change a line" << endl;
                    cout << "4.Remove any line" << endl;
                    cout << "5.Revert back changes" << endl;
                    cout << "6.Go back" << endl;
                    int option2;
                    cin >> option2;
                    if (option2 == 1) {
                        system("CLS");
                        for (int i = 0; i < selectedProject.text_size(); i++) {
                            cout << selectedProject.text(i) << endl;
                        }
                        cout << "\n" << endl;
                        int x;
                        cout << "Press 0 to go back..." << endl;
                        cin >> x;
                        if (x == 0) {
                            system("cls");
                            goto l3;
                        }

                    }
                    if (option2 == 2) {
                        system("CLS");
                        string inp;
                        // cin >> inp;
                        cin.ignore();
                        getline(cin, inp);
                        selectedProject.add_text(inp);
                        v1.set_changescount(v1.changescount() + 1);
                        std::ofstream ofs(location, std::ios_base::out | std::ios_base::binary);
                        selectedProject.SerializeToOstream(&ofs);

                        if (v1.changescount() == 5) {
                            v1.set_changescount(0);
                            char currTime[10];
                            time_t my_time = time(NULL);
                            sprintf(currTime, ctime(&my_time));
                            v1.add_createdtime(currTime);
                            string path = versionsLocation + "/" + to_string(v1.versionnumber()) + ".txt";
                            std::ofstream ofs(path, std::ios_base::out | std::ios_base::binary);
                            v1.set_versionnumber(v1.versionnumber() + 1);
                            selectedProject.SerializeToOstream(&ofs);
                        }
                        //write changes in v1:
                        std::ofstream temp1(verDir, std::ios_base::out | std::ios_base::binary);
                        v1.SerializeToOstream(&temp1);
                        

                        c1.set_changescount(c1.changescount() + 1);
                        c1.add_linenum(selectedProject.text_size());
                        c1.add_action(Changes::ADD);
                        c1.add_changes(inp);
                        char currTime[10];
                        time_t my_time = time(NULL);
                        sprintf(currTime, ctime(&my_time));
                        c1.add_createdtime(currTime);
                        boost::uuids::uuid uuid = boost::uuids::random_generator()();
                        string ID = boost::uuids::to_string(uuid);
                        c1.add_id(ID);

                        std::ofstream t1(verDir2, std::ios_base::out | std::ios_base::binary);
                        c1.SerializeToOstream(&t1);
                        goto l3;
                    }
                    if (option2 == 3) {
                        system("CLS");
                        int lineNum;
                        string inp;
                        cout << "Enter the line number you want to change...-1 to go back" << endl;
                        cin >> lineNum;
                        if (lineNum == -1) {
                            system("cls");
                            goto OPTIONS;
                        }
                        if (lineNum <= 0) {
                            system("cls");
                            cout << "Invalid line Number" << endl;
                            goto OPTIONS;
                        }
                        cout << "Enter the new content for that line." << endl;
                        // cin >> inp;
                        cin.ignore();
                        getline(cin, inp);
                        string prev = selectedProject.text(lineNum - 1);
                        selectedProject.set_text(lineNum - 1, inp);
                        v1.set_changescount(v1.changescount() + 1);
                        std::ofstream ofs(location, std::ios_base::out | std::ios_base::binary);
                        selectedProject.SerializeToOstream(&ofs);

                        if (v1.changescount() == 5) {
                            v1.set_changescount(0);
                            char currTime[10];
                            time_t my_time = time(NULL);
                            sprintf(currTime, ctime(&my_time));
                            v1.add_createdtime(currTime);
                            string path = versionsLocation + "/" + to_string(v1.versionnumber()) + ".txt";
                            std::ofstream ofs(path, std::ios_base::out | std::ios_base::binary);
                            v1.set_versionnumber(v1.versionnumber() + 1);
                            selectedProject.SerializeToOstream(&ofs);
                        }
                        //write changes in v1:
                        std::ofstream temp1(verDir, std::ios_base::out | std::ios_base::binary);
                        v1.SerializeToOstream(&temp1);

                        c1.set_changescount(c1.changescount() + 1);
                        c1.add_linenum(lineNum);
                        c1.add_action(Changes::UPDATE);
                        c1.add_changes(prev);
                        char currTime[10];
                        time_t my_time = time(NULL);
                        sprintf(currTime, ctime(&my_time));
                        c1.add_createdtime(currTime);
                        boost::uuids::uuid uuid = boost::uuids::random_generator()();
                        string ID = boost::uuids::to_string(uuid);
                        c1.add_id(ID);

                        std::ofstream t(verDir2, std::ios_base::out | std::ios_base::binary);
                        c1.SerializeToOstream(&t);
                        goto l3;
                    }
                    if (option2 == 4) {
                        system("CLS");
                        Project newProj;
                        newProj.set_name(selectedProject.name());
                        newProj.set_id(selectedProject.id());
                        newProj.set_userid(selectedProject.userid());
                        int lineNum;
                        cout << "Enter the line number to be deleted....Enter -1 to go back" << endl;
                        cin >> lineNum;
                        if (lineNum == -1) {
                            system("cls");
                            goto OPTIONS;
                        }
                        if (lineNum <= 0) {
                            system("cls");
                            cout << "Invalid line Number" << endl;
                            goto OPTIONS;
                        }
                        string prev = selectedProject.text(lineNum - 1);
                        for (int i = 0; i < selectedProject.text_size(); i++) {
                            if (i == lineNum - 1) {
                                continue;
                            }
                            newProj.add_text(selectedProject.text(i));
                        }
                        v1.set_changescount(v1.changescount() + 1);
                        std::ofstream ofs(location, std::ios_base::out | std::ios_base::binary);
                        newProj.SerializeToOstream(&ofs);

                        if (v1.changescount() == 5) {
                            v1.set_changescount(0);
                            char currTime[10];
                            time_t my_time = time(NULL);
                            sprintf(currTime, ctime(&my_time));
                            v1.add_createdtime(currTime);
                            string path = versionsLocation + "/" + to_string(v1.versionnumber()) + ".txt";
                            v1.set_versionnumber(v1.versionnumber() + 1);
                            std::ofstream ofs(path, std::ios_base::out | std::ios_base::binary);
                            selectedProject.SerializeToOstream(&ofs);
                        }
                        //write changes in v1:
                        std::ofstream temp1(verDir, std::ios_base::out | std::ios_base::binary);
                        v1.SerializeToOstream(&temp1);

                        c1.set_changescount(c1.changescount() + 1);
                        c1.add_linenum(lineNum);
                        c1.add_action(Changes::REMOVE);
                        c1.add_changes(prev);
                        char currTime[10];
                        time_t my_time = time(NULL);
                        sprintf(currTime, ctime(&my_time));
                        c1.add_createdtime(currTime);
                        boost::uuids::uuid uuid = boost::uuids::random_generator()();
                        string ID = boost::uuids::to_string(uuid);
                        c1.add_id(ID);

                        std::ofstream t(verDir2, std::ios_base::out | std::ios_base::binary);
                        c1.SerializeToOstream(&t);
                        goto l4;
                    }
                    if (option2 == 5) {
                        REVERT:
                        system("CLS");
                        cout << "1.Revert using versions" << endl;
                        cout << "2.Revert using changes" << endl;
                        cout << "3.Back" << endl;
                        int option;
                        cin >> option;
                        if (option==1) {
                            cout << "Please select a version to revert to...Enter -2 to go back: " << endl;
                            for (int i = 0; i < v1.versionnumber(); i++) {
                                cout << "Version " << i << " --- " << v1.createdtime(i) << endl;
                            }
                            int opt;
                            cin >> opt;
                            if (opt == -2 ) {
                                goto REVERT;
                            }
                            if (opt == -1) {
                                system("cls");
                                goto OPTIONS;
                            }
                            string str = selectedProject.name() + "/versions/" + to_string(opt) + ".txt";
                            //Read from version file and store it in selectedProject:
                            ifstream projectFile;
                            projectFile.open(str, ios::in | ios::binary);
                            selectedProject.ParseFromIstream(&projectFile);
                            //write it back in project file:
                            std::ofstream op(location, std::ios_base::out | std::ios_base::binary);
                            selectedProject.SerializeToOstream(&op);
                        }
                        else if (option == 2) {
                            CHANGE:
                            cout << c1.action_size() << endl;
                            for (int i = 0; i < c1.changes_size(); i++) {
                                cout << "ID : " << c1.id(i).substr(0,4) << endl;
                                if (c1.action(i) == Changes::UPDATE) {
                                    cout << "Action : " << Actions[c1.action(i)] << ",  Changed : " << c1.changes(i) <<" to "<<selectedProject.text(c1.linenum(i)-1) << ",  Line Number : " << c1.linenum(i) << ",  Time created : " << c1.createdtime(i) << endl;
                                }
                                else {
                                cout << "Action : " << Actions[c1.action(i)] << ",  Changes : " << c1.changes(i) << ",  Line Number : " << c1.linenum(i) << ",  Time created : " << c1.createdtime(i) << endl;
                                }
                                cout << endl;
                            }
                            cout << "Please Enter any ID to revert to...Enter -1 to go back: " << endl;
                            string id;
                            cin >> id;
                            int indexOfChange=-1;
                            if (id == "-1") {
                                system("cls");
                                goto OPTIONS;
                            }
                            for (int i = 0; i < c1.changes_size(); i++) {
                                if (id == c1.id(i).substr(0, 4)) {
                                    indexOfChange = i;
                                }
                            }
                            if (indexOfChange == -1) {
                                cout << "Invalid ID";
                                goto CHANGE;
                            }
                            int n = c1.changes_size() - 1;
                            int j = 0;
                            cout << indexOfChange<<endl;
                            for (int i =n; i >indexOfChange ; i--) {
                                j++;
                                if (c1.action(i)==0) {
                                    selectedProject.mutable_text()->RemoveLast();
                                    std::ofstream op(location, std::ios_base::out | std::ios_base::binary);
                                    selectedProject.SerializeToOstream(&op);
                                }
                                if (c1.action(i)==1) {
                                    selectedProject.add_text(c1.changes(i));
                                    for (int a = selectedProject.text_size()-1; a > c1.linenum(i)-1; a--) {
                                        selectedProject.mutable_text()->SwapElements(a,a-1);
                                    }
                                    std::ofstream op(location, std::ios_base::out | std::ios_base::binary);
                                    selectedProject.SerializeToOstream(&op);
                                }
                                if(c1.action(i)==2) {
                                    selectedProject.set_text(c1.linenum(i)-1, c1.changes(i));
                                    std::ofstream op(location, std::ios_base::out | std::ios_base::binary);
                                    selectedProject.SerializeToOstream(&op);
                                }
                            }
                            for (int i = 0; i < j; i++) {
                                c1.mutable_action()->RemoveLast();
                                c1.mutable_changes()->RemoveLast();
                                c1.mutable_linenum()->RemoveLast();
                                c1.mutable_id()->RemoveLast();
                                c1.mutable_createdtime()->RemoveLast();
                                c1.set_changescount(c1.changescount() - 1);
                            }
                            std::ofstream t1(verDir2, std::ios_base::out | std::ios_base::binary);
                            c1.SerializeToOstream(&t1); 
                        }
                        else if (option == 3) {
                            goto OPTIONS;
                        }
                        else {
                            cout << "\nInvalid input" << endl;
                            goto REVERT;
                        }
                        goto l4;
                    }
                    if (option2 == 6) {
                        system("CLS");
                        goto MENUPAGE;
                    }



                }
                else if (choice1 == 3) {
                    continue;
                }
                else {
                    cout << "Invalid Selection..." << endl;
                    goto MENUPAGE;
                }

            }
            else {
                cout << "\nInvalid Password" << endl;
                goto PASSWORD;
            }


        }
        else if (input == 2) {
        system("CLS");
        string userName;
        string email;
        int age;
        string location;
        string password;
        string userID;
    USERNAME:
        cout << "User Name. " << endl;
        cin >> userName;
        for (int i = 0; i < list.users_size(); i++)
        {
            const auto& user = list.users(i);
            if (user.username() == userName)
            {
                cout << "User Name already exists..please select any other" << endl;
                goto USERNAME;
            }
        }
    EMAIL:
        cout << "Email. " << endl;
        cin >> email;
        if (!uPortal.isEmailValid(email))
        {
            cout << "Email is not valid" << endl;
            goto EMAIL;
        }
        cout << "Age. " << endl;
        cin >> age;
        cout << "Location. " << endl;
        cin >> location;
        password = uPortal.getpassword("Enter the password\n");

        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        userID = boost::uuids::to_string(uuid);
        password = sha256(password);

        User* u1 = list.add_users();
        u1->set_username(userName);
        u1->set_age(age);
        u1->set_email(email);
        u1->set_location(location);
        u1->set_password(password);
        u1->set_userid(userID);

        std::ofstream ofs("userList.txt", std::ios_base::out | std::ios_base::binary);
        list.SerializeToOstream(&ofs);
        system("cls");
        goto START;

        }
        else if (input == 3) {
            break;
        }
        else {
            system("CLS");
            cout << "Invalid input" << endl;
            continue;
        }
    }
}

