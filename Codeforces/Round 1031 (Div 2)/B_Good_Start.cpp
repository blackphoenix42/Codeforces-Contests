#include <bits/stdc++.h>
using namespace std;
void tilesGen()
{
    long long w, h, a, b;
    cin >> w >> h >> a >> b;
    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    bool x_axis = false;
    if ((y1 - y2) % b == 0)
    {
        if (y1 == y2)
        {
            if ((x1 - x2) % a == 0)
            {
                x_axis = true;
            }
        }
        else
        {
            x_axis = true;
        }
    }

    bool y_axis = false;
    if ((x1 - x2) % a == 0)
    {
        if (x1 == x2)
        {
            if ((y1 - y2) % b == 0)
            {
                y_axis = true;
            }
        }
        else
        {
            y_axis = true;
        }
    }

    if (x_axis || y_axis)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        tilesGen();
    }
    return 0;
}
