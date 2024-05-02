#ifndef NODE_H
#define NODE_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <set>
#include <cstdint>

struct WrongMonomial {
    explicit WrongMonomial(std::string s, char ch) {
        errorType = std::move(s);
        c = ch;
    }

    std::string errorType;
    char c = 'Z';
};

struct Node {
    Node();

    explicit Node(std::string s);

    Node(const Node &t);

    ~Node() = default;

    bool operator<(Node &nd);

    bool operator==(Node &nd);

    bool operator!=(Node &nd);

    bool operator>(Node &nd);

    bool operator<=(Node &nd);

    Node operator*(Node &nd);

    Node operator/(Node &nd);

    Node getDerivative(char x);

    std::string toString();

    int64_t coefficient = 1;
    std::vector<int64_t> powers;
    Node *prev = nullptr;
    Node *next = nullptr;
};

#endif // NODE_H