#include "testlib.h"
#include <set>
using namespace std;

bool check(int N, vector<int> P, vector<int> E, vector<int> vis_order) {
	set<int> visited;
	visited.insert(1);

	int t = 0;
	for(int v: vis_order) {
		if(visited.count(v)) {
			quitf(_wa, "Double-visit: %d", v);
			return false;
		}
		if(!visited.count(P[v])) {
			quitf(_wa, "Parent-not-visited: %d (parent %d)", v, P[v]);
			return false;
		}
		if(E[v] < t) {
			quitf(_wa, "Time is over for: %d (limit %d now %d)", v, E[v], t);
			return false;
		}

		++t;
		visited.insert(v);
	}

	if(visited.size() != N) {
			quitf(_wa, "Did not visit all nodes");
			return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
    setName("special validator for problem E");
    registerTestlibCmd(argc, argv);

	for(int nt=1;; ++nt) {
		// read input
		int N = inf.readInt();
		inf.readEoln();
		if(N == 0)
			break;
		setTestCase(nt);
		vector<int> P(N+1);
		vector<int> E(N+1);
		for(int i=2; i<=N; ++i) {
			P[i] = inf.readInt();
			inf.readSpace();
			E[i] = inf.readInt();
			inf.readEoln();
		}

		// read output and answer
		string out_yn = ouf.readWord("yes|no");
		string ans_yn = ans.readWord("yes|no");
		vector<int> out_order;
		vector<int> ans_order;
		if(out_yn=="yes") out_order = ouf.readInts(N-1, 2, N);
		if(ans_yn=="yes") ans_order = ans.readInts(N-1, 2, N);

		// validate
		if(out_yn=="no") {
			if(ans_yn == "no")
				continue;
			else
				quitf(_wa, "Answered \"no\" for a feasible input");
		} else {
			check(N, P, E, out_order);
		}
	}

	// EOF check
	if(ouf.seekEof())
		quitf(_ok, "valiadted all inputs");
	else
		quitf(_wa, "Participant output contains extra tokens");
}
