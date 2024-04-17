#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <iostream>
struct wrong_monomial {
    wrong_monomial(std::string s, char ch) {
        error_type = s;
        c = ch;
    }

    std::string error_type;
    char c = 'Z';
};

struct node {
    node();

    node(std::string s);

    node(const node &t);

    ~node() = default;

    bool operator<(node &nd);

    bool operator==(node &nd);

    bool operator!=(node &nd);

    node operator*(node &nd);

    bool operator>(node &nd);

    bool operator<=(node &nd);

    std::string to_string();

    double k = 1;
    std::vector<double> powers;
    node *prev = nullptr;
    node *next = nullptr;
};


#endif // NODE_H
