#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <unordered_map>

using namespace std;

int nn,mn,zn ,kn = 10000000;
vector<vector <char> > lanesn;
vector<int> locn;
int cntn = 0;
vector<vector<bool> > chckn;
bool foundn = false;
unordered_map<char,bool> checkn;

void outputN(){
    for (int i = 0; i < nn; i++)
        {
            for (int j = 0; j < mn; j++)
            {
                if(locn[i] == j) cout << "#";
                else cout << lanesn[i][j];
                if(j < mn-1) cout << " ";
            }
            cout << endl;
        }
    cout << "-------------------------" << endl;
}

void confirmN(){
    set<int> unique;
    for (int i = 0; i < nn; i++)
    {
        unique.insert(locn[i]);
    }
    if(unique.size() != nn)foundn = false;
    else{
        set<char> uq2;
        for (int i = 0; i < nn; i++)
        {
            uq2.insert(lanesn[i][locn[i]]);
        }
        if(uq2.size() != zn)foundn = false;
        else {
            bool fn = true;
            for (int i = 1; i < nn; i++)
            {
                if(locn[i] == locn[i-1]+1 || locn[i] == locn[i-1]-1){
                    fn = false;
                    break;
                }
            }
            foundn = fn;
        }
    }
}

void loopN(int dn){ 
    for (int i = locn[dn]; i < mn; i++)
    {
        if(dn<nn-1){
            loopN(dn+1);
        }
        if(foundn)break;
        locn[dn]++;
        locn[dn] %= mn;
        if(dn == nn-1){
            cntn++;
            confirmN();
        }
        if(foundn)break;
        if(cntn % kn == 0){
            outputN();
        }
    }
}

void diven(int i, int j){
    chckn[i][j]= true;
    if(i > 0 && lanesn[i-1][j] == lanesn[i][j] && !chckn[i-1][j])diven(i-1,j);
    if(i < nn-1 && lanesn[i+1][j]== lanesn[i][j] && !chckn[i+1][j])diven(i+1,j);
    if(j > 0 && lanesn[i][j-1]== lanesn[i][j] && !chckn[i][j-1])diven(i,j-1);
    if(j < nn-1 && lanesn[i][j+1]== lanesn[i][j] && !chckn[i][j+1])diven(i,j+1);
}


void solveN(string textn,int ksliden){
    int rown = 0;
    int coln = 0;
    int maxcoln = 0;
    kn = ksliden;
    locn.clear();
    lanesn.clear();
    foundn = false;
    cntn = 0;
    vector<char> tmpn;
    for (int i = 0; i < textn.size(); i++)
    {
        if (textn[i] == '\r')continue;
        if(textn[i] == '\n' || textn[i] == ' '){
            if(rown == 0){
                maxcoln = coln;
            }
            if(coln != maxcoln){
                cout << "Row tidak lengkap" << endl;
                return; 
            }
            coln = 0;
            rown++;
            lanesn.push_back(tmpn);
            tmpn.clear();
        }else{
            checkn[textn[i]] = false;
            tmpn.push_back(textn[i]);
            coln++;
        }
    }
    if(tmpn.size() != 0){
        if(tmpn.size() != maxcoln){
            cout << "Row tidak lengkap" << endl;
            return;
        }
        lanesn.push_back(tmpn);
        rown++;
    }
    nn = rown; mn = maxcoln;
    set <char> cntnz;
    locn.assign(nn,0);
    if(nn != mn){cout << "N != M" << endl; return;}
    chckn.assign(nn,vector<bool>(nn,false));
    for (int i = 0; i < nn; i++)
    {
        for (int j = 0; j < mn; j++)
        {
            if (checkn[lanesn[i][j]] && !chckn[i][j])
            {
                cout << "INVALID INPUT (Warna tidak membentuk satu kelompok)" << endl;
                return;
            }else if (!checkn[lanesn[i][j]]){
                checkn[lanesn[i][j]] = true;
                diven(i,j);
            }
            cntnz.insert(lanesn[i][j]);
        }
    }
    zn= cntnz.size();
    if(nn != zn){cout << "Jumlah warna != N" << endl; return; }
    auto startn = chrono::high_resolution_clock::now();
    loopN(0);
    auto endn = chrono::high_resolution_clock::now();
    if(!foundn)cout << "Tidak ada solusi" << endl;
    else{
        outputN();
        cout << "FOUND" << endl;
        chrono::duration<double,milli> tn = endn - startn;
        cout << "Waktu Pencarian : " << tn << endl;;
        cout << "Banyak Kasus Yang Di Tinjau: " << cntn << endl;
    }
}