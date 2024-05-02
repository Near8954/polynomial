#ifndef POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_H

#include <string>
#include "../node/node.h"
class Polynomial {
public:
    Polynomial();
    ~Polynomial();
    explicit Polynomial(std::string s);
    Polynomial(const Polynomial &pol);

    void insert_back(Node *&e);
    void insert_back(const Polynomial& pol);
    void remove(Node *&it);
    void clear();

    void sort();
    void normalize();

    int64_t getValueInPoint(std::vector<int64_t> &vars);
    Polynomial getDerivative(int n, char x);

    Polynomial operator+(const Polynomial &pol);
    Polynomial operator*(const Polynomial &pol);
    Polynomial operator-(const Polynomial &pol);
    Polynomial operator/(Polynomial pol);
    Polynomial& operator=(const Polynomial &pol);
    bool operator==(const Polynomial &pol);

    std::vector<int64_t> getRoots();
    std::string toString();

    void setNext(Polynomial *&pol);
    void setNextNull();
    void setPrev(Polynomial *&pol);
    void setPrevNull();

    Polynomial *getNext();
    Polynomial *getPrev();

    Node *getHead();
    Node *getTail();

    int size();

private:
    Node *head = nullptr;
    Node *tail = nullptr;
    Polynomial *next = nullptr;
    Polynomial *prev = nullptr;
    int sz = 0;
};
#endif //POLYNOMIAL_POLYNOMIAL_H
