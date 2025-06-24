#include <bits/stdc++.h> 
using namespace std;
int solution(vector<int> arr){
    int n=arr.size();
    int count[n]={0};
    for(int i=0;i<n;i++){
        if(arr[i]!=-1){
            count[arr[i]]+=i;
        }
    }
    int maxW=0;
    int nodeNo=0;
    for(int i=0;i<n;i++){
        if(count[i]>maxW){
            maxW= count[i];
            nodeNo=i;  
        }
    }
    return nodeNo;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    int t;
    cin >> t;
    for(int it=1;it<=t;it++) {
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        cout<<solution(arr)<<endl;
    }
    return 0;
}