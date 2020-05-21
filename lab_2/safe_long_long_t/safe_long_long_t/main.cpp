//
//  main.cpp
//  lab_2
//
//  Created by Влад Комсомоленко on 27.02.2020.
//  Copyright © 2020 Space. All rights reserved.
//

#include <iostream>

class safe_long_long_t {
   private:
    long long value;

   public:
    safe_long_long_t(long long value) : value(value) {}
    long long Value() {
        return value;
    }
    void operator = (safe_long_long_t i) {
        value = i.value;
    }
    void operator += (safe_long_long_t i) {
           value += i.value;
       }
    void operator -= (safe_long_long_t i) {
           value -= i.value;
       }
    void operator *= (safe_long_long_t i) {
           value = i.value;
       }
    void operator /= (safe_long_long_t i) {
           value /= i.value;
       }
    safe_long_long_t operator + (safe_long_long_t j) {
        return safe_long_long_t(value + j.value);
    }
    safe_long_long_t operator - (safe_long_long_t j) {
        return safe_long_long_t(value - j.value);
    }
    safe_long_long_t operator * (safe_long_long_t j) {
        return safe_long_long_t(value * j.value);
    }
    safe_long_long_t operator / (safe_long_long_t j) {
        return safe_long_long_t(value / j.value);
    }
    bool operator < (safe_long_long_t j) {
        return value < j.value;
    }
    bool operator > (safe_long_long_t j) {
        return value > j.value;
    }
    bool operator != (safe_long_long_t j) {
        return !(value == j.value);
    }
    bool operator == (safe_long_long_t j) {
        return value == j.value;
    }
};
std::ostream& operator<<(std::ostream& out, safe_long_long_t i) {
    out << i.Value();
    return out;
}
std::istream& operator>>(std::istream& in, safe_long_long_t i) {
    in >> i.Value();
    return in;
}

int main() {
    safe_long_long_t i = 100;
    safe_long_long_t j = 10;
    std::cout << "i = " << i << std::endl;
    std::cout << "j = " << j << std::endl;
    std::cout << i << " + " << j << " = " << (i + j) << std::endl;
    std::cout << i << " - " << j << " = " << (i - j) << std::endl;
    std::cout << i << " * " << j << " = " << (i * j) << std::endl;
    std::cout << i << " / " << j << " = " << (i / j) << std::endl;
    std::cout << i << " != " << j << " => " << (i != j) << std::endl;
    std::cout << i << " == " << j << " => " << (i == j) << std::endl;
    std::cout << i << " < " << j << " => " << (i < j) << std::endl;
    std::cout << i << " > " << j << " => " << (i > j) << std::endl;
    return 0;
}
