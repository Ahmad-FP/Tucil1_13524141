#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n,m;
vector<vector <char> > lanes;
vector<int> loc;
int cnt = 0;
bool found = false;

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
        if(uq2.size() != n)found = false;
        else found = true;
    }
}

void loop(int d){
    confirm();
    for (int i = loc[d]; i < m; i++)
    {
        if(found)break;
        cnt++;
        if(d<n-1){
            loop(d+1);
        }
        loc[d]++;
        confirm();
    }
    
}


int main(){
    cin >> n >> m;
    lanes.resize(n);
    loc.resize(n);
    for (int i = 0; i < m; i++)
    {
        lanes[i].resize(m);
        loc[i] = 0;
    }
    if(n != m)cout << "NIL" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> lanes[i][j];
        }
    }
    loop(0);
    if(!found)cout << "NIL" << endl;
    else{
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
        
    }
}