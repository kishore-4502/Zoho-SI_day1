#include <iostream>
using namespace std;

// Input
// 0 2 0 3 1
// 4 1 2 0 0
// 2 0 0 0 0
// 0 1 0 2 3
// 0 0 1 1 0

int func(int N, int M, int **arr, int i, int j, int **flag);
int leader(int *ptr, int size);
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
    // A flag matrix to check whether the place is already added or not
    int **flag = new int *[N];
    for (int i = 0; i < N; i++)
    {
        flag[i] = new int[M];
        for (int j = 0; j < M; j++)
        {
            flag[i][j] = -1;
        }
    }
    // Another array to store answers
    int *ans = new int[M * N];
    for (int i = 0; i < (M * N); i++)
    {
        ans[i] = -1;
    }
    // Lets calculate the neighbour value for all the groups in the matrix
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (flag[i][j] == -1)
            {
                int temp = func(N, M, arr, i, j, flag);
                if (temp > 0)
                {
                    ans[k] = temp;
                    k++;
                }
            }
        }
    }
    int ans_size = 0;
    cout << "\nThe Possible groups are" << endl;
    for (int i = 0; i < (M * N); i++)
    {
        if (ans[i] == -1)
        {
            break;
        }
        cout << ans[i] << " ";
        ans_size++;
    }
    // TO determine the leader
    cout << "\nThe Leader Group is ";
    cout << leader(ans, ans_size) << endl;

    // Free out all the dynamic memory used
    for (int i = 0; i < M; i++)
    {
        delete[] arr[i];
        delete[] flag[i];
    }
    delete[] arr;
    arr = NULL;
    delete[] flag;
    flag = NULL;
    delete[] ans;
    ans = NULL;
}

// Given a position, the following function will return the sum of its neighbour values
int func(int N, int M, int **arr, int i, int j, int **flag)
{
    if (arr[i][j] == 0)
    {
        return 0;
    }
    int right = 0;
    int left = 0;
    int up = 0;
    int down = 0;
    flag[i][j] = 1;
    if (j + 1 < N && flag[i][j + 1] == -1)
    {
        flag[i][j + 1] = 1;
        right += func(N, M, arr, i, j + 1, flag);
    }
    if (j - 1 >= 0 && flag[i][j - 1] == -1)
    {
        flag[i][j - 1] = 1;
        left += func(N, M, arr, i, j - 1, flag);
    }
    if (i + 1 < M && flag[i + 1][j] == -1)
    {
        flag[i + 1][j] = 1;
        down += func(N, M, arr, i + 1, j, flag);
    }
    if (i - 1 >= 0 && flag[i - 1][j] == -1)
    {
        flag[i - 1][j] = 1;
        up += func(N, M, arr, i - 1, j, flag);
    }
    return (arr[i][j] + right + left + up + down);
}
int leader(int *ptr, int size)
{
    int leader = 0;
    for (int i = 0; i < size; i++)
    {
        if (ptr[i] > leader)
        {
            leader = ptr[i];
        }
    }
    return leader;
}
