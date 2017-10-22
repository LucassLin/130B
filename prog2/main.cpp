#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <math.h>  
#include <fstream>
#include "Disjoint.h"

using namespace std;

/*
 * 
 */

bool myComparison(const pair<pair<int, int>, double> &a,const pair<pair<int, int>, double> &b)
{
       return a.second<b.second;
}

bool myComparison1(const pair<int,int> &a,const pair<int,int> &b)
{
       return a.first<b.first;
}

bool myComparison2(const pair<int,int> &a,const pair<int,int> &b)
{
       return a.second<b.second;
}


int main() {
    int n;
    cin >> n;
    vector<pair<double, double> > points(n);
    for (int i=0; i<n; i++)
    {
        double x, y;
        cin >> x;
        cin >> y;
        points[i].first = x;
        points[i].second = y;
    }
    int e;
    cin >> e;
    cout <<endl;
    if(e < n-1){
    	cout << "No minimum spanning tree possible\n";
    	return 0;
	}
    vector<pair<int, int> > edges(e);
    for (int i=0; i<e; i++)
    {
        int x, y;
        cin >> x;
        cin >> y;
        edges[i].first = x;
        edges[i].second = y;
    }
    cout <<endl;
    
	

    vector< pair<pair<int, int>, double> > distance(e);
    for (int i=0; i<e; i++)
    {
        int pointOne = edges[i].first;
        int pointTwo = edges[i].second;
        distance[i].first.first = pointOne;
        distance[i].first.second = pointTwo;
        double x1 = points[pointOne].first;
        double y1 = points[pointOne].second;
        double x2 = points[pointTwo].first;
        double y2 = points[pointTwo].second;
        distance[i].second = sqrt( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }
    
//    
    sort(distance.begin(), distance.end(), myComparison);
    Disjoint set(n);
    vector<pair<int,int> > result;
    int k = 0;
    int d = 0;
    while (k != n-1)
    {
        int one = distance[d].first.first;
        int two = distance[d].first.second;
        if(set.find(one) != set.find(two)){
//        	cout << "Point is " << one <<", union is " <<set.find(one) <<endl;
//        	cout << "Point is " << two <<", union is " <<set.find(two) <<endl;
            pair<int, int> edge(one, two);
            result.push_back(edge);
            set.unionSets(one,two);
            k++;
        }
        d++;
    }
    
	sort(result.begin(), result.end(), myComparison1);
	
    
    int start = 0;
    int end = 0;
    while(start < result.size()){
    	for(int i=0; i<result.size(); i++){
    		if(result[i].first == result[start].first){
    			end++;
			}
		}
		sort(result.begin()+start, result.begin()+end, myComparison2);
		start = end;
	}

    cout<< "The edges are shown below: \n";	
    for(int i=0; i<n-1; i++)
    {
        cout << result[i].first <<" " <<result[i].second <<endl;
    }
    
    
    
    
    
    return 0;
}

