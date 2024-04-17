#ifndef BASE_H
#define BASE_H
#include "../polynomial/polynomial.h"

class base {
public:
    void insert_back(polynomial *&pol);

    void remove(polynomial *&pol);

    polynomial* get(int id);

    polynomial* get_head();

    int size() {
        return sz;
    }

    std::string to_string();
private:
    polynomial* head = nullptr;
    polynomial* tail = nullptr;
    int sz = 0;
};

#endif // BASE_H
