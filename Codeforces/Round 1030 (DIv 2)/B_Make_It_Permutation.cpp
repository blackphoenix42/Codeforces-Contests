#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        cout << 2 * (n - 1) << endl;
        for (int i = 2; i <= n; ++i)
        {
            cout << i << " 1 " << n << endl;
            cout << i << " 2 " << n << endl;
        }
        /*
        1 2 3 4
        1 2 3 4
        1 2 3 4
        1 2 3 4


        1 2 3 4     1 2 3 4
        4 3 2 1     4 1 2 3
        1 2 3 4     1 2 3 4
        1 2 3 4     1 2 3 4

        1 2 3 4     1 2 3 4
        4 3 2 1     4 1 2 3
        1 2 3 4     1 2 3 4
        1 2 3 4     1 2 3 4        


        */
    }
    return 0;
}
