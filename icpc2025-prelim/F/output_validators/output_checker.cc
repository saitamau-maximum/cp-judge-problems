#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std; 

using vi=std::vector<int>;
using vvi=std::vector<vi>;
using pii=std::pair<int,int>;

const int MIN_N = 1, MAX_N = 10000;
int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

	for(;;)
	{
		int n = inf.readInt();
		if(n==0)break;
		string s = inf.readToken();
		string t = inf.readToken();
		string bo1 = ans.readToken();
		string bo2 = ouf.readToken();
		if(bo1=="yes"){
			ensuref(bo2=="yes", "ans is yes but output is not yes");
			string r = ouf.readToken();
			string zzz = ans.readToken();
			ensuref(r.size() <= MAX_N, "too long");
			for(int i=0;i<r.size();i++)ensuref(r[i]=='A'||r[i]=='B', "invalid letter");
			for(int i=0;i<r.size();i++){
				int now=0;
				for(int j=0;j<s.size();j++){
					if(now==0){
						if(r[i]=='A'&&s[j]=='a')s[j]='b',now=1;
						if(r[i]=='B'&&s[j]=='b')s[j]='a',now=1;
					}
					else if(now==1){
						if(r[i]=='A'&&s[j]=='b')s[j]='a',now=2;
						if(r[i]=='B'&&s[j]=='a')s[j]='b',now=2;
					}
				}
				ensuref(now==2, "invalid operation");
			}
			ensuref(s==t, "sequence not match");
		}
		else{
			ensuref(bo2=="no", "ans is no but output is not no");
		}
	}
	if (!ouf.seekEof()) quitf(_wa, "Participant output contains extra tokens");
	quitf(_ok,"correct");
	return 0;
}
