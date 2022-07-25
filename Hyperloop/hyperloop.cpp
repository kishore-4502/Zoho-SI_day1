#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Passenger {
public:
    string name;
    int age;
    char destination;
    Passenger(string name,int age,char destination) {
        this->name = name;
        this->age = age;
        this->destination = destination;
    }
};

class Hyperloop
{
public:
    bool isInitialized = false;
    int noOfStations = 0;
    int sPoint=0;
    vector<vector<pair<int, int>>> adjPoints;
    vector<int> minDist;
    vector<int> parent;
    vector<string> paths;

    int toInt(char ch) {
        return toupper(ch) - 'A';
    }

    void init() {
        isInitialized = true;
        cout << "Enter the No of stations" << endl;
        int noOfStations;
        cin >> noOfStations;
        this->noOfStations = noOfStations;
        for (int i = 0; i < noOfStations; i++)
        {
            vector<pair<int, int>> temp;
            adjPoints.push_back(temp);
            parent.push_back(-1);
            minDist.push_back(INT_MAX);
        }
        cout << "Enter the starting location" << endl;
        char startingPoint;
        cin >> startingPoint;
        int sPoint = toInt(startingPoint);
        this->sPoint = sPoint;

        cout << "Enter the No of Interconnecting points" << endl;
        int noOfPoints;
        cin >> noOfPoints;
        for (int i = 0; i < noOfPoints; i++)
        {
            char start, end;
            int dist;
            cin >> start >> end >> dist;
            int s = toInt(start);
            int e = toInt(end);
            adjPoints[s].push_back({ e,dist });
            adjPoints[e].push_back({ s,dist });
        }

    }
    string constructPath(int destination)
    {
        string path;
        int index = destination;
        while (index >= 0)
        {
            path += char(index+'A');
            index = parent[index];
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void minDistance()
    {
        priority_queue<pair<int, int>,vector<pair<int, int>>,greater<pair<int,int>>> pq;
        minDist[sPoint] = 0;
        pq.push(make_pair( 0,sPoint));
        while (!pq.empty()) {
            int distance = pq.top().first;
            int vertex = pq.top().second;
            pq.pop();
            vector<pair<int, int>>::iterator it;
            for (auto it : adjPoints[vertex]) {
                int nextpoint = it.first;
                int additionalDist = it.second;
                if (distance + additionalDist < minDist[nextpoint])
                {
                    minDist[nextpoint] = distance + additionalDist;
                    pq.push(make_pair(minDist[nextpoint], nextpoint));
                    parent[nextpoint] = vertex;
                }
            }
        }
        for (int i = 0; i < minDist.size(); i++)
        {
            paths.push_back(constructPath(i));
        }
    }
    void PrintDis() {
        for (int i = 0; i < minDist.size(); i++) {
            cout << minDist[i] << " ";
        }
        cout << endl;
    }
    void PrintPath() {
        for (int i = 0; i < paths.size(); i++) {
            cout << paths[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Hyperloop hyperloop;
    vector<Passenger> passengersList;
    while (true)
    {
        cout << "1--INIT\n2--ADD_PASSENGER\n3--START_POD\n4--PRINT_Q\n5--EXIT" << endl;
        int option;
        cin >> option;
        if (option == 1)
        {
            system("cls");
            hyperloop.init();
            hyperloop.minDistance();
            //hyperloop.PrintDis();
            //hyperloop.PrintPath();
        }
        else if (option == 2)
        {
            system("cls");
            if (hyperloop.isInitialized) {
                cout << "Enter the Passenger name" << endl;
                string name;
                cin >> name;
                cout << "Enter the Age" << endl;
                int age;
                cin >> age;
                cout << "Enter your destination" << endl;
                char destination;
                cin >> destination;
                Passenger p1(name, age, destination);
                passengersList.push_back(p1);
            }
            else {
                cout << "Please Initialize Hyperloop" << endl;
            }
        }
        else if (option == 3)
        {
            system("cls");
            if (hyperloop.isInitialized) {
                cout << "Enter the no of passengers" << endl;
                int noOfPassengers;
                cin >> noOfPassengers;
                for (int count = 0; count < noOfPassengers; count++) {
                    int oldIndex = -1;
                    int oldAge = 0;
                    for (int i = 0; i < passengersList.size(); i++) {
                        Passenger temp = passengersList[i];
                        if (temp.age > oldAge) {
                            oldAge = temp.age;
                            oldIndex = i;
                        }
                    }
                    int x = hyperloop.toInt(passengersList[oldIndex].destination);
                    cout << passengersList[oldIndex].name<<" " << hyperloop.paths[x] << endl;
                    passengersList.erase(passengersList.begin() + oldIndex);
                }
            }
            else {
                cout << "Please Initialize Hyperloop" << endl;
            }
        }
        else if (option == 4)
        {
            system("cls");
            if (hyperloop.isInitialized) {
                cout << "Passengers Remaining : " << passengersList.size() << endl;
                for (int i = 0; i < passengersList.size(); i++) {
                    Passenger temp = passengersList[i];
                    cout << temp.name << " " << temp.age << endl;
                }
            }
            else {
                cout << "Please Initialize Hyperloop" << endl;
            }
        }
        else if (option == 5) {
            system("cls");
            break;
        }
        else {
            system("cls");
            cout << "Invalid Selection" << endl;
        }
    }
}

