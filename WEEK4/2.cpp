#include <bits/stdc++.h>
using namespace std;
typedef struct desc
{
    int pos;
    int amt;
} desc;
void findTotalItem(vector<int> arr, int n, int q, vector<desc> vec)
{
    int sum = 0;
    for (int i = 0; i < q; i++)
    {
        if (arr[vec[i].pos - 1] < vec[i].amt)
        {
            sum += arr[vec[i].pos - 1];
            vec[i].amt -= arr[vec[i].pos - 1];
        }
        else
            break;
    }
}
int main()
{
    int n, q, pos;
    cin >> n >> q;
    vector<int> arr(n);
    // vector<int, int> desc(q);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<desc> vec(q);
    for (int i = 0; i < q; i++)
    {
        cin >> vec[i].amt >> vec[i].pos;
    }
    findTotalItem(arr, n, q, vec);
    return 0;
}