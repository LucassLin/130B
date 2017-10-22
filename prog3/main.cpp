#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

double dist(pair<pair<double, double>, double>p1, pair<pair<double, double>, double>p2)
{
    return sqrt( (p1.first.first - p2.first.first)*(p1.first.first - p2.first.first) + (p1.second - p2.second)*(p1.second - p2.second) + (p1.first.second - p2.first.second)*(p1.first.second - p2.first.second));
}

double Area(pair<pair<double, double>, double> A, pair<pair<double, double>, double> B, pair<pair<double, double>, double> C){
	double a = dist(A,B);
	double b = dist(A,C);
	double c = dist(B,C);
	double s = (a+b+c)/2;
	return sqrt(s * (s-a) * (s-b) * (s-c));
}


//double minCost( int cost[][100], int m, int n, vector< pair<pair<double, double>, double> > Value1, vector< pair<pair<double, double>, double> > Value2, vector< pair<pair<int, int>, int> > &result){
//	if(n<0 || m<0){//m=4, n=5, C=5, R=6
//		return INT_MAX;
//	}
//	else if (m == 0 && n == 0){
//		return cost[m][n];
//	}
//	else{
////		if (minCost(cost, m-1, n, Value1, Value2, result)+Area(Value1[m-1], Value2[n], Value1[m]) < minCost(cost, m, n-1, Value1, Value2, result)+Area(Value1[m], Value2[n-1], Value2[n]))//(minCost(cost, m-1, n)+weight[m][n+1][m+1] < minCost(cost, m, n-1)+weight[m+1][n][n+1])
////		{			
////			result.push_back(make_pair(make_pair(m,n+1+m+1), m+1));
////		}
////		else{
////			result.push_back(make_pair(make_pair(m+1,n+m+1), n+1+m+1));			
////		}
//		cout << Area(Value1[m-1], Value2[n], Value1[m]) <<endl;
//		return min(minCost(cost, m-1, n, Value1, Value2, result)+Area(Value1[m-1], Value2[n], Value1[m]), minCost(cost, m, n-1, Value1, Value2, result)+Area(Value1[m], Value2[n-1], Value2[n]));
//		}
//}

double minCost(int start, int m, int n, vector< pair<pair<double, double>, double> > Value1, vector< pair<pair<double, double>, double> > Value2, vector< pair<pair<int, int>, int> > &result){
	double** tc = new double*[1000];
	for(int i=0; i<1000; i++){
		tc[i] = new double[1000];
	}
	int M = m;
	tc[0][start] = 0;
	for(int i=1; i<=m; i++){
		tc[i][start] = tc[i-1][start] + Area(Value1[i-1], Value2[start], Value1[i]);
	}
	for(int j=1+start; j<=n+start; j++){
		tc[0][j] = tc[0][j-1] + Area(Value1[0], Value2[j-1], Value2[j]);
	}
	for(int i=1; i<=m; i++){
		for(int j=1+start; j<=n+start; j++){
			tc[i][j] = min(tc[i-1][j]+Area(Value1[i-1], Value2[j], Value1[i]), tc[i][j-1]+Area(Value1[i], Value2[j-1], Value2[j]));
			//cout << Area(Value1[i], Value2[j-1], Value2[j]) <<", " <<Area(Value1[i-1], Value2[j], Value1[i])  <<endl;
		}
		
	}
	int p1 = m;
	int p2 = n+start;
	//cout << "value is " <<tc[p1][p2] <<endl;
	for(int i=0; i<n+m; i++){
			if (tc[p1][p2] == tc[p1][p2-1]+Area(Value1[p1], Value2[p2-1], Value2[p2])){
				int a = p1 + 1;
				if(a>m){a = a-m;}
				if(a == 0){a = 1;} 
				int b = p2 + M;
				if(b-m>n){b = b-n;}
				if(b<=m){b++;}
				int c = p2 + 1 + M;
				if (c-m>n){c = c-n;}
				if(c<=m){c++;}
				result.push_back(make_pair(make_pair(a,b), c));
				p2--;
			}
			else if (tc[p1][p2] == tc[p1-1][p2]+Area(Value1[p1-1], Value2[p2], Value1[p1])){
				int a = p1;
				if(a>m) {a = a - m;}
				if(a == 0){a = 1;} 
				int b = p2 + 1 + M;
				if(b-m>n){b = b - n;}
				if(b<=m){b++;}
				int c = p1 + 1;
				if(c>m){c = c-m;}
				if(c==0){c = 1;}
				result.push_back(make_pair(make_pair(a,b), c));
				p1--;
			}
			else{
				result.push_back(make_pair(make_pair(99,99),99));
			}
	}
	double lol = tc[m][n+start];
//	for(int i=0; i<=m; i++){
//		for (int j=0; j<=n; j++){
//			cout << tc[i][j] <<endl;
//		}
//	}
	for(int i=0; i<1000; i++){
		delete [] tc[i];
	}
	delete [] tc;
	
	return lol;
	
}

int main(int argc, char** argv){
    int n1, n2;
    cin >> n1;
    cin >> n2;
    vector< pair<pair<double, double>, double> > Con1(n1);
    for(int i=0; i<n1; i++){
    	cin >> Con1[i].first.first;
        cin >> Con1[i].first.second;	
        cin >> Con1[i].second;
	}
	for(int i=0; i<n1; i++){
		Con1.push_back(Con1[i]);
	}
	Con1.push_back(make_pair(make_pair(Con1[0].first.first, Con1[0].first.second), Con1[0].second));
	vector< pair<pair<double, double>, double> > Con2(n2);
    for(int i=0; i<n2; i++){
    	cin >> Con2[i].first.first;
        cin >> Con2[i].first.second;
        cin >> Con2[i].second;
	}
//	if(Con2[0].first.first!=Con1[0].first.first){
//		for(int i=1; i<Con2.size(); i++){
//			if(Con2[i].first.first == Con1[0].first.first){
//				if(Con2[i].first.second == Con1[0].first.second){
//					rotate(Con2.begin(), Con2.begin()+i, Con2.end());
//				}
//			}
//		}
//	}
	for(int i=0; i<n2; i++){
		Con2.push_back(Con2[i]);
	}
	Con2.push_back(make_pair(make_pair(Con2[0].first.first, Con2[0].first.second), Con2[0].second));
	cout <<endl;
//	for(int i=0; i<4; i++){
//		cout << Area(Con1[4], Con2[i], Con2[i+1]) <<", ";
//	} 
	vector< pair<pair<int, int>, int> > hold;
	vector< pair<pair<int, int>, int> > result;
	
	double min = 9999999999.99;
	for(int i=0; i<n2; i++){
		if(minCost(i, n1, n2, Con1, Con2, hold) < min){
			hold.clear();
			min = minCost(i, n1, n2, Con1, Con2, hold);
			result = hold;
		}
	}
	
	//double TC = minCost(0, n1, n2, Con1, Con2, hold);
	//cout << min;
	for(int i=0; i<result.size(); i++)
	{
		cout << result[i].first.first <<" " << result[i].first.second <<" " << result[i].second <<endl;
	}
	
	
	
	
//	for(int i=0; i<n1; i++){
//		for(int j=0; j<n2; j++){
//			cost[i][j] = Area 
//		}
	}
	
