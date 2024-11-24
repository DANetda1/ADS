#include <cmath>
#include <fstream>
#include <random>
#include <algorithm>
#include <iostream>

bool is_point_inside_intersection(long double x, long double y, long double x1,
                                   long double y1, long double r1,
                                   long double x2, long double y2,
                                   long double r2, long double x3,
                                   long double y3, long double r3) {
    return pow(x - x1, 2) + pow(y - y1, 2) <= pow(r1, 2) &&
           pow(x - x2, 2) + pow(y - y2, 2) < pow(r2, 2) &&
           pow(x - x3, 2) + pow(y - y3, 2) < pow(r3, 2);
}
long double intersection_area(int n, long double scale = 1) {
    long double x1 = 1;
    long double y1 = 1;
    long double r1 = 1;
    long double x2 = 1.5;
    long double y2 = 2;
    long double r2 = sqrt(5) / 2;
    long double x3 = 2;
    long double y3 = 1.5;
    long double r3 = sqrt(5) / 2;

    long double max_x = std::max({x1 + r1, x2 + r2, x3 + r3});
    long double min_x = std::min({x1 - r1, x2 - r2, x3 - r3});
    long double max_y = std::max({y1 + r1, y2 + r2, y3 + r3});
    long double min_y = std::min({y1 - r1, y2 - r2, y3 - r3});

    std::random_device random_dev;
    std::mt19937 generator(random_dev());
    std::uniform_real_distribution<long double> rndx(min_x * scale, max_x * scale);
    std::uniform_real_distribution<long double> rndy(min_y * scale, max_y * scale);

    int k = 0;
    for(int iteration = 0; iteration < n; ++iteration){
        long double x = rndx(generator);
        long double y = rndy(generator);

        if(is_point_inside_intersection(x, y, x1, y1, r1, x2, y2, r2, x3, y3, r3)){
            ++k;
        }
    }

    return (static_cast<long double>(k) * (max_x - min_x) * (max_y - min_y)) / n * scale * scale;
}

int main() {
    long double right_area = M_PI / 4 + 5 * asin(0.8) / 4 - 1;
    std::ofstream result1("result1.csv");
    if (!result1.is_open()) {
        std::cerr << "Не удалось открыть файл result1.csv для записи.\n";
        return 1;
    }
    result1 << "n;area;area_diff\n";
    for(int n = 100; n < 100000; n += 500){
        long double area = intersection_area(n);
        result1 << n << ';' << area << ';' << std::abs(area - right_area) << '\n';
    }
    result1.close();
    std::ofstream result2("result2.csv");
    if (!result2.is_open()) {
        std::cerr << "Не удалось открыть файл result2.csv для записи.\n";
        return 1;
    }
    result2 << "scale;area;area_diff\n";

    for(long double scale = 1; scale < 10; scale += 0.1){
        long double area = intersection_area(1000000, scale);
        result2 << scale << ';' << area << ';' << std::abs(area - right_area) << '\n';
    }
    result2.close();

    return 0;
}