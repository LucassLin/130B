
#ifndef DISJOINT_H
#define DISJOINT_H

#include <vector>
using namespace std;

class Disjoint{
private:
    vector<pair<int, int> > s;
    
public:
    Disjoint(int num);
    int find(int i);
    void unionSets(int x, int y);
    
};

Disjoint::Disjoint(int num)
{
    s.reserve(num);
    for(int i=0; i<num; i++){
    	pair<int, int> edge(i, 0);
    	s.push_back(edge);
	}
}


void Disjoint::unionSets(int x, int y)
{
	int root1 = find(x);
	int root2 = find(y);
	if (s[root1].second < s[root2].second){
		s[root1].first = root2;
	}
	else if (s[root1].second > s[root2].second){
		s[root2].first = root1;
	}
	else{
		s[root2].first = root1;
		s[root1].second++;
	}
}

int Disjoint::find(int i)
{
    if(s[i].first != i){
    	s[i].first = find(s[i].first);
	}
	return s[i].first;
}

#endif /* DISJOINT_H */

