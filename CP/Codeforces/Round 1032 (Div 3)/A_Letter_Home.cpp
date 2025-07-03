#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, s;
        cin >> n >> s;
        vector<int> x(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> x[i];
        }

        int min_x = *min_element(x.begin(), x.end());
        int max_x = *max_element(x.begin(), x.end());

        int steps = (max_x - min_x) + min(abs(s - min_x), abs(s - max_x));

        cout << steps << endl;
    }
    return 0;
}
