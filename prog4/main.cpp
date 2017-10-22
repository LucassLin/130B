#include <iostream>
#include <time.h> 
#include <cmath>
#include <stdlib.h>
#include <numeric>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

bool myComparison(const pair<pair<double, double>, double> &a,const pair<pair<double, double>, double> &b)
{
       return a.second<b.second;
}

bool myComparison1(const pair<double,double> &a,const pair<double,double> &b)
{
       return a.first<b.first;
}

bool myComparison2(const pair<double,double> &a,const pair<double,double> &b)
{
       return a.second<b.second;
}

//double distance(pair<double,double> P1, pair<double,double> P2, pair<double,double> P3){
//	
//}

int main(int argc, char** argv){
    int n;
    cin >> n;
    vector<pair<double,double> > points(n);
	for(int i=0; i<n; i++)
	{
		double x, y;
		cin >> x;
		cin >> y;
		points[i].first = x;
		points[i].second = y;
	}
	
	srand ( time(NULL) );
	double MAD = 100000000;
	vector< pair<pair<double, double>, double> > result;
	
	int k;
	if(n<500){k=n*2;}
	else if(n>500 && n<2000){k=n;}
	else {k= n/20;}
	for(int i=0; i<k; i++){
		int R1, R2;
		R1 = rand() % n;
		do{
			R2 = rand() % n;
		}while (R1 == R2);
		vector< pair<pair<double, double>, double> > hold;
		double dx = points[R1].first - points[R2].first; 
		double dy = points[R1].second - points[R2].second;
		double a1 = dy/dx;
		double b1 = points[R1].second - a1*points[R1].first;
		vector<double> distance;
		vector<double> temp;
		double dis = 0; 
		for(int i=0; i<n; i++){
			if(i!=R1 && i!=R2){
				double a2 = -1 / a1;
				double b2 = points[i].second - a2*points[i].first;
				
				double x2 = (b2-b1)/(a1-a2);
				double y2 = a2*x2 + b2;
				
				double dist = sqrt( (points[i].first - x2)*(points[i].first - x2) + (points[i].second - y2)*(points[i].second - y2));
				hold.push_back(make_pair(make_pair(points[i].first, points[i].second), dist));
			}
		}
		sort(hold.begin(), hold.end(), myComparison);
		double MedianX = hold[hold.size()/2-1].second;
		vector< pair<pair<double, double>, double> > MADV;
		for(int i=0; i<hold.size(); i++){
			MADV.push_back(make_pair(make_pair(hold[i].first.first, hold[i].first.second), abs(hold[i].second - MedianX)));
		}
		sort(MADV.begin(), MADV.end(), myComparison);
		
		
		if(MADV[MADV.size()/2-1].second < MAD){
			MAD = MADV[MADV.size()/2-1].second;
			result = MADV;
		}	
	}
	vector<double> X;
	vector<double> Y;
	for(int i=0; i<result.size(); i++){
		if(result[i].second <= MAD){
			X.push_back(result[i].first.first);
			Y.push_back(result[i].first.second);
		}
	}

	
	double sumX = accumulate(X.begin(), X.end(), 0.0);
	double meanX = sumX / X.size();
	double sumY = accumulate(Y.begin(), Y.end(), 0.0);
	double meanY = sumY / Y.size();
	
	double top = 0;
	double bottom = 0;
	for(int i=0; i<X.size(); i++){
		top = top + (X[i]-meanX)*(Y[i]-meanY);
		bottom = bottom + (X[i]-meanX)*(X[i]-meanX);
	}	
	double Slope = top/bottom;
	double inter = meanY - Slope*meanX;

	cout << endl;
	std::cout << std::setprecision(3) << "a = " << Slope <<endl;
	std::cout << std::setprecision(3) << "b = " << inter <<endl;
	
	
}
