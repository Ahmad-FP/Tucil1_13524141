#include <iostream>
#include <vector>
#include <unordered_set>
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

bool confirm(){
    for (int i = 1; i < n; i++)
    {
        if(loc[i] == loc[i-1]+1 || loc[i] == loc[i-1]-1)return false;
    }
    return true;
}

void loop(int d,unordered_set<int> &l, vector<int> &lorder, unordered_set<char> &c, vector<char> &corder){
    for(int i = loc[d]; i  < m;i++)
    {
        cnt++;
        if(l.find(loc[d]) == l.end() && c.find(lanes[d][loc[d]]) == c.end()){
            l.insert(loc[d]);lorder.push_back(loc[d]);
            c.insert(lanes[d][loc[d]]); corder.push_back(lanes[d][loc[d]]);
            if (d < n-1)
            {
                loop(d+1,l,lorder,c,corder);
            }
            if(l.size() == n && c.size() == n && !found){
                if(confirm())found = true;
            }
            if(found)break;
            l.erase(lorder.back()); lorder.pop_back();
            c.erase(corder.back()); corder.pop_back();
        }
        loc[d]++;
        loc[d] %= n;
        if(cnt % k == 0){
            output();
        }
    }

}



int main(){
    cin >> n >> m >> k;
    lanes.resize(n);
    loc.resize(n);
    set<char> cntz;
    for (int i = 0; i < m; i++)
    {
        lanes[i].resize(m);
        loc[i] = 0;
    }
    if(n != m){cout << "NIL" << endl;return 0;}
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> lanes[i][j];
            cntz.insert(lanes[i][j]);
        }
    }
    z = cntz.size();
    if(n != z){cout << "NIL" << endl; return 0;}
    unordered_set<int> l;
    unordered_set<char> c;
    vector<int> lorder;
    vector<char> corder;
    loop(0,l,lorder,c,corder);
    if(!found)cout << "NIL" << endl;
    else{
        output();
        
    }
}