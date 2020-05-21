//
//  lab_2
//
//  Created by Влад Комсомоленко on 18.05.2020.
//  Copyright © 2020 Space. All rights reserved.
//

#include <iostream>

template <typename T>
class safe_c_array_t {
   private:
    int size = 0;
    T *array{};

   public:
    explicit safe_c_array_t(int arr_size) {
        size = arr_size;
        array = new T[size];
    }

    safe_c_array_t(safe_c_array_t const &arr) {
        size = arr.size;
        array = new T[size];
        for (int i = 0; i < size; i++) {
            array[i] = arr.array[i];
        }
    }

    safe_c_array_t &operator=(const safe_c_array_t &arr) {
        if (this != &arr) {
            delete[] array;
            size = arr.size;
            array = new T[size];
            for (int i = 0; i < size; i++) {
                array[i] = arr.array[i];
            }
        }
        return *this;
    }

    ~safe_c_array_t() {
        delete[] array;
    }

    T &operator[](int n) {
        return array[n];
    }
};

int main() {
    safe_c_array_t <int>array_1(10);
    safe_c_array_t <int>array_2(array_1);
    return 0;
}
