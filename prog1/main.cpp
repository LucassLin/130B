#include <stdio.h>
#include <algorithm>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>  
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool myComparison(const pair<double,double> &a,const pair<double,double> &b)
{
       return a.second<b.second;
}

vector<double> min(vector<double> x, vector<double> y)
{
    return (x[0] < y[0])? x : y;
}

float dist(pair<double,double>p1, pair<double,double>p2)
{
    return sqrt( (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second));
}

vector<double> bruteForce(vector<pair<double,double> >v, int n, int& count)
{
    vector<double> vi(5);
    float min = FLT_MAX;
    for(int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
                count++;
            if (dist(v[i], v[j]) < min){
                min = dist(v[i], v[j]);
                vi[0] = (min);
                vi[1] = (v[i].first);
                vi[2] = (v[i].second);
                vi[3] = (v[j].first);
                vi[4] = (v[j].second);
                //cout << "min is " << min <<" "<< "(" << v[i].first <<", " << v[i].second <<") " << "(" << v[j].first <<", " << v[j].second <<")\n";
            }
        }
    }

    return vi;
}

vector<double> stripClosest(vector<pair<double,double> > strip, int size, double d, int& count)
{
    vector<double> v(5);
    v[0] = 100000;
    double min = d;
    for(int i=0; i<size; i++)
    {
        for(int j=i+1; j<size && (strip[j].second - strip[i].second) < min; j++,count++)
        {
            if (dist(strip[i], strip[j]) < min){
                min = dist(strip[i], strip[j]);
                v[0] = (dist(strip[i], strip[j]));
                v[1] = (strip[i].first);
                v[2] = (strip[i].second);
                v[3] = (strip[j].first);
                v[4] = (strip[j].second);
            }
        }
    }
    return v;
}

vector<double> findmin(vector<pair<double,double> > v, int n, int& count)
{
    if (n <= 3)
    {
        return bruteForce(v, n, count);
    }
    int mid = n/2;
    pair<double,double> midPoint = v[mid];
    
    vector<pair<double,double> > v1(v.begin(), v.begin() + mid);
    vector<double> left = findmin(v1, mid, count);
    vector<pair<double,double> > v2(v.begin() + mid, v.end());
    vector<double> right = findmin(v2, n-mid, count);
    vector<double> d = min(left, right);
    double dis = d[0];
    count ++;
    
    vector<pair<double,double> > strip;//holds points in strip
    for (int i=0; i<n; i++){
        if (abs(v[i].first - midPoint.first) < dis){
            strip.push_back(v[i]);
        }
    }
    sort(strip.begin(), strip.end(), myComparison);//strip sorted
    count = count + strip.size();
    return min(d, stripClosest(strip, strip.size(), dis, count));
    
}


vector<double> BruteForce(vector<pair<double,double> > vec, int size, int& count)
{
    double min = FLT_MAX;
    vector<double> v(5);
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            count ++;
            if(dist(vec[i], vec[j]) < min){
                min = dist(vec[i], vec[j]);
                v[0] = (dist(vec[i], vec[j]));
                v[1] = (vec[i].first);
                v[2] = (vec[i].second);
                v[3] = (vec[j].first);
                v[4] = (vec[j].second);
            }
        }
    }
    return v;
}

/*
 * 
 */
int main(int argc, char** argv) {
    
//    ifstream fin ("testInputDouble01.txt", ifstream::in);
//    int n;
//    fin >> n;
//    int index = 0;
    int n;
    cin >> n;
    vector<pair<double,double> > points(n);
//    while(!fin.eof())
//    {
//	double x, y;
//	fin >> x;
//	fin >> y;
//	points[index].first = x;
//	points[index].second = y;
//	index++;
//    }
	for(int i=0; i<n; i++)
	{
		double x, y;
		cin >> x;
		cin >> y;
		points[i].first = x;
		points[i].second = y;
	}
    int count_number = 0;
    vector<double> result1 = BruteForce(points, n, count_number);

    cout<< std::showpoint << "(" << result1[3] << ", " << result1[4] <<")" <<" (" <<result1[1] << ", " << result1[2] <<")\n"; 
	cout << "Total number of comparison is " << count_number <<endl;
    
    int number_of_comparison = 0;// holds number of comparison for divide and conquer
    sort(points.begin(), points.end());
    pair<double,double> midPoint = points[n/2];
    
    vector<double> result;
    result = findmin(points, n, number_of_comparison);//find point using divde and conquer
    


    cout << std::showpoint << "(" << result[1] <<", " << result[2] << ") " << "(" <<result[3] <<", " <<result[4] <<")\n";
    cout << "Total number of comparison is " <<number_of_comparison <<endl;
    
    return 0;
}

