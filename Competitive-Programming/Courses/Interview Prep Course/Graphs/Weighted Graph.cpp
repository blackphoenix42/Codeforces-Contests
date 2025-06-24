
#include <bits/stdc++.h>
using namespace std;

class Graph
{
    unordered_map<string, list<pair<string, int>>> l;

public:
    void addEdge(string x, string y, bool bidir, int wt)
    {
        l[x].push_back(make_pair(y, wt));
        if (bidir)
            l[y].push_back(make_pair(x, wt));
    }
    void printEdge()
    {
        for (auto p : l)
        {
            string city = p.first;
            list<pair<string, int>> nbrs = p.second;
            cout << city << " ->";
            for (auto nbr : nbrs)
            {
                string dest = nbr.first;
                int dist = nbr.second;
                cout << dest << " " << dist << ",";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g;
    // true for bidirectional edge and number is weight
    g.addEdge("A", "B", true, 20);
    g.addEdge("B", "D", true, 40);
    g.addEdge("A", "C", true, 10);
    g.addEdge("C", "D", true, 30);
    g.addEdge("A", "D", false, 50);
    g.printEdge();
    return 0;
}
