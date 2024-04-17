#include "node.h"

std::pair<double, std::vector<double>> check(const std::string &s) {
    double k = 1.0;
    if (s.empty()) {
        return {0, std::vector<double>(26)};
    }
    std::string num;
    int state = 0;
    bool sign = false;
    char var = 'Z';
    std::vector<double> pows;
    pows.resize(26);
    try {
        for (char i: s) {
            if (state == 0) {
                if (isdigit(i)) {
                    state = 1;
                    num += i;
                } else if (i >= 'a' && i <= 'z') {
                    state = 2;
                    var = i;
                } else if (i == '-' || i == '+') {
                    if (i == '-') {
                        sign = !sign;
                    }
                } else {
                    throw wrong_monomial("unexpected symbol ", i);
                }
            } else if (state == 1) {
                if (isdigit(i)) {
                    state = 1;
                    num += i;
                } else if (i >= 'a' && i <= 'z') {
                    state = 2;
                    k = std::stoi(num);
                    var = i;
                    num.clear();
                } else if (i == '-' || i == '+') {
                    throw wrong_monomial("incorrect sign place ", i);
                } else {
                    throw wrong_monomial("unexpected symbol ", i);
                }
            } else if (state == 2) {
                if (isdigit(i)) {
                    throw wrong_monomial("expected num found ", i);
                } else if (i >= 'a' && i <= 'z') {
                    if (num.empty()) {
                        pows[var - 'a'] += 1;
                    } else {
                        pows[var - 'a'] += std::stoi(num);
                        num.clear();
                    }
                    var = i;
                } else if (i == '^') {
                    state = 3;
                } else if (i == '-' || i == '+') {
                    throw wrong_monomial("incorrect sign place", i);
                } else {
                    throw wrong_monomial("unexpected symbol ", i);
                }
            } else if (state == 3) {
                if (isdigit(i)) {
                    num += i;
                } else if (i >= 'a' && i <= 'z') {
                    state = 2;
                    if (num.empty()) {
                        throw wrong_monomial("var in power ", i);
                    } else {
                        pows[var - 'a'] += std::stoi(num);
                        var = i;
                        num.clear();
                    }
                } else if (i == '^') {
                    throw wrong_monomial("double power ", i);
                } else if (i == '-' || i == '+') {
                    throw wrong_monomial("incorrect sign place", i);
                } else {
                    throw wrong_monomial("unexpected symbol ", i);
                }
            }
        }
        if (var == 'Z') {
            k = std::stoi(num);
        }
        if (state == 3 && num.empty()) {
            throw wrong_monomial("incorrect power", 'Z');
        }
        if (num.empty() && var != 'Z') {
            pows[var - 'a'] += 1;
        }
        if (!num.empty() && var != 'Z') {
            pows[var - 'a'] += std::stoi(num);
        }
        if (sign) {
            k *= -1;
        }
    } catch (const wrong_monomial &mn) {
        throw;
    }
    return {k, pows};
}



node::node() {
    powers.resize(26);
    k = 1.0;
    prev = nullptr;
    next = nullptr;
}

node::node(const node &t) {
    k = t.k;
    powers = t.powers;
    prev = t.prev;
    next = t.next;
};

node::node(std::string s) {
    prev = nullptr;
    next = nullptr;
    powers.resize(26);
    auto nd(check(s));
    powers = nd.second;
    k = nd.first;
};



std::string node::to_string() {
    std::string ans;
    if (k != 1) {
        ans += std::to_string((int)this->k);
    }
    for (int i = 0; i < 26; ++i) {
        if (this->powers[i] != 0) {
            ans += char(i + 'a');
            if (this->powers[i] != 1) {
                ans += '^';
                ans += std::to_string((int)this->powers[i]);
            }
        }
    }
    return ans;
}

bool node::operator<(node &nd) {
    for (int i = 0; i < 26; ++i) {
        if (this->powers[i] < nd.powers[i]) return true;
        else if (this->powers[i] > nd.powers[i]) return false;
    }
    return (this->k < nd.k);
}

bool node::operator==(node &nd) {
    if (this->k != nd.k) {
        return false;
    }
    for (int i = 0; i < 26; ++i) {
        if (this->powers[i] != nd.powers[i]) {
            return false;
        }
    }
    return true;
}

bool node::operator!=(node &nd) {
    return !(*this == nd);
}


bool node::operator>(node &nd) {
    return (!(*this < nd) && !(*this == nd));
}

bool node::operator<=(node &nd) {
    return ((*this < nd) || (*this == nd));
}

node node::operator*(node &nd) {
    node ans;
    for (int i = 0; i < powers.size(); ++i) {
        ans.powers[i] += powers[i];
    }
    for (int i = 0; i < nd.powers.size(); ++i) {
        ans.powers[i] += nd.powers[i];
    }
    ans.k = k * nd.k;
    if (ans.k == 0) {
        ans.powers.clear();
    }
    return ans;
}


/*std::ostream &operator<<(std::ostream &os, const node &nd) {
    os << nd.k;
    for (int i = 0; i < 26; ++i) {
        if (nd.powers[i] != 0) {
            os << char(i + 'a') << '^' << nd.powers[i];
        }
    }
    return os;
}*/

