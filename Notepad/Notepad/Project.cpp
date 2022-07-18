#include<iostream>
#include "main.pb.h"
using namespace std;

class ProjectPortal {
public:
	void addproject(Project* project, string fileName, int id, string userID ) {
		project->set_name(fileName);
		project->set_id(id);
		project->set_userid(userID);
	}
};