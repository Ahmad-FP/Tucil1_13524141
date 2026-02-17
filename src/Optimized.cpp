#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <chrono>

using namespace std;

int n,m,z ,k = 10000000;
vector<vector <char> > lanes;
vector<int> loc;
int cnt = 0;
vector<vector<bool> > chck;
bool found = false;
unordered_map<char,bool> check;


void outputO(){
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
    cout << "-----------------------------" << endl;
}

bool confirmO(){
    cnt++;
    for (int i = 1; i < n; i++)
    {
        if(loc[i] == loc[i-1]+1 || loc[i] == loc[i-1]-1)return false;
    }
    return true;
}

void loopO(int d,unordered_set<int> &l, vector<int> &lorder, unordered_set<char> &c, vector<char> &corder){
    for(int i = loc[d]; i  < m;i++)
    {
        cnt++;
        if(l.find(loc[d]) == l.end() && c.find(lanes[d][loc[d]]) == c.end()){
            l.insert(loc[d]);lorder.push_back(loc[d]);
            c.insert(lanes[d][loc[d]]); corder.push_back(lanes[d][loc[d]]);
            if (d < n-1)
            {
                loopO(d+1,l,lorder,c,corder);
            }
            if(l.size() == n && c.size() == n && !found){
                if(confirmO())found = true;
            }
            if(found)break;
            l.erase(lorder.back()); lorder.pop_back();
            c.erase(corder.back()); corder.pop_back();
        }
        loc[d]++;
        loc[d] %= n;
        if(cnt % k == 0){
            outputO();
        }
    }

}

void dive(int i, int j){
    chck[i][j]= true;
    if(i > 0 && lanes[i-1][j] == lanes[i][j] && !chck[i-1][j])dive(i-1,j);
    if(i < n-1 && lanes[i+1][j]== lanes[i][j] && !chck[i+1][j])dive(i+1,j);
    if(j > 0 && lanes[i][j-1]== lanes[i][j] && !chck[i][j-1])dive(i,j-1);
    if(j < n-1 && lanes[i][j+1]== lanes[i][j] && !chck[i][j+1])dive(i,j+1);
}

void solveO(string texto,int kslide){
    int row = 0;
    int col = 0;
    int maxcol = 0;
    k = kslide;
    loc.clear();
    lanes.clear();
    found = false;
    cnt = 0;
    vector<char> tmp;
    for (int i = 0; i < texto.size(); i++)
    {
        if (texto[i] == '\r')continue;
        if(texto[i] == '\n' || texto[i] == ' '){
            if(row == 0){
                maxcol = col;
            }
            if(col != maxcol){
                cout << "Row tidak lengkap" << endl;
                return; 
            }
            col = 0;
            row++;
            lanes.push_back(tmp);
            tmp.clear();
        }else{
            check[texto[i]] = false;
            tmp.push_back(texto[i]);
            col++;
        }
    }
    if(tmp.size() != 0){
        if(tmp.size() != maxcol){
            cout << "Row tidak lengkap" << endl;
            return;
        }
        lanes.push_back(tmp);
        row++;
    }
    n = row; m = maxcol;
    set<char> cntz;
    loc.assign(n,0);
    if(n != m){cout << "N != M" << endl; return;}
    chck.assign(n,vector<bool>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (check[lanes[i][j]] && !chck[i][j])
            {
                cout << "INVALID INPUT (Warna tidak membentuk satu kelompok)" << endl;
                return;
            }else if (!check[lanes[i][j]]){
                check[lanes[i][j]] = true;
                dive(i,j);
            }
            cntz.insert(lanes[i][j]);
        }
    }
    z = cntz.size();
    if(n != z){cout << "Jumlah warna != N" << endl; return;}
    unordered_set<int> l;
    unordered_set<char> c;
    vector<int> lorder;
    vector<char> corder;
    auto start = chrono::high_resolution_clock::now();
    loopO(0,l,lorder,c,corder);
    auto end = chrono::high_resolution_clock::now();
    if(!found)cout << "Tidak ada solusi" << endl;
    else{
        outputO();
        cout << "FOUND" << endl;
        chrono::duration<double,milli> t = end - start;
        cout << "Waktu Pencarian : " << t << endl;;
        cout << "Banyak Kasus Yang Di Tinjau: " << cnt << endl;


    }
}