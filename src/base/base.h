#ifndef BASE_H
#define BASE_H

#include "../polynomial/polynomial.h"

class base {
public:
    void insert_back(Polynomial *&pol);

    void remove(Polynomial *&pol);

    Polynomial *get(int id);

    Polynomial *get_head();

    int size() {
        return sz;
    }

    std::string toString();

private:
    Polynomial *head = nullptr;
    Polynomial *tail = nullptr;
    int sz = 0;
};

#endif // BASE_H