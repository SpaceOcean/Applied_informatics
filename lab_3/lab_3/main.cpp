//
//  main.cpp
//  lab_3
//
//  Created by Влад Комсомоленко on 29.05.2020.
//  Copyright © 2020 Space. All rights reserved.
//

#include <iostream>
#include <sstream>

class int_list_t {
private:
    struct node_t {
        int value;
        node_t *next = nullptr;
        node_t *prev = nullptr;
        
    };
    node_t *top = new node_t;
    node_t *bottom = new node_t;
    size_t list_size;

    node_t *find(size_t pos) const {
        node_t *current;
        if (list_size / 2 > pos) {
            current = bottom->next;
            while (pos > 0) {
                current = current->next;
                pos--;
            }
        } else {
            current = top;
            while (pos != list_size) {
                current = current->prev;
                pos++;
            }
        }
        return current;
    }

public:
    int_list_t(){
        bottom->next = top;
        top->prev = bottom;
        list_size = 0;
    }; // O(1)
    
    int_list_t(const int_list_t &other){
        bottom->next = top;
        top->prev = bottom;
        list_size = 0;
        node_t *current = other.bottom->next;
        while (current != other.top) {
            push_back(current->value);
            current = current->next;
        }
    }; // COPY $other list O(other.size)
    
    int_list_t(size_t count, int value){
        bottom->next = top;
        top->prev = bottom;
        list_size = 0;
        for (size_t i = 0; i < count; i++) {
            push_back(value);
        }
    }; // create list $count size and fill it with $value O($count)
    
    ~int_list_t(){
        clear();
        delete top;
        delete bottom;
    };    // O(size)
 
    int_list_t &operator=(const int_list_t &other){
        if (this != &other) {
            clear();
            node_t *current = other.bottom->next;
            while (current != other.top) {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }; // O(size + other.size())
 
    int &operator[](size_t pos){
        return find(pos)->value;
    }; // O(min($pos, size - $pos))
    
    const int operator[](size_t pos) const{
        return find(pos)->value;
    }; // O(min($pos, size - $pos))
 
    int &back(){
        return top->prev->value;
    };    // last element O(1)
    
    const int back() const{
        return top->prev->value;
    }; // O(1)
 
    int &front(){
        return bottom->next->value;
    };    // first element O(1)
    
    const int front() const{
        return bottom->next->value;
    }; // O(1)
 
    void clear(){
        while (list_size != 0) {
            erase(0);
        }
    }; // O(size)
    
    size_t size() const{
        return list_size;
    }; // O(1)
    
    bool empty() const{
        return list_size == 0;
    }; // O(1)
 
    void insert(size_t pos, int new_val){
        auto *before = find(pos);
        auto *new_element = new node_t;
        new_element->next = before;
        new_element->prev = before->prev;
        before->prev->next = new_element;
        before->prev = new_element;
        new_element->value = new_val;
        list_size++;
    }; // insert element $new_val BEFORE element with index $pos O(min($pos, size - $pos))
    
    void push_front(int new_val){
        insert(0, new_val);
    }; // O(1)
    
    void push_back(int new_val){
        insert(list_size, new_val);
    };    // O(1)
 
    void erase(size_t pos){
        node_t *current = find(pos);
        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
        list_size--;
    }; // remove element with index $pos O(min($pos, size - $pos))
    
    void pop_front(){
        erase(0);
    }; // O(1)
    
    void pop_back(){
        erase(list_size - 1);
    };  // O(1)
 
    int_list_t splice(size_t start_pos, size_t count){
        auto *list = new int_list_t();
        node_t *first = find(start_pos);
        node_t *last = find(start_pos + count - 1);
        list->bottom->next = first;
        first->prev->next = last->next;
        last->next->prev = first->prev;
        first->prev = list->bottom;
        list->top->prev = last;
        last->next = list->top;
        list_size -= count;
        list->list_size += count;
        return *list;
    }; // splice part of list into result (not copy!) O($start_pos + $count)
    
    int_list_t &merge(int_list_t &other){
        if (other.size() != 0) {
            node_t *first = other.bottom->next;
            node_t *last = other.top->prev;
            top->prev->next = first;
            first->prev->next = last->next;
            last->next->prev = first->prev;
            first->prev = top->prev;
            top->prev = last;
            last->next = top;
            list_size += other.list_size;
            other.list_size = 0;
        }
        return *this;
    }; // merge two lists, after operation $other must be valid empty list O(1)
 
    void reverse(){
        node_t *current = bottom->next;
        node_t *next;
        node_t *prev = top;
        top->prev->next = bottom;
        std::swap(top->prev, bottom->next);
        while (current != bottom) {
            next = current->next;
            current->next = prev;
            current->prev = next;
            prev = current;
            current = next;
        }
    }; // O(size)
    
    void swap(int_list_t &other){
        std::swap(this->bottom, other.bottom);
        std::swap(this->top, other.top);
        std::swap(list_size, other.list_size);
    }; // O(1)
 
    friend std::istream &operator>>(std::istream &stream, int_list_t &list){
        int value = 0;
        list.clear();
        while (stream >> value) {
            list.push_back(value);
        }
        return stream;
    };    // O(size)
    
    friend std::ostream &operator<<(std::ostream &stream, const int_list_t &list){
        auto current = list.bottom->next;
        while (current != list.top) {
            stream << current->value << " ";
            current = current->next;
        }
        return stream;
    }; // O(size)
 
};

int main(int argc, const char * argv[]) {
    int_list_t list_1(10, 7);
    std::cout << "list_1: " << list_1 << std::endl;
    int_list_t list_2(list_1);
    std::cout << "list_2: " << list_2 << std::endl;
    list_2.push_front(20);
    std::cout << "list_2.push_front list_2: " << list_2 << std::endl;
    list_2.insert(4, 13);
    std::cout << "list_2.insert list_2: " << list_2 << std::endl;
    list_2.erase(3);
    std::cout << "list_2.erase list_2: " << list_2 << std::endl;
    list_2.merge(list_1);
    std::cout << "merge list_2: " << list_2 << std::endl;
    list_2.pop_front();
    std::cout << "list_2.pop_front list_2: " << list_2 << std::endl;
    list_2.pop_back();
    std::cout << "list_2.pop_back list_2: " << list_2 << std::endl;
    list_2.splice(0, 5);
    std::cout << "list_2.splice list_2: " << list_2 << std::endl;
    list_2.insert(list_2.size(), 1703);
    std::cout << "list_2.insert list_2: " << list_2 << std::endl;
    list_2.reverse();
    std::cout << "list_2.reverse list_2: " << list_2 << std::endl;
    list_2.clear();
    std::cout << "list_2.clear list_2: " << list_2 << std::endl;
}
