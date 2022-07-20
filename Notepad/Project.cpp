#include<iostream>
#include<conio.h>
#include "user.pb.h"
#include "version.pb.h"
#include "project.pb.h"
using namespace std;

class ProjectPortal {
public:
	void addproject(Project* project, string fileName,string projectId, string userID ) {
		project->set_name(fileName);
		project->set_id(projectId);
		project->set_userid(userID);
	}
	
};