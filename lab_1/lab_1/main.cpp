//
//  main.cpp
//  Test
//
//  Created by Влад Комсомоленко on 26.02.2020.
//  Copyright © 2020 Space. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>


double funck(double x){
    double y = x*log(x);
    return y;
}

double value_min(std::vector<double> values, int width){
    double value_min = 100000;
    for (int i = 0; i < width; i++){
        if (values[i] < value_min && values[i] > -10000){
            value_min = values[i];
        }
    }
    return value_min;
}

double value_max(std::vector<double> values, int width){
    double value_max = -100000;
    for (int i = 0; i < width; i++){
        if (values[i] > value_max){
            value_max = values[i];
        }
    }
    return value_max;
}

int main(int argc, const char * argv[]) {
    int columns; int height; double x0; double x1;
    std::cin >> columns >> height >> x0 >> x1;
    std::vector<double> values;
    x0 = (int)(x0 * 100) / 100;
    x1 = (int)(x1 * 100) / 100;
    height++; // для строки с нулём
    double x_step = (x1 - x0) / columns;
    for (int i = 0; i < columns; i++){
        double x = x0 + (i * x_step);
        values.push_back(funck(x));
        
    }
    double y_min = value_min(values, columns);
    double y_max = value_max(values, columns);
    double y_step = (y_max - y_min) / height;
    // определяем у=0
    int z_string = 0;
    int negative = 0;
    double first = 0;
    double second = 0;
    for (int i = 0; i < columns-1; i++){
        if (values[i] > -100000){
            first = values[i];
            second = values[i+1];
            break;
        }
    }
    double difference = first;
    double y = 0;
    if (first > second){
        y = y_max;
    } else {
        y = y_min;
    }
    for (int i = 0; i < height; i++){
        if ((y_max <= 0) && (y_min < 0)){
            negative = 0;
            break;
        }
        else if ((y_min >= 0) && (y_max > 0)){
            z_string = height - 1;
            break;
        }
        if (first < second){
            y += y_step;
            if (abs(y) <= abs(difference)){
                difference = abs(y);
                negative = i + 1;
                z_string = height - negative;
            }
        }
        if (first > second){
            y -= y_step;
            if (abs(y) <= abs(difference)){
                difference = abs(y);
                z_string = i + 1;
                negative = height - z_string;
            }
        }
    }

    //создаём и заполняем пустыми значениями массив
    const char* ary[height][columns];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < columns; j++) {
            ary[i][j] = " ";
        }
    }
    for (int i = 0; i < columns; i++) {
        
        ary[z_string][i] = "-";
    }
    for (int i = 0; i < columns; i++){
        for (int j = 0; j < height; j++){
            if (z_string == columns){
                ary[j][i] = "-";
            }
            else if ((y_max-y_step*j)<=values[i] && j < z_string){
                ary[j][i] = "#";
            }
            else if ((y_max-y_step*j)>=values[i] && j > z_string){
                ary[j][i] = "#";
            }
        }
    }
    //вывод массива
    for (int i = 0; i < height; i++) {
        if (i < 9){
            std::cout << i+1 << ") ";
        } else {
            std::cout << i+1 << ")";
        }
        
        for (int j = 0; j < columns; j++) {
            std::cout << ary[i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}
