#include <bits/stdc++.h>
using namespace std;

int main()
{
    int arr [] = {10,15,20,13,6,90};

    // By Defaulat Max Heap
    // priority_queue<int> heap;

    // Min Heap
    priority_queue<int, vector<int>,greater<int>> heap;

    for (int x : arr){
        heap.push(x);
    }

    while(!heap.empty()){
        cout<<heap.top()<<endl;
        heap.pop();
    }

    return 0;
}