#include<iostream>
#include<bits/stdc++.h>

using namespace std;

map<string, int> m;

bool isOverlapping(string a, string b, int i, int j, int k, int l) {
	if(a != b)
		return false;

	if(i == k)
		return false;

	if(k>j || l<i)
		return false;

	//print indexes
	//cout<<" i = "<<i<<" j = "<<  j<<" k = "<<k <<" l = "<<l<<endl; 
	if(k <= j)
		return true;
	
	//this condition not required as we are only cheching substrings b coming
	//after a in s.
	//if(l>=i)
	//	return true;
}

void check_overlapping_substring(string s, string subString, int i, int j) {
	int len = j-i;
	
	// start from i to look substrings coming after subString

	for(int k=i; k<s.size(); ++k) {
		if(k + len <= s.size()) {
			string subString2 = "";
			for(int x = k; x < k+len; ++x)
				subString2 = subString2 + s[x];
			
			if(isOverlapping(subString, subString2, i, j-1, k, k+len-1)) {
				
				if(m.find(subString) == m.end()) {
					cout<<"Overlapping Substring " <<subString<<endl;
					m[subString] = 1;
				}
			}
		}
		else break;
	}
}

int main() {

	string s;
	cin>>s;

	int size = s.size();

	for(int len=2; len < size; ++len) {
		for(int i=0; i<size; ++i) {
			if(i+len <= size) {
				string subString = "";
				for(int x=i; x<i+len; ++x)
					subString = subString+s[x];
				check_overlapping_substring(s, subString, i, i+len);
			}
		}
	}
}