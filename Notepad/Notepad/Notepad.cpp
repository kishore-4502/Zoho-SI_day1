#include <iostream>
#include <fstream>
#include "main.pb.h"
#include "User.cpp"
#include "Project.cpp"
#include <cstdio>
#include<direct.h>
#include <ctime>
//#pragma warning(disable : 4996)



using namespace std;


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
            cout << "Enter your user ID" << endl;
            cin >> userID;
            for (int i = 0; i < list.users_size(); i++)
            {
                const auto& user = list.users(i);
                if (user.userid() == userID) {
                    index = i;
                }
            }
            if (index == -1) {
                cout << "Invalid user Id" << endl;
                goto USID;
            }

        PASSWORD:
            cout << "Enter the Password" << endl;
            cin >> password;
            if (list.users(index).password() == uPortal.encrypt(password)) {
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
                    l1:
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
                    int id=0;
                    if (ind != -1) {
                        cout << "File Name already exists..." << endl;
                        goto l1;
                    }

                   for (int i = 0; i < fileName.size(); i++) {
                          id += fileName[i];
                   }
                   id += fileName.size();
                   pPortal.addproject(projects.add_projects(), fileName, id, list.users(index).username());
                   char* loc = &fileName[0];
                   string str = fileName + "/versions";
                   char* vLoc = &str[0];
                   int n=_mkdir(loc);
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
                        system("CLS");
                        for (int i = 0; i < projects.projects_size(); i++)
                        {
                            cout << projects.projects(i).name() << endl;
                        }
                        cout << "\n" << endl;
                        cout << "Please select a project to open...Enter 0 to go back..." << endl;
                        int projNum;
                        cin >> projNum;
                        if (projNum == 0) {
                            system("CLS");
                            goto MENUPAGE;
                        }
                        string rootDir = projects.projects(projNum - 1).name() + "/";
                        string location = projects.projects(projNum - 1).name()+"/"+ projects.projects(projNum - 1).name();
                        string versionsLocation = projects.projects(projNum - 1).name() + "/versions";
                        string verDir = rootDir + "versionDetails.txt";
                        
                        
                            l4:
                            system("CLS");
                            Project selectedProject;
                            ifstream projectFile;
                            projectFile.open(location, ios::in | ios::binary);
                            selectedProject.ParseFromIstream(&projectFile);
                            selectedProject.set_name(projects.projects(projNum-1).name());
                            selectedProject.set_id(projects.projects(projNum - 1).id());
                            selectedProject.set_userid(projects.projects(projNum - 1).userid());


                            l3:
                            system("CLS");
                            Version v1;
                            v1.set_projectid(selectedProject.name());
                            ifstream temp;
                            temp.open(verDir, ios::in | ios::binary);
                            v1.ParseFromIstream(&temp);

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
                                v1.set_changescount(v1.changescount()+1);
                                std::ofstream ofs(location, std::ios_base::out | std::ios_base::binary);
                                selectedProject.SerializeToOstream(&ofs);

                                if (v1.changescount() == 5) {
                                    v1.set_changescount(0);
                                    char currTime[10];
                                    time_t my_time = time(NULL);
                                    sprintf(currTime, ctime(&my_time));
                                    v1.add_createdtime(currTime);
                                    string path = versionsLocation + "/" + to_string(v1.versionnumber())+".txt";
                                    std::ofstream ofs(path, std::ios_base::out | std::ios_base::binary);
                                    v1.set_versionnumber(v1.versionnumber()+1);
                                    selectedProject.SerializeToOstream(&ofs);
                                }
                                //write changes in v1:
                                std::ofstream temp1(verDir, std::ios_base::out | std::ios_base::binary);
                                v1.SerializeToOstream(&temp1);
                                goto l3;
                            }
                            if (option2 == 3) {
                                system("CLS");
                                int lineNum;
                                string inp;
                                cout << "Enter the line number you want to change." << endl;
                                cin >> lineNum;
                                cout << "Enter the new content for that line." << endl;
                               // cin >> inp;
                                cin.ignore();
                                getline(cin, inp);
                                selectedProject.set_text(lineNum -1,inp);
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
                                goto l3;
                            }
                            if (option2 == 4) {
                                system("CLS");
                                Project newProj;
                                newProj.set_name(selectedProject.name());
                                newProj.set_id(selectedProject.id());
                                newProj.set_userid(selectedProject.userid());
                                int lineNum;
                                cout << "Enter the line number to be deleted." << endl;
                                cin >> lineNum;
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
                                goto l4;
                            }
                            if (option2 == 5) {
                                system("CLS");
                                cout << "Please select a version to revert to" << endl;
                                for (int i = 0; i < v1.versionnumber();i++) {
                                    cout << "Version " << i<<" --- "<<v1.createdtime(i) << endl;
                                }
                                int opt;
                                cin >> opt;
                                string str = selectedProject.name() + "/versions/" + to_string(opt) + ".txt";
                                //Read from version file and store it in selectedProject:
                                ifstream projectFile;
                                projectFile.open(str, ios::in | ios::binary);
                                selectedProject.ParseFromIstream(&projectFile);
                                //write it back in project file:
                                std::ofstream op(location, std::ios_base::out | std::ios_base::binary);
                                selectedProject.SerializeToOstream(&op);
                                goto l3;
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
                    cout << "Invalid Password" << endl;
                    goto PASSWORD;
                }


            }
            else if (input == 2) {
                system("CLS");

                string userName;
                string email;
                int age;
                string location;
                string userID;
                string password;

                cout << "Please sign-up to continue!" << endl;
                cout << "User Name. " << endl;
                cin >> userName;


            EMAIL:
                cout << "Email. " << endl;
                cin >> email;
                if (!uPortal.isEmailValid(email)) {
                    cout << "Email is not valid" << endl;
                    goto EMAIL;
                }

                cout << "Age. " << endl;
                cin >> age;

                cout << "Location. " << endl;
                cin >> location;

            USERID:
                cout << "Enter a unique user ID. " << endl;
                cin >> userID;
                for (int i = 0; i < list.users_size(); i++)
                {
                    const auto& user = list.users(i);
                    if (user.userid() == userID) {
                        cout << "User ID already exists..please select any other" << endl;
                        goto USERID;
                    }

                }

                cout << "Enter a Password. " << endl;
                cin >> password;
                password = uPortal.encrypt(password);
                User *u1= list.add_users();
                u1->set_username(userName);
                u1->set_age(age);
                u1->set_email(email);
                u1->set_location(location);
                u1->set_userid(userID);
                u1->set_password(password);
                
                std::ofstream ofs("userList.txt", std::ios_base::out | std::ios_base::binary);
                list.SerializeToOstream(&ofs);
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

