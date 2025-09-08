#include <bits/stdc++.h>
using namespace std;
int findMaxScore(vector<int> arr, int n, int k)
{
    int sc = 0;
    priority_queue<int> pq(arr.begin(), arr.end());
    for (int i = 0; i < k; i++)
    {
        int top = pq.top();
        pq.pop();
        sc += top;
        pq.push(ceil(top / 3));
    }
    return sc;
}
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << findMaxScore(arr, n, k);
    return 0;
}