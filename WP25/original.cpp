#include<iostream>
#include<string>
#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> states;
vector<string> variables;
vector<string> final_states;
vector<string> intermmediate_states;
string initial_state;

vector< vector<string> > gtg;

void print_gtg() {
    for(int i=0; i<gtg.size(); ++i) {
        for(int j=0; j<gtg[i].size(); ++j) {
            cout<<gtg[i][j] <<" ";
        }
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
    gtg = vector<vector<string> > (states.size(), vector<string> (states.size()));
}

void find_intermmediate_states() {
    for(int i=0; i<states.size(); ++i) {
        if(find(final_states.begin(), final_states.end(), states[i]) == final_states.end()
            && initial_state != states[i])
            intermmediate_states.push_back(states[i]);
    }
}

vector<string> get_prev(int index) {
    vector<string> prev;

    for(int i=0; i<states.size(); ++i) {
        if(i != index && gtg[i][index] != "") {
            prev.push_back(states[i]);
        }
    }
    cout<<"out\n";
    return prev;
}

vector<string> get_next(int index) {
    vector<string> next;

    for(int i=0; i<states.size(); ++i) {
        if(i != index && gtg[index][i] != "") {
            next.push_back(states[i]);
        }
    }
    return next;
}

string find_loop(string state) {
    int index = index_of_state(state);
    if(gtg[index][index] != "") {
        return gtg[index][index];
    }
    return {};
}

void get_regex() {
    for(int i=0; i<intermmediate_states.size(); ++i) {
        vector<string> prev;
        vector<string> next;
        cout<<index_of_state(intermmediate_states[i])<<endl;
        prev = get_prev(index_of_state(intermmediate_states[i]));
        next = get_next(index_of_state(intermmediate_states[i]));

        cout<<prev.size()<<endl;
        cout<<next.size()<<endl;

        for(int j=0; j<prev.size(); ++j) {
            for(int k=0; k<next.size(); ++k) {
                string temp = find_loop(intermmediate_states[i]);
                string update = "";

                update += gtg[index_of_state(prev[j])][index_of_state(next[k])] + " + ";

                update += gtg[index_of_state(prev[j])][index_of_state(intermmediate_states[i])];

                if(temp.length() != 0)
                    update += "(" + temp + ")*";

                update += gtg[index_of_state(intermmediate_states[i])][index_of_state(next[k])];
                cout<<update<<endl;
                gtg[index_of_state(prev[j])][index_of_state(next[k])] = update;

            }
        }
        //cout<<next.size()<<endl;
        //cout<<prev.size()<<endl;
        //cout<<prev[0]<<endl;
        //cout<<"HERE\n";
    }

    print_gtg();

    string sii = gtg[index_of_state(initial_state)][index_of_state(initial_state)];
    string sij = gtg[index_of_state(initial_state)][index_of_state(final_states[0])];
    string sjj = gtg[index_of_state(final_states[0])][index_of_state(final_states[0])];
    string sji = gtg[index_of_state(final_states[0])][index_of_state(initial_state)];

    cout<<"final result"<<endl;
    cout<<sii<<endl;
    cout<<sij<<endl;
    cout<<sjj<<endl;
    cout<<sji<<endl;

}

int main() {

    /************ Input ************/

    freopen("dfa_1.txt", "r+", stdin);
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
            variables.push_back(string(1, s[i]));

    cin>>initial_state;
    initial_state.erase(0, 2);

    cin>>s;
    s.erase(0, 3);
    s.erase(s.length() - 1);
    for(int i=0; i<s.length(); ++i)
        if(isalpha(s[i]))
            final_states.push_back(string(1, s[i]));

    cout<<index_of_state("B")<<endl;

    initialize_gtg();

    for(int i=0; i<gtg.size(); ++i) {
        for(int j=0; j<gtg[i].size(); ++j) {
            gtg[i][j] = "";    
        }
    }

    /**************** End **************/


    /******** GTG Initialization ***********/
    while(cin>>s) {
        s.erase(0, 3);
        int state1 = index_of_state(string(1,s[0]));
        int state2 = index_of_state(string(1, s[4]));
        
        if(gtg[state1][state2] == "")
            gtg[state1][state2] = string(1, s[2]);
        else {
            gtg[state1][state2] += "+" + string(1, s[2]);
        }
    }
    
    // for(int i=0; i<gtg.size(); ++i) {
    //     for(int j=0; j<gtg[i].size(); ++j) {
    //         cout<<gtg[i][j] <<" ";
    //     }
    //     cout<<endl;
    // }

    /*********** End *******************/

    find_intermmediate_states();
    for(int i=0; i<intermmediate_states.size(); ++i)
        cout<<intermmediate_states[i]<<endl;

    get_regex();
    
}