#include <bits/stdc++.h>
#include <cmath>
#include <iomanip>
using namespace std;

struct Circle {
    double x;
    double y;
    double r;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<Circle> circles(3);
    for(int i=0; i<3; ++i){
        cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }
    double min_x = circles[0].x - circles[0].r;
    double max_x = circles[0].x + circles[0].r;
    double min_y = circles[0].y - circles[0].r;
    double max_y = circles[0].y + circles[0].r;
    for(int i=1; i<3; ++i){
        min_x = min(min_x, circles[i].x - circles[i].r);
        max_x = max(max_x, circles[i].x + circles[i].r);
        min_y = min(min_y, circles[i].y - circles[i].r);
        max_y = max(max_y, circles[i].y + circles[i].r);
    }
    const long long N = 1000000;
    long long M = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis_x(min_x, max_x);
    uniform_real_distribution<double> dis_y(min_y, max_y);
    auto is_inside = [&](double x, double y) -> bool {
        for(int i=0; i<3; ++i){
            double dx = x - circles[i].x;
            double dy = y - circles[i].y;
            if(dx*dx + dy*dy > circles[i].r * circles[i].r){
                return false;
            }
        }
        return true;
    };
    for(long long i=0; i<N; ++i){
        double x = dis_x(gen);
        double y = dis_y(gen);
        if(is_inside(x, y)){
            M++;
        }
    }
    double Srec = (max_x - min_x) * (max_y - min_y);
    double Se = ((double)M / N) * Srec;
    cout << fixed << setprecision(10) << Se;
}