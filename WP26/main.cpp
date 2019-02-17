#include<iostream>
#include<string>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> states;
vector<string> alphabets;
vector<string> f_states;
vector<string> intermmediate_states;
string initial_state;

vector< vector < vector<string> > > gtg;

vector< vector < vector<string> > > new_gtg;
string current_final;

void print_gtg(int k) {
    cout<<"gtg\n";
    for(int i=0; i<gtg.size(); ++i) {
        for(int j=0; j<gtg[i].size(); ++j)
            cout<<gtg[i][j][k] <<"   ";
        cout<<endl;
    }
}

int index_of_state(string state) {
    for(int i=0; i<states.size(); ++i)
        if(states[i] == state)
            return i;
    return -1;
}

void initialize_gtg() {
    gtg = vector< vector< vector<string> > > (states.size(), vector<vector<string> >(states.size(), vector<string> (states.size())));
    for(int i=0; i<gtg.size(); ++i) {
        for(int j=0; j<gtg[i].size(); ++j) {
            gtg[i][j][0] = "&";    
        }
    }
}

void find_intermmediate_states() {
    for(int i=0; i<states.size(); ++i) {
        if(current_final != states[i]
            && initial_state != states[i])
            intermmediate_states.push_back(states[i]);
    }
}

int main() {

    /************ Input ************/

    freopen("dfa_0.txt", "r+", stdin);
    string s;
    cin>>s;

    s.erase(0, 3);
    s.erase(s.length() - 1);

    for(int i=0; i<s.length(); ++i) {
        if(isalpha(s[i]))
            states.push_back(string(1, s[i]));
    }

    cin>>s;
    s.erase(0, 4);
    s.erase(s.length() - 1);
    for(int i=0; i<s.length(); ++i)
        if(isalnum(s[i]))
            alphabets.push_back(string(1, s[i]));

    cin>>initial_state;
    initial_state.erase(0, 2);

    cin>>s;
    s.erase(0, 3);
    s.erase(s.length() - 1);
    for(int i=0; i<s.length(); ++i)
        if(isalpha(s[i]))
            f_states.push_back(string(1, s[i]));

    //cout<<index_of_state("B")<<endl;

    initialize_gtg();

    

    /**************** End **************/


    /******** GTG Initialization ***********/
    while(cin>>s) {
        s.erase(0, 3);
        int state1 = index_of_state(string(1, s[0]));
        int state2 = index_of_state(string(1, s[4]));
        
        if(gtg[state1][state2][0] == "&")
            gtg[state1][state2][0] = string(1, s[2]);
        else
            gtg[state1][state2][0] += "+" + string(1, s[2]);
    }

    print_gtg(0);
    
    new_gtg = gtg;

    /*********** End *******************/

    // find_intermmediate_states();
    //for(int i=0; i<intermmediate_states.size(); ++i)
    //    cout<<intermmediate_states[i]<<endl;

    int n = states.size();
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(i == j)
                gtg[i][j][0] = '&';
            else 
                gtg[i][j][0] = '&';
            for(auto a : alphabets) {
                cout<<new_gtg[i][j][0] << "  " <<a<<endl;
                if(new_gtg[i][j][0] == a)
                    gtg[i][j][0] += "+" + a;
            }
        }
    }

    //print_gtg(0);

    for(int k=1; k<n; ++k)
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j) {
                //cout<<"here"<<endl;
                gtg[i][j][k] = gtg[i][j][k-1] + "+" + gtg[i][k][k-1] + "("+gtg[k][k][k-1]+")*" + gtg[k][j][k-1];
            }

    print_gtg(1);
    print_gtg(2);
    
    print_gtg(n-1);


}