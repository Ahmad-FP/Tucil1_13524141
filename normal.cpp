#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n,m,z ,k = 10000000;
vector<vector <char> > lanes;
vector<int> loc;
int cnt = 0;
bool found = false;

void output(){
    for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if(loc[i] == j) cout << "#";
                else cout << lanes[i][j];
                if(j < m-1) cout << " ";
            }
            cout << endl;
        }
    cout << "ENDS" << endl;
}

void confirm(){
    set<int> unique;
    for (int i = 0; i < n; i++)
    {
        unique.insert(loc[i]);
    }
    if(unique.size() != n)found = false;
    else{
        set<char> uq2;
        for (int i = 0; i < n; i++)
        {
            uq2.insert(lanes[i][loc[i]]);
        }
        if(uq2.size() != z)found = false;
        else {
            bool f = true;
            for (int i = 1; i < n; i++)
            {
                if(loc[i] == loc[i-1]+1 || loc[i] == loc[i-1]-1){
                    f = false;
                    break;
                }
            }
            found = f;
        }
    }
}

void loop(int d){
    for (int i = loc[d]; i < m; i++)
    {
        cnt++;
        if(d<n-1){
            loop(d+1);
        }
        if(found)break;
        loc[d]++;
        loc[d] %= m;
        if(d == n-1){
            confirm();
        }
        if(found)break;
        if(cnt % k == 0){
            output();
        }
    }
}



int main(){
    cin >> n >> m >> k;
    lanes.resize(n);
    loc.resize(n);
    set <char> cntz;
    for (int i = 0; i < m; i++)
    {
        lanes[i].resize(m);
        loc[i] = 0;
    }
    if(n != m){cout << "NIL" << endl; return 0;}
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> lanes[i][j];
            cntz.insert(lanes[i][j]);
        }
    }
    z= cntz.size();
    if(n != z){cout << "NIL" << endl; return 0;}
    loop(0);
    if(!found)cout << "NIL" << endl;
    else{
        output();
    }
}