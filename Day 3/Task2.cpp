#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int bfs(int N, int M, int **arr, int *start, int *end);
int main()
{
    int N = 0;
    int M = 0;
    cout << "Enter the no of rows" << endl;
    cin >> N;
    cout << "Enter the no of columns" << endl;
    cin >> M;
    // Create a dynamic matrix:
    int **arr = new int *[N];
    cout << "Enter all the matrix values" << endl;
    for (int i = 0; i < N; i++)
    {
        arr[i] = new int[M];
        for (int j = 0; j < M; j++)
        {
            cin >> arr[i][j];
        }
    }
    int leader[5][2] = {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 0}};
    int size_of_leader = sizeof(leader) / sizeof(leader[0]);

    // for group 1:
    int grp_one[2][2] = {{0, 3}, {0, 4}};
    int size_of_grp1 = sizeof(grp_one) / sizeof(grp_one[0]);
    int min1 = __INT_MAX__;
    for (int i = 0; i < size_of_leader; i++)
    {
        for (int j = 0; j < size_of_grp1; j++)
        {
            int temp = bfs(N, M, arr, leader[i], grp_one[j]);
            if (temp < min1)
            {
                min1 = temp;
            }
        }
    }
    cout << "The Min distance between leader {11} and grp1 {4} is " << min1 << endl;

    // for group 2:
    int grp_two[2] = {3, 1};
    int min2 = __INT_MAX__;
    for (int i = 0; i < size_of_leader; i++)
    {
        int temp = bfs(N, M, arr, leader[i], grp_two);
        if (temp < min2)
        {
            min2 = temp;
        }
    }
    cout << "The Min distance between leader {11} and grp2 {1} is " << min2 << endl;

    // for group 3:
    int grp_three[4][2] = {
        {3, 3},
        {3, 4},
        {4, 2},
        {4, 3},
    };
    int size_of_grp3 = sizeof(grp_three) / sizeof(grp_three[0]);
    int min3 = __INT_MAX__;
    for (int i = 0; i < size_of_leader; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int temp = bfs(N, M, arr, leader[i], grp_three[j]);
            if (temp < min3)
            {
                min3 = temp;
            }
        }
    }
    cout << "The Min distance between leader {11} and grp3 {7} is " << min3 << endl;

    // Free out all the dynamic memory used
    for (int i = 0; i < M; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    arr = NULL;
}

int bfs(int N, int M, int **arr, int *start, int *end)
{
    int *init = new int[3];
    init[0] = start[0];
    init[1] = start[1];
    init[2] = 0;
    queue<int *> q;
    q.push(init);

    // vector<vector<bool>> visited(5, vector<bool>(5, false));
    bool flag[5][5] = {
        {false,
         false,
         false,
         false,
         false},
        {false,
         false,
         false,
         false,
         false},
        {false,
         false,
         false,
         false,
         false},
        {false,
         false,
         false,
         false,
         false},
        {false,
         false,
         false,
         false,
         false}};
    flag[start[0]][start[1]] = true;
    while (!q.empty())
    {
        int *p = q.front();      //{0,0}
        int x = p[0];            // 0
        int y = p[1];            // 0
        int lengthOfPath = p[2]; // 1
        q.pop();
        int neighbours[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        for (int *neighbour : neighbours)
        {
            int newx = neighbour[0] + x;
            int newy = neighbour[1] + y;
            if (newx == end[0] && newy == end[1])
                return lengthOfPath;
            if (newx >= 0 && newy >= 0 && newx < N && newy < M && arr[newx][newy] == 0 &&
                !flag[newx][newy])
            {
                int *newState = new int[3];
                newState[0] = newx;
                newState[1] = newy;
                newState[2] = lengthOfPath + 1;
                q.push(newState);
                flag[newx][newy] = true;
            }
        }
    }
    delete[] init;
    init = NULL;
    return __INT_MAX__;
}
